SRC=                                   \
	polyy.h                            \
	position.h                         \
	tree.h                             \
	ai.h                               \
	polyy.cpp                          \
	update.cpp                         \
	random_move.cpp                    \
	random_neighbour_move.cpp          \
	random_joint_move.cpp              \
	random_elsewhere_move.cpp          \
	position.cpp                       \
	attacking.cpp                      \
	defending.cpp                      \
	heuristic.cpp                      \
	tree.cpp                           \
	ai.cpp                             \
	main.cpp

player: $(SRC)
	python merge.py
	g++ -Wall -g -O2 player.cpp -o player

clean:
	rm -f *.o *.exe player* *~

