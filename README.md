# MNXB11-project-template
# About
This folder contains a skeleton for your project that you can use as
inspiration. Once you get started, do feel free to go ahead and replace this
README file with one representing your project.

# Directory structure

The base directory here contains your "main" file, i.e. the C++ file that you
will be using as your starting point in your project. The code in this file should ideally be short and just make use of the functionality that you've
prepared in your other translation units. The majority of your code should be placed in  the two folders where you define your translation units, `src/` and `include/`. 

Do remember to add your include guards to your header files, otherwise the compiler will
get multiple definitions if you end up loading two source files that include the
same header.

In the template you can find a small translation unit called Example (in [src/Example.cxx](src/Example.cxx) and [include/Example.h](include/Example.h)) that shows some commented reminders of how the syntax for some C++ constructs work. Feel free to use this as a reference to remind yourself of how to do something while working on it but make sure to remove it from your final project version!

There is a demonstration of a toy project you can use for inspiration at [EinarElen/MNXB11-project-demo](https://github.com/EinarElen/MNXB11-project-demo). You should not copy code from this repository. There are some intentional bugs hiding in there, see if you can spot them. 

We have also included three special files in the base of the repository 
- [.gitignore](.gitignore)
  - This file contains regular expressions that git tells git that it shouldn't add certain file to your repository. 
  - Your git repository should generally not contain binary files like object files or executables nor should it contain build artefacts like external libraries. 
- [.clang-format](.clang-format)
  - This file holds the configuration for the clang-format tool that you can use to format your code consistently 
  - It is a good idea to keep your code formatted in a consistent manner, especially when working in groups but doing it manually is a waste of your time. Use a tool for it!
  ```
  # Show what the src/Example.cxx file would look like if formatted
  clang-format src/Example.cxx 
  # Carry out the formatting in the file directly 
  clang-format src/Example.cxx -i
  ```
  - The `.clang-format` file holds the configuration that clang-format will use to determine how to format your code. By default, it will be formatted according to Google's style but you can pick any that you like from https://clang.llvm.org/docs/ClangFormatStyleOptions.html
- [rootlogon.C](rootlogon.C)
  - This file contains code that ROOT will execute automatically whenever you start it, a good place to place general style choices you want to make or anything else you always want to run! 
  - Be careful to not include anything that depends on your particular machine here (e.g. absolute paths)
# Building the project

The [datasets](datasets) folder contains open data from SMHI and a README.md with further information about it.


We have included a basic Makefile here which should be familiar to you. It follows the same project structure that we have been using in the course. When you add a new translation unit to the project, you have update the dependencies in the Makefile. 

By default, the `all` target will be run which 
- Compiles any `.cxx` files in the `src/` directory into object files 
- Compiles `main.cxx` and links with all the object files in `src/`

You can run the `clean` target to remove any object files that have been produced as well as the `main` executable.

## Adding external software libraries

If you want to make use of external software libraries with your project, you
will always have to tell the tool that builds your project. The Makefile included in this template will pick up any header files in the external/include directory and look for libraries in external/lib and external/lib64 so if you use external as your installation directory, you only need to add the corresponding `-l` flag to the linker.

Here's an illustration of the typical process to add a (CMake based) external library
``` sh
# Clone or download the library you want to use 
git clone https://somerepository.com/alibrary alibrary # The last argument determines what the directory will be called

mkdir build/alibrary -pv # -p will tell mkdir to create the build/ directory if it doesn't already exist 
# Go into the build directory
cd build/alibrary 
# Look up the documentation for the library to find out if there are any additional flags you need for CMake 

# This command tells CMake to configure the build directory based on the source code in the ../../alibrary folder and to install the resulting headers and library files into ../../external
cmake ../../alibrary -DCMAKE_INSTALL_PREFIX=../../external 
# Build and install! Use -jN to launch N jobs
make -j8 install # If you are on an 8-core machine
```

Make sure to document how to do this for any library you choose to use!

Have fun!
