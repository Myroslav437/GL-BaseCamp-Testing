# GL-BaseCamp-Testing
## _Technical task to GlobalLogic C++ BaseCamp 2022_

### About:
This cross-platform utility can search for a file by its name from a specified directory. It can be built for any OS which supports ```g++``` compiler of version 9 or higher.
It is implemented using the standard ```C++``` library only and majorly relies on the ```C++17``` ```<filesystem>``` library.

## How to build:
First, install the required ```g++``` compiler of version 9 or higher. Then just use the ```make``` utility to build the app for your system.

### How to use:
#### On linux:
    ```./fsearcher <filename> <startFolder>```

#### On Windows:
    ```fsearcher.exe <filename> <startFolder>```

where 
> ```<filename>```  - the name of the file that you would like to find
> ```<startFolder>``` - the folder from which searching is started (your root folder by default)

### How it works:
This program uses multiple threads (8 by default) to perform the recursive directory search from the starting folder.
All searching logic is implemented in a separate static library so it can be used in other projects
The class diagram of the program:
![Alt text](/Class\ diagram.jpg?raw=true "Class diagram")