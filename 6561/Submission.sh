#! /bin/sh

cat Common.h		\
	IO.h 			\
	RNG.h 			\
	Timer.h 		\
	Board.h 		\
	TTable.h 		\
	AI.h 			\
	IO.cc 			\
	RNG.cc 			\
	Board.cc 		\
	TTable.cc 		\
	Timer.cc 		\
	ExpectMax.cc 	\
	main.cc > Submission.cc

sed -i '/#include "/d' ./Submission.cc
