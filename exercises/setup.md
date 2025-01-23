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

Let me know if you encounter any specific errors or need help with a particular step!
