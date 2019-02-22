Directions for compilation and execution on OSU flip servers: 

Step 1: Compile project using makefile
make -f imp2make

Step 2: Execute project
./imp2.exe

After this, the program will have read in "imp2input.txt" and will output results to "imp2output.txt"

The output can be validated by running:
python checker.py

New inputs can be generated using: (will overwrite imp2input.txt)
python generate.py