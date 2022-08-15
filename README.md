## Colisseum
Documentation:

Data	Structures:
1) Hash	Table	called	GroupsTable based	on a	dynamic	array with	linked	list (Chain Hashing,	
regular) which	contains	pointers	to	objects	of	a	class	Group	(the	key	for	inserting	is	
trainingGroupID).	Class	Group	contains	following	fields:
          • trainingGroupID
          • Ranked	tree	based	on	Splay	tree	called	Gladiators which is sorted by gladiators’	
Score+ID (actually	contains	objects	of	class	Gladiator	that	are	compared	by	their	
Score+ID and	have	two	corresponding	fields:	Score	and	gladiatorID).	Each	vertex	
in	the	tree	also	contains	number	of	vertexes (sizeOfSubtree) and	sum	of	score	
(scoreOdSubTree) in	its	subtree.	
          • IndexInHeap	(group’s	index	in	minimum	heap	GroupsHeap).
          • Flag	isAbleToFight	which	is	true	when	group	can	fight	and	false	otherwise.
2) Minimum	heap	GroupsHeap based	on	almost	complete	tree	(array) which	is	sorted	by	
trainingGroupIDs	(key).	Also	heap	contains	pointer	to	GroupsTable.
3) Splay	tree	called	GladiatorsByID	which is	sorted	by gladiators’ ID	(key).

