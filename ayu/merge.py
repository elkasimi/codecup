files = [
	"Common.h",
	"Data.h",
	"Queue.h",
	"Stack.h",
	"Group.h",
	"Position.h",
	"Util.h",
	"IO.h", 
	"Timer.h", 
	"Tree.h",
	"HashSet.h",
	"OpeningBook.h",
	"AI.h",
	"Data.c",
	"Queue.c",
	"Stack.c",
	"Group.c",
	"Position.c",
	"Util.c",
	"IO.c", 
	"Timer.c", 
	"Tree.c", 
	"HashSet.c", 
	"OpeningBook.c", 
	"MCTS.c",
	"AI.c", 
	"main.c"]

fout = open("Mamay.c", "w")

for f in files:
	lines = open(f, "r").readlines()
	for line in lines:
		if line.find('#include "') == -1:
			fout.write(line)

fout.close()
