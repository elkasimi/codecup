files = (
	'polyy.h',
	'position.h',
	'tree.h',
	'ai.h',
	'polyy.cpp',
	'update.cpp',
	'random_move.cpp',
	'random_neighbour_move.cpp',
	'random_joint_move.cpp',
	'random_elsewhere_move.cpp',
	'position.cpp',
	'attacking.cpp',
	'defending.cpp',
	'heuristic.cpp',
	'tree.cpp',
	'ai.cpp',
	'main.cpp'
)
s = ''
for f in files:
	s += '#line 1 "%s"\n' %f
	lines = open(f, 'r').readlines()
	for line in lines:
		if line.find('#include') == -1 or line.find('"') == -1:
			s += line
	s += '\n'

f = open('player.cpp', 'w')
print >> f, s
