
import os
import sys

iteration = sys.argv[1]

newfile = open("test.c", 'w+') 
with open ("test_template.c") as f:
    for line in f.readlines():
        if "#define ITER" in line:
            line = "#define ITER " + iteration + "\n"
        newfile.write(line)
newfile.close();

