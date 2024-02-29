# Daemon App - Tests

## Requirements
CMLib

or

GTest
```
apt install googletest
cd /usr/src/googletest
cmake CMakeLists.txt
make
make install

```
> When not using CMLib, configure the project with `-DBRINGAUTO_SYSTEM_DEP=ON`


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