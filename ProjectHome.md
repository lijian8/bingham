# News #

### [2013-12-14] Created libbingham Tutorials ###
  * See the Tutorials section below for Matlab and C tutorials.

### [2013-05-20] Released libbingham v0.3 ###
  * Added matlab functions bingham\_fit() and bingham\_fit\_scatter().
  * Added several utility functions.

### [2012-04-18] Released libbingham v0.2.1 ###
  * Fixed a bug in bingham\_mult() caused by eigen\_symm() returning eigenvalues in the wrong order (compared to the GSL version).
  * Also added more matlab functions.

### [2012-04-12] Released libbingham v0.2 ###
  * Enlarged Bingham lookup tables to handle concentration params up to -900.
  * More MATLAB support.
  * Removed dependency on GSL.
  * Switched from GPL to BSD license.


# Overview #

The Bingham statistics library contains implementations of the Bingham distribution for directional (axial) statistics on the unit spheres S1, S2, and S3.  In addition, finite element approximations are available via tessellations of S2 and S3.


# Tutorials #

  * [libbingham Matlab tutorial](http://www.mit.edu/~jglov/research/libbingham_tutorials/matlab_tutorial.html)
  * [libbingham C tutorial](http://www.mit.edu/~jglov/research/libbingham_tutorials/c_tutorial.html)

# Documentation #

See [documentation](http://bingham.googlecode.com/svn/trunk/c/doc/html/index.html) for more info.