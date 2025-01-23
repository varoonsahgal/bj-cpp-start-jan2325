This project has a `CMakeLists.txt` file and want to build and run the project, follow these steps:

### 1. **Install CMake (if not already installed)**
Ensure that CMake is installed on your system. You can check by running:

```bash
cmake --version
```

If not installed, download it from [CMake's official website](https://cmake.org/download/) or install it using a package manager (`apt`, `brew`, `choco`, etc.).

---

### 2. **Create a Build Directory**
It is recommended to create a separate build directory to keep the generated build files separate from your source files.

```bash
mkdir build
cd build
```

---

### 3. **Generate Build Files**
Run CMake to generate the build files:

```bash
cmake ..
```

- The `..` points to the directory containing your `CMakeLists.txt`.
- If your `CMakeLists.txt` has specific configurations (like `Debug` or `Release`), you can specify them:
  ```bash
  cmake -DCMAKE_BUILD_TYPE=Release ..
  ```

---

### 4. **Build the Project**
Use the generated build files to compile your project. Typically, you run:

```bash
cmake --build .
```

You can also specify a target if there are multiple executables or libraries defined in your project:

```bash
cmake --build . --target <target_name>
```

---

### 5. **Run the Executable**
Locate the compiled executable in the build directory (usually in a `bin/` or similar folder, depending on your `CMakeLists.txt` configuration) and run it.

```bash
./<executable_name>
```

---

### 6. **Optional: Debugging or IDE Integration**
- **Debugging:** If you need to debug, you can use tools like `gdb` or an IDE.
- **IDE Integration:** Many IDEs (like Visual Studio, CLion, and VS Code) support CMake projects directly. Open your project in the IDE and let it configure the build system.



To create a reusable Visual Studio solution (`.sln`) file from a `CMakeLists.txt` file, follow these steps:
---


### 1. **Install Required Tools**
Ensure you have the following installed:
- **Visual Studio** (2019 or later, with C++ development tools installed)
- **CMake**

---

### 2. **Configure CMake to Generate a Visual Studio Solution**
Run the following command in your terminal (from the root directory of your project, or a dedicated `build/` directory):

```bash
cmake -G "Visual Studio 17 2022" ..
```

Replace `"Visual Studio 17 2022"` with the version of Visual Studio you're using:

| Visual Studio Version | Generator Name                  |
|------------------------|---------------------------------|
| VS 2022               | `Visual Studio 17 2022`        |
| VS 2019               | `Visual Studio 16 2019`        |
| VS 2017               | `Visual Studio 15 2017`        |

### Optional: Specify 64-bit Architecture
If you want to build a 64-bit solution, append `Win64` to the generator name:

```bash
cmake -G "Visual Studio 17 2022" -A x64 ..
```

---

### 3. **Open the Solution File**
CMake will generate a `.sln` file in the directory where you ran the command. You can find it with the name of your project or as the default `ALL_BUILD.sln`.

- Open the `.sln` file in Visual Studio.
- All the targets (executables, libraries) defined in your `CMakeLists.txt` will appear as projects in the solution.

---

### 4. **Reuse the Solution**
You can open the `.sln` file directly in Visual Studio for future development. As long as the source files or `CMakeLists.txt` don't change, you won't need to re-run `cmake`.

---

### 5. **If You Make Changes**
If you update your `CMakeLists.txt` or add new source files, regenerate the solution by running:

```bash
cmake .. -G "Visual Studio 17 2022"
```

This will update the `.sln` file without overwriting your existing settings in Visual Studio (e.g., breakpoints, configuration).

---

### 6. **Automating the Process**
For ease of reuse, you can write a simple batch script (`generate_solution.bat`) to automate the process:

```bat
@echo off
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
echo Solution generated in build directory.
pause
```

Run the script whenever you need to regenerate the solution.
