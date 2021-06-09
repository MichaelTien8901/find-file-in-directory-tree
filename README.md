# Find File In Directory Tree

## Overview 

   Search if there is file under directory tree.  This implementation skip special folder entries '.' , '..', and hidden files starting with '.'.  
   
   This is only tested for Linux.
   
## Test

Test script
```console
# cc ff.c
# ./a.out /usr man 10
found file path = /usr/bin/man
```
