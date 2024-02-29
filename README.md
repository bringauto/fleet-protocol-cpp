# Fleet Protocol V2 CXX Helpers

This project provides a set of C++ classes to help with the implementation of the Fleet Protocol V2.

## Requirements

* CMLib

or

* Fleet protocol [>=v2.0.0]
> When not using CMLib, configure the project with `-DBRINGAUTO_SYSTEM_DEP=ON`

## Usage

### Installation

To install the library, first configure the project with CMake option BRINGAUTO_INSTALL=ON and BRINGAUTO_PACKAGE=ON and then install it.

```bash
mkdir _build && cd _build
cmake -DBRINGAUTO_INSTALL=ON -DBRINGAUTO_PACKAGE=ON ..
make install
```

### Package

To create a package, configure the project with CMake option BRINGAUTO_PACKAGE=ON and then create it using `cpack`.

```bash
mkdir _build && cd _build
cmake -DBRINGAUTO_INSTALL=ON -DBRINGAUTO_PACKAGE=ON ..
cpack
```