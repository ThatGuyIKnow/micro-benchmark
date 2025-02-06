
# MicroBenchmark

This project is a quick setup for a CPP benchmark. It's automatically sets up Google Benchmark and Google Test, along with a sample project. Included are VSCode/Codium tasks and launch files, relevant for quick debugging and testing.

## Prerequisites

- **CMake** 3.13 or higher
- **Git**
- **A C++20 compatible compiler** (e.g., GCC, Clang)
- **Internet connection** (for fetching dependencies)

## Setup Instructions

1. **Clone the Repository**

```bash
git clone https://github.com/ThatGuyIKnow/micro-benchmark.git
cd micro-benchmark
```
### Configure the Project with CMake

Specify the source file you wish to build:

```bash
cmake -S . -B build \
 -DSOURCE_FILE:STRING=your_source_file.cc \
 -DCMAKE_BUILD_TYPE=<"Debug" or "Release"> \
 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```
Replace your_source_file.cc with the filename of the source file you want to compile. The default is tree_compression.cc.

### Build the Project

You can build the project using the following command:

```bash
cmake --build build --target your_source_file
```
Replace your_source_file with the target name derived from the source file, which should be the filename without the extension.

### Running the Benchmarks

Once built, you can run the resultant executable directly from the build directory:

```bash
./build/your_source_file
```
Replace your_source_file with the executable name, which matches the source file name without the extension.

## Project Structure

CMakeLists.txt: Configuration file for CMake that manages the build process.

src/: Contains source files for various tree compression implementations.

benchmark/: Contains Git submodules for Google Benchmark and Google Test libraries.
Contributing


## Contributions are welcome! 

Please fork the repository and submit a pull request for any enhancements or bug fixes.

- Fork the repository.

- Create a feature branch: git checkout -b my-feature-branch

- Commit your changes: git commit -am 'Add new feature'

- Push to the branch: git push origin my-feature-branch

- Submit a pull request.
