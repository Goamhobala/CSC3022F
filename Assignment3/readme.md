The general format of the command should look as follows:
```
./findcomp [options] <inputFileName>
```

* Note that the default make run command is:
```
```

The list of options is as follows:
-m <int>: minimum size for a connected component
-f <int> <int>: Filter connected components. Keep only those that have sizes within the range provided
-t <int>: Set a threashold value for connected components
-p: to print out the data (id and size) of each connected component
-w <string>: write out the connected components into a pgm file with the specified file name

