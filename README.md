# Get Next Line

## Introduction
The **Get Next Line** (GNL) project is an implementation of a function that reads a line from a file descriptor. This function is useful for reading files line by line without loading the entire file into memory.

## Table of Contents
- [Features](#features)
- [Function Prototype](#function-prototype)
- [Implementation Details](#implementation-details)
- [Compilation](#compilation)
- [Usage](#usage)
- [Testing](#testing)
- [License](#license)

## Features
- Reads from a file descriptor line by line
- Manages multiple file descriptors simultaneously
- Handles any buffer size
- Efficient memory allocation

## Function Prototype
```c
char *get_next_line(int fd);
```
- **fd**: The file descriptor to read from.
- **Returns**: The next line from the file or `NULL` if EOF or an error occurs.

## Implementation Details
- Uses a static buffer to store data between function calls.
- Reads chunks from the file using `read()` and stores them in a buffer.
- Extracts and returns a full line, handling newline characters correctly.
- Manages memory efficiently to prevent leaks.

## Compilation
To compile `get_next_line.c` into a static library:
```sh
gcc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
ar rcs libgnl.a get_next_line.o get_next_line_utils.o
```

## Usage
Include `get_next_line.h` in your project and link against the compiled library:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd))) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

Compile with:
```sh
gcc main.c -L. -lgnl -o gnl_test
```

## Testing
You can test the function using:
```sh
echo -e "Hello\nWorld\n" > test.txt
./gnl_test
```
Expected output:
```
Hello
World
```

## License
This project is open-source and can be used for educational purposes.

