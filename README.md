# Colisseum
## About

## Documentation:

### Data	Structures:
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

### Functions:

1) **Init**: First of all, we need to check whether parameters are valid – O(n) (checking all elements in given array of size n). Afterwards, we create Hash Table GroupsTable and insert pointers to n object of class Group with all given ID numbers – O(n) (notice that because of given assumption that all groups’ IDs are unique, each operation insert to HT takes O(1) amort. which is in total O(n) in the worst case). Then we create minimal heap GroupsHeap which contains all given groups’ ID numbers and pointer to already created HT GroupsTable – O(n) (MakeHeap(n)). 
