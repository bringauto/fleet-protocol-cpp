# Daemon App - Tests

## Requirements

GTest
```
apt install googletest
cd /usr/src/googletest
cmake CMakeLists.txt
make
make install

```

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