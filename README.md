# CS213-Assignment2-VoleSimulator

CS213 Object-Oriented Programming Assignment 2 - Vole Machine Simulator with a
Qt Widgets graphical interface.

## Build and run

Install Qt 5 or Qt 6 with its Widgets development component, and CMake 3.16 or
newer. From the repository directory, run:

```sh
cmake -S . -B build
cmake --build build
```

If CMake cannot locate Qt, set `CMAKE_PREFIX_PATH` to the Qt installation
prefix (for example, the directory containing the `6.x` or `5.x` version
directory).

Run the generated `VoleSimulator` executable from the build directory (on
Windows, it is in `build/Debug` or `build/Release` when using a
multi-configuration generator).

### Open in Qt Creator

Open the repository's `CMakeLists.txt` using **File > Open File or Project**.
Do not open just the `.cpp` file as the project. When Qt Creator asks you to
configure the project, select a desktop kit whose Qt version and compiler
match (for example, **Qt 6.12.0 MinGW 64-bit**). Then build with **Ctrl+B**
and start it with the green Run button.

## Using the GUI

- Browse to a program text file and choose an even hexadecimal start address,
  then select **Load program**.
- Use **Run all** or **Step** to execute instructions and inspect the CPU,
  registers, memory, and screen output.
- Set an individual register or memory cell using hexadecimal values.
- Select **Reset** to clear the machine before loading another program.

Program files contain four hexadecimal digits per instruction. Blank lines and
lines whose first token starts with `;` are ignored.
