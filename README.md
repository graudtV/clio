# clio

## Overview
Presently ***clio*** (**c**ommand **l**ine **i**nput-**o**utput library) is a helper tool for creating interactive command line applications. But maybe it will be somehow extended in the future for other purposes (or maybe not, who knows)

## Requirements
- C++17
- Boost

## Build & Install
```bash
mkdir build && cd build
cmake ..
make                   # just build library
sudo make install      # build & install
make example           # build examples
```

## Using clio in your project
If _clio_ was installed in accordance with [Build & Install](#Build--Install) section, it can be found with cmake:
```cmake
find_package(clio REQUIRED)
target_link_libraries(your-target-name PRIVATE clio)
```
The last line automatically setups all necessary _clio_ include directories and libraries for your target
