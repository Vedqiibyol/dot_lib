# dot_lib

A collection of STB-like header files for C, made in pure C. ~~there's no C++,
whatever Github says~~

It works for both UNIX-like and Windows, and does not rely on the C standard
library.

# Install

To install the libraries, first download the Repo either by downloading the Zip
file of the Repo, or by using the command bellow

```
git clone https://github.com/Vedqiibyol/dot_lib.git
```

Then running the appropriate script for your platform.

If you want to place the files in a specific directory, just copy them there,
or specify the path as the only argument for the script.

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

# Note

You may find in some headers a few lines with macros and the following code

```C
#if defined (__kohr_compatibility)
```

These few lines are here in advance for a future project of mine, if you wish
to include these files for your programming language library or any other
language really, just try to find a way to create that variable, it will remove
prefixes such as `str_` or `mem_` from the function in certain files, you may
then wrap them into namespaces.

Kohr is a future project, this feature allows the use of putting incldue files
into a namespace directly like so: `include_c "str.h" -> str`.
