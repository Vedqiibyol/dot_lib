# .Libs

A collection of STB-like header files for C, made in pure C.

It works for both UNIX-like and Windows, and does not rely on the C standard
library.

# Install

To install the libraries, first download the Repo either by downloading the Zip
file of the Repo, or by using the command bellow

```
git clone https://github.com/Vedqiibyol/.libs.git
```

Then running the appropriate script for your platform.

If you want to place the files in a specific directory, just copy them there,
using the scripts will simply put the files into your include path.

# Use

Usage is pretty simple, just include the files you need just as if you were
using any file from the C standard library.

There is also a documentation on each and every file, functions and constants
at your disposal, you can check the library version number by including
`.libs_info.h` and printing `DOTLIBS_VERSION`.

If you have put your files in somewhere else than your include path, do not
forget to provide the path to your compiler when compiling:

```
clang -Ipath/to/the/headers your_file.c
```
