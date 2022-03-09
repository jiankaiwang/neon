# Accelerating using NEON

## How to Start

* Build the OpenCV first.

```sh
git clone https://github.com/opencv/opencv.git
cd ./opencv
mkdir ./build
cmake ..
cmake --build .
```

## Examples

### Deinterleave

The deinterleave operation is to seperate the RGB channel into red, green, and blue channel.

* Setup the OpenCV build path to the `CMakeLists.txt` under the path `src`.

```txt
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../opencv/build)
```

* Build the whole source code.

```sh
# The images generated at the path `../../data`.
./build-linux.sh
```
