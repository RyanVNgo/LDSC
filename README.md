# LDSC - Linked Data Structures for C
A library providing a collection of standard data structures.
## Current Data Structures
- Linked List
- Stack
## Requirements
- `gcc`
- `make`
## Installation
1. Clone the respository:
   
   ```sh
   git clone https://github.com/RyanVNgo/LDSC.git
   ```
   
3. Change to project directory:
   
   ```sh
   cd LDSC
   ```
   
5. Compile library:
   
   ```sh
   make
   ```
6. Compile you're project with the appropriate header files in the `include` directory along with the `libLDSC.a` static library file.

### Note
A precompiled `libLDSC.a` file is provided in the repo (may change in the future):
- **Compiler Version**: GCC 11.4.0
- **Architecture:**: x86_64
- **GNU C Library Version**: 2.35
- **Operating System Version**: Ubuntu 22.04.4 LTS on Windows 10 x86_64
- **Build Configuration**: -std=11 -Wall -Wextra -Werror
