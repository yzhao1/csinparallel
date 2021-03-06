/* PDC project S13 by Luke Bonde and Allison Brumfield   4/17/2013
   Simulates an epidemic or disease spreading through a population */


#include <iostream>
using namespace std;
#include <time.h>
#include <cstdlib>
#include <math.h>

const int width = 10000;    //The width of the environment
const int height = 10000;   //The height of the environemnt

// The state of health a person can be in
enum State {Susceptible = 0, Infected = 1, Recovered = 2};

//A class that contains the pertinate information about the specific disease 
class Infection {
public:
  int duration;          // 1 unit of time = 6 hours
  float contagiousness;  // Percent chance of transmission
  float radius;            // The radius in which transimission is possible
  Infection(int d, float c, float r) {
    duration = d;
    contagiousness = c;
    radius = r;}
} ;

//A class that represents a single person that can move around randomly in the world and potentially get sick
class Person {
public:
  int x,y;
  State state;
  int infectedPeriod; // Units of time until recovered.
  Person() { 
    x = rand() % width; 
    y = rand() % height; 
    state = Susceptible;}
    void updateState(State s) {
    state = s;}
  void infectWith(Infection i){
    updateState(Infected);
    infectedPeriod = i.duration;
  }
  bool isInfected(){
    return (state==Infected);
  }
  bool isSusceptible(){
    return (state==Susceptible);
  }
  void move() { 
    x = (x + (rand() % 5) - 2 + width) % width ; // Add width to ensure non-negativity...
    y = (y + (rand() % 5) - 2 + height) % height;
  }
  void timeStep() { 
    move();
    if (infectedPeriod > 0) --infectedPeriod;
    else if (infectedPeriod == 0 and isInfected()) updateState(Recovered);
  }
};

float dist(Person & p1, Person & p2) {
  float dist = pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2);
  return sqrt(dist);
}
  
int main() {
  srand(time(NULL));

  //Set up parameters
  int numPersons = 20000;
  int initialInfected = 200;
  int numIterations = 200;
  Infection Influenza(28,.5,45);
  Person * MN;
  MN = new Person[numPersons];

  //infect the starting number of infected people
  for (int i = 0; i < initialInfected; ++i)
    MN[i].infectedWith(Influenza);

  ///////////////// BEGIN SIMULATION //////////////////

  for (int i = 0; i < numIterations; ++i) { //controls iteration
    //For each person ...
    for (int p = 0; p < numPersons; ++p) {
      
      MN[p].timeStep(); //move and update health status

      if (MN[p].isInfected()) { 
	//if person is infected, check to see if any suseptible are within the radiuMN[p].timeStep();s of transmission
	for (int q = 0; q < numPersons; ++q) {
	  if (MN[q].isSusceptible()) {
	    if (dist(MN[p],MN[q]) < Influenza.radius) {
	      //if within the radius, simulate the chance of contracting the disease using a random number
	      if (((float)(rand() % 100))/100 < Influenza.contagiousness) {
		//if transmission occurs, infect the susceptible person
		MN[q].infectedWith(Influenza);
	      }
	    }
	  }
	}
      }
    }
  }

  ////////////// END OF SIMULATION ////////////////

  //Count final conditions
  int numInfected = 0, numSusceptible = 0;
  for (int p = 0; p < numPersons; ++p) {
    if (MN[p].isInfected())
      ++numInfected;
    if (MN[p].isSusceptible())
      ++numSusceptible;
  }
  //Print summary of final conditions
  cout << numSusceptible << " persons are still susceptible" << endl;
  cout << numInfected << " persons are currently infected" << endl;
  cout << numPersons - numSusceptible - numInfected << " persons have recovered." << endl;
}
