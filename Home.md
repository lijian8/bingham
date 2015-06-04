# Introduction #

Welcome!  The main purpose of this page is to provide documentation, examples, tutorials, etc. for the Bingham Statistics Library.  The library itself is brand new, so please be patient while we finish the documentation.


# What is the Bingham Statistics Library? #

The Bingham Statistics Library is a C library that contains implementations of the Bingham distribution for directional (axial) statistics on the unit spheres S<sup>1</sup>, S<sup>2</sup>, and S<sup>3</sup>.  A major focus of this project is to use the Bingham distribution to represent uncertainty on 3D rotations via the unit quaternion hypersphere (S<sup>3</sup>), thus there are many additional features in the library which are quaternion-specific.

In contrast to many statistics libraries which only provide a bare-bones implementation of each distribution (PDF, sampling, etc.), the Bingham Statistics Library contains functions for computing modes, entropy, KL divergence, parameter estimation, merging two Bingham distributions into one, multiplication of Bingham distributions, as well as discretization, composition, and many operations on Bingham mixture distributions.


# Why the Bingham Distribution? #

Many geometric quantities have a natural representation as a unit vector on a hypersphere. For example, an angle can be thought of as a point on a circle, a direction in 3-D as a point on a sphere, a 3-D rotation as a unit quaternion (which is a 4-D unit vector on the hypersphere S<sup>3</sup>), and the "shape" (i.e. all the information that is left when you remove position, scale, and orientation) of a sequence of N points in 2 or 3 dimensions as a point on the hypersphere S<sup>2N-1</sup> or S<sup>3N-1</sup>, respectively. Since angles, rotations, and shapes are plentiful in physical systems, there is a need to perform probabilistic inference on hyperspheres when there is uncertainty in the system. However, most existing algorithms ignore the topology of hyperspheres, and instead use a Gaussian noise model in a local, linear, tangent space. These methods work well when the errors are small, but as the variance grows, so too does the error of the linear approximation.

The Bingham distribution is an antipodally symmetric (which means that p(x) = p(-x)) probability distribution on hyperspheres.  The Bingham is a member of the exponential family, and is the maximum entropy distribution on the hypersphere which matches the sample inertia matrix (second moments).  Since the unit quaternions q and -q represent the same 3D rotation, the Bingham distribution is perfectly suited to representing uncertainty on 3D rotations.  The Bingham distribution has also been used on S<sup>2</sup>--most commonly in material science to represent preferred orientations of minerals in rocks.


# Usage #

The preferred method for download is svn, that way you'll get the latest code.

The library contains both C and Matlab code, but only the C code is currently supported.  (The Matlab functions are mostly used for plotting figures, and do not contain a complete implementation of the Bingham distribution.  Use with caution!)

In bingham/c, run:

```
make
make install
```

This will install the C library, libbingham.a, on your machine.  To use the library in your own project, simply add "-lbingham" to your linker flags and include the appropriate headers as you would with any other C library.

Documentation is still sparse, but there are many examples in the bingham/c directory in test\_bingham.c, test\_util.c, fit\_bingham.c, bingham\_lookup.c, bingham\_sample.c, and cluster\_bingham.c.



# Links #

The [Nuklei library](http://nuklei.sourceforge.net/) provides another open-source implementation of probability distributions on SO(3) and SE(3) data.  Nuklei is a C++ library that implements kernel functions and kernel density estimation for SE(3) data. Nuklei also provides tools for manipulating SE(3) transformations, and for manipulating point clouds.