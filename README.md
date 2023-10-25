# simdmark
`simdmark` checks the CPU for available SIMD extensions and then runs tests on it.

# Usage
Running the program with no arguments will run all possible tests automatically.
By default, all tests are run with `10000` iterations each.

Name | Description
--- | ---
`-h --help` | Prints the help string.
`-e --extensions` | Prints all available SIMD extensions.
`-v --version` | Prints the version of `simdmark`.
`-i --iterations` | Specifies the amount of iterations to run for each test.

# Tests
ID | Description
--- | ---
0 | Arithmetic operations on packed vectors.
1 | Arithmetic operations on scalar vectors.

# Building
> _Tested on openSUSE Tumbleweed with gcc and clang_

- Run `cmake build .`
- Then, inside the resulting directory, run `cmake --build .`
