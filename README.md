# Deriving complete Control flow graphs (CFG) of processor modules:

Here, we have to make a control flow graph for verilog code. Control flow graph is a relation between two operations
in a program such that one operation will be executed after the other. The main goal is to make mapping of the state
in the transition state of the verilog program by the control graph path producing a path dependency graph. 


## Implementation:

We have implemented the given task in C++ language.

To implement this, we have break this problem into control blocks as visualization for large code is very difficult.
So firstly, we have analyzed many verilog codes and noted down the repeated blocks. We have found six repeated control
blocks. After that, we have seperately find out control graph for each control block.  

1. If, else if, else statement : There are 4 types of If, else if, else statements. The types and its control flow implemented in the code is explained below:

  a) A single if statement: If the if condition is true, the control flow will enter the if statement block, else it will direct outside the if statement block. 
  
  b) if and else statements used together: If the if condition is true, the control flow will enter the if statement block, else it will enter the else statement block.
  
  c) if and else if statements used together: If the if condition is true, the control flow will enter the if statement block, else it will check the first else if statement.
  If there are multiple else if statement blocks, then for each else if statement, if the condition is true, it will enter the block, else it will check the next else if statement.
  For the last else if statement, if the condition is true, it will enter the block, else it will direct outside that block.
  
  d) if,else if and else statements used togehter: If the if condition is true, the control flow will enter the if statement block, else it will check the first else if statement.
  If there are multiple else if statement blocks, then for each else if statement, if the condition is true, it will enter the block, else it will check the next else if statement.
  For the last else if statement, if the condition is true, it will enter the block, else it will enter the else statement block.

2. switch case statement : For swith case statement, we compare the keyword with all the possible cases. If any of the case is satisfied, the control flow will enter the block of that particular case, else it will enter the default case block.

3. for loop : The control flow of for loop goes from that line to the next line. Then the block inside the for loop runs and then the control flow again jumps back to the first line.

4. while loop : The control flow of while loop goes from that line to the next line. Then the block inside the while loop runs and then the control flow again jumps back to the first line.

5. repeat loop : The control flow of repeat loop goes from that line to the next line. Then the block inside the repeat loop runs and then the control flow again jumps back to the first line.

6. forever loop : The control flow of forever loop goes from that line to the next line. Then the block inside the forever loop runs and then the control flow again jumps back to the first line.



## Input format:

We are providing verilog code file in .txt file and we are reading the code line by line. 
So to read that verilog code in text file, we have to save the input file at the same location as the .cpp file.
We than read the input file line by line using the fstream class. We considered each line of code as a single string.

As testcases, we are using 3 verilog codes in .txt file:
1) Traffic_light_controller
2) Case_1
3) Tic_Tae_Toe_Game


## Output format:

So in output, we are printing edges of control flow graph.
We are then using graphviz to visualize the graph.

Steps to visualize the control flow graph:

1. add a graphviz(dot) extension in vs code.
2. run the given code(c++).
3. Add a new file in vs code with name graph.dot.
4. Then paste the below code in graph.dot file.
5. digraph G{  
    node[style=filled, color=cornflowerblue, fontcolor=white, fontsize=10, fontname="Helvetica"]
    edge[arrowhead=vee, arrowtail=inv, arrowsize=.7, color=maroon, fontsize=10,fontcolor=navy]
    //paste the output here obtained from runnning the c++ code.

}
6. To generate the .svg file of control flow graph, press Ctrl+Shift+V.

The output of the 3 input files is given as .svg files of the control flow graph:
1) Traffic_light_controller_CFG
2) Case_1_CFG
3) Tic_Tae_Toe_Game_CFG








