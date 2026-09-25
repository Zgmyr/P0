## P0
Zachary Gmyr<br>
CS4280 - Program Translation Project

### Overview

This program constructs a binary search tree (BST) from given input data, either through standard input (keyboard/redirection) or passed as an argument using a file name. Invoking P0 with a file name argument requires a `.fs26s2` extension for the input file (not included when invoking). Two files are output as a result, displaying a compact view of both preorder/postorder traversal of the BST.

Validation is used for the input data to filter digit-only, nonnegative integer tokens. Invalid tokens are rejected, and duplicates of a valid datum are ignored when the tree is built. The number of digits in a datum (ignoring leading zeros) is used for the BST key, and unique datums are preserved in the order by which they appear through input. Sanitized data is stored in a generated temporary file (valid_data.fs26s2), which can be removed using `make clean` (see compilation & usage).

### Compilation & Usage

Use `make` in CLI to build P0 using the provided makefile.

Use `make clean` to remove compiled objects, intermediate 'valid_data.fs26s2' file, .preorder/.postorder output files, and target executable.

When P0 is invoked without an argument, standard input (keyboard/redirection) is used to read data. Otherwise, a file argument can be provided for input.

1. Invoking `./P0` prompts the user to enter data manually through the terminal and signal EOF when finished. For Windows, EOF can be signaled on a new line using `CTRL+Z` then `ENTER`. On Linux, EOF can be signaled using `CTRL+D`.

2. P0 can also be invoked by redirection with a file containing input data.

```
./P0 < input_data_file.fs26s2    // including extension
```

3. P0 can also be invoked with a file argument `./P0 filename`, where `filename` is the base name of an input file using the extension `.fs26s2`:

```
./P0 input_data_file    // for input_data_file.fs26s2
```

### Side Notes

* Input is validated as digit-only, nonnegative integer tokens; datums like `-34` or `+8` are rejected.
* Leading zeros are ignored only when determining a datum's key, though the original datum (and input order) is still preserved. As an example, a node may contain `=2: 040 40 0040`.
* A special case occurs when a datum consists entirely of zeros. If multiple variants of `0` are given with one or more leading zeros (e.g. `00 0 000 00`), they all receive key=1 after leading zeros are ignored for key calculation. Their original forms are preserved, so a node may contain `=1: 00 0 000`. This differs from input such as `777 7 77`, where no leading zeros are present, so the keys are simply the respective digit counts 3, 1, and 2.