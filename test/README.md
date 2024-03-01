# Daemon App - Tests

## Requirements
* CMLib
* GTest
```
apt install googletest
cd /usr/src/googletest
cmake CMakeLists.txt
make
make install

```
> When using BA_PACKAGER, GTest is automatically downloaded, else configure the project with CMake option 
> `-DBRINGAUTO_SYSTEM_DEP=ON`

## Build
```
mkdir _build_tests && cd _build_tests
cmake ../
make
```

## Run
```
./fleet_protocol_tests
```