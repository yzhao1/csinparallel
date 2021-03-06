.. Epidemic Simulation documentation master file, created by
   sphinx-quickstart on Thu Jun 13 13:47:49 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Epidemic Simulation
===================

.. toctree::
   :maxdepth: 1

   intro/intro
   cppspecs/cppspecs
   parallelizing/openmpandmpi
   parallelizing/gowalkthrough
   parallelizing/seqgocode1
   parallelizing/seqgocode2
   parallelizing/portingcpptogo
   testing/testing

Note on this module: there are four different versions of instructions for parallelizing in Go. 

   - The first gives fairly detailed Go specs and a walkthrough for writing them up, directed at students who have either Python or C++ experience and haven't necessarily written a C++ version of this code already. A more thorough set of parallelizing directions follows.

   - The second and thrid give sequential Go code, thoroughly commented for both Go style and the program's overall logic, and simply ask students to parallelize it (gocode1 is the thorough instructions from the full walkthrough; gocode2 is for more advanced students). These could be used in conjunction with the C++ version or not, as desired.

   
   - The fourth version is for students with some programming experience who are porting their existing C++ code into Go; it merely highlights some key structural and syntactic differences between the two languages and then lists resources for figuring out the rest.

.. comment
	* :ref:`genindex`
	* :ref:`modindex`
	* :ref:`search`
