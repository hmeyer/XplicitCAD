XplicitCAD
==========

C++ / VTK approach to Implicit CAD, heavily inspired by [ImplicitCAD](https://github.com/colah/ImplicitCAD). Xplicit aims to copy most of the nice features and genuis ideas from [colah](http://christopherolah.wordpress.com/2011/11/06/manipulation-of-implicit-functions-with-an-eye-on-cad/), and use them in conjunction with VTKs fast meshing and visualization framework.

CAD-Language
------------

In this first version Xplicit will use [Lua](http://http://www.lua.org/) - because it is easily embeddable.

Dependencies
------------

* libvtk5-dev

Issues
------

qt-moc raises an error during early build.
This is solved by [fixing Qt4Macros.cmake](http://vtk.1045678.n5.nabble.com/syntax-error-near-unexpected-token-td5681161.html).
