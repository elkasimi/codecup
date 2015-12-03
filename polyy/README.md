the script merge.py merge all files in one(player.cpp) to be submitted to codecup.
to  build the player:
make

to analyze a given position:
./player -a moves list

for example:
./player -a 1 2 6

the player use the Monte Carlo Tree Search Algorithm(MCTS) with Rapid Action Value Estimation(RAVE) together.
for a more information this paper was useful for me:
http://www.cs.utexas.edu/~pstone/Courses/394Rspring11/resources/mcrave.pdf

