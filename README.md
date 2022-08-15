# Colisseum
Dry	Part
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
Assumptions:
1) Splay	Tree	is	implemented	as	it	is	described	in	the	given	presentation in	the	previous	dry	
assignment.	So,	operations	Insert,	Delete,	Find take	O(logn)	amort.	Each	tree	also	
contains	field	NumberOfNodes,	which	is	changed	each	time	operations	insert or	delete	
in	map	are	called	- O(1).	
2) Ranked	tree	based	on	Splay	tree	is	implemented with	the	same	concept	as	was
described in	the	class	as	they	are	both	BSTs.	So,	operation	Select(x) is	done	as	we	saw in	
the	class.
3) �"#$%& always	equal	or	less	than	� because	each	gladiator	can	belong	maximum	to	one
group.	Hence,	O(log�"#$%&)	=	O(log	m),	so	we	use	it	further.	
4) Doing	something	like	insert/find/...	a	gladiator	by	Score+ID means	increasing	order	of	
score and	in	case	two	gladiators	have	the	same	score decreasing	order	of their ID	
number.	
5) Minimal	Heap	is	based	on almost	complete	tree (implemented	as	array) as	it	was	
described in	the	class. Operation MakeHeap takes	O(n),	while Insert,	DecKey	and	
DelMin	take	O(Ologn).	Operation	FindMin	take	O(1).	So	we	use	it	futher.
6) We implement hash-table with Chain Hashing based on dynamic array in order to use	
Simple	Uniform	Hashing	Assumption.	So	as	we	learned	in	the	class,	operations	Insert
and	Find	have	amortized	time	complexity	O(1)	average	on	input.	Also HT	contains	field	
numberOfElements	which	represents	number	of	groups	in	the	system.
7) Every	object	of	class	Group	contains	its	index (IndexInHeap) in	min	heap	(array).	Each	
time	we	need	to	swap	elements	in (in	case	of	SiftUp/SiftDown) we	also	change	field	
IndexInHeap appropriately with	a	help	of	pointer	to	HT	GroupsTable	in	heap.	It	takes	
O(1).
Functions:
����: First	of	all,	we	need	to	check	whether	parameters	are	valid	– O(n) (checking	all	elements	
in	given	array	of	size	n).	Afterwards,	we	create	Hash	Table	GroupsTable and	insert	pointers	to	n	
object	of	class	Group with	all	given ID	numbers – O(n) (notice	that	because	of	given	assumption
that	all	groups’ IDs	are	unique,	each	operation	insert	to	HT	takes	O(1) amort.	which	is	in	total	
O(n) in	the	worst	case).	Then	we	create	minimal	heap	GroupsHeap	which	contains	all	given	
groups’ ID	numbers	and	pointer	to	already	created	HT	GroupsTable	– O(n) (MakeHeap(n)).	
�������:� � �� �ℎ� ����� ����.
����������������: First	of	all,	check	if parameters	are	valid	– O(1).	After	that	we	check	
whether	group	with	given ID	already	exists	in	the	system	– O(1) average	on	input. amort.	
(operation	Find	in	HT	GroupsTable).	If	yes,	return.	Otherwise,	we	create	new	object	of	class	
Group with	such	ID and	insert	it	in	HT	GroupsTable – O(1) average	on	input amort.;	with	initial	
index	in	heap	equalled to	current	number	of	groups	in	the	system (access	to	
NumberOfElements	in	HT	– O(1)). Then	we	add	given	group’s	ID	to	min	heap	GroupsHeap	–
O(logn) (insert	in	min	heap).	
�������:� log � ������� �� ����� �����.
������������:	First	of	all,	check	if parameters	are	valid	– O(1).	After	that	we	check	whether	
group	with	given parameter	trainingGroupID	already	exists	in	the	system	– O(1) average	on	
input. amort.	(operation	Find	in	HT	GroupsTable).	If	no,	return.	Otherwise,	we check	if	in	the	
system	exists	gladiator	with	given	gladiatorID	– O(logm) amort.	(operation	Find	in	Splay	tree).	If	
yes,	return.	Else	we	insert	given	gladiatorID to	GladiatorsByID - O(logm) amort.	(operation	
Insert in	Splay	tree). Then	we	add by	Score+ID	(given	parameters) to	found	group	new	created	
object	of	class	Gladiator	(as	it’s	clear	with	given	parameters	score	and	gladiatorID)- O(logm)
amort.	(operation	Insert	in	Ranked	Tree	based	on	Splay	tree).
�������:� log � ������� �� ����� �����.
����������������ℎ�:	Firstly,	check	if	parameters	are	valid	- O(1).	Afterwards for	each	group:	
we	check	whether	group	with	given parameter	trainingGroupID	already	exists	in	the	system	–
O(1) average	on	input. amort.	(operation	Find	in	HT	GroupsTable).	If	one	of	them	not	- return.
Otherwise, we	need	to	check	if	they	can	both	fight	– check	field	ableTofight	– O(1);	and	have	
enough	gladiators	– (access	to	Splay	Tree’s	field	NumberOfNodes	– O(1)).
If	yes,	we access	to	group's	Splay	tree	Gladiators	and	select element	with	index	
NumberOfNodes	 – k	 - O(logm),	as	we	learned	in	the	class.	Then we	count	sum	of	Score of	all	
gladiators	that	have	less	or	equal	score (let's	call	it	LessSum	for	ease;	these	are	all	elements	
which	are	less	than (NumberOfNodes – k + 1)ST gladiator)	- O(logm),	as	we	learned	in	the
lecture	5.	Root	contains	sum	of	all	gladiators’ score in	the	group,	so	we	can	just	decrease	it	by	
LessSum	and	get	needed	sum	of	the � most	powerful	gladiators	in	the	group - O(1).	
Then we	compare	results	for	two	groups	- O(1);	in	case	one	of	them	loses	(has	smaller result)	
we	do	following:
With	a	help	of	group’s	IndexInHeap we	call	function	DecKey in	GroupsHeap and	decrease	
element	(group’s	ID) in	GroupsTable to	-1 – O(logn).	After that, we	call	function	DelMin	and	
delete	group	that	lost the	fight	from	the	heap – O(logn);	as	we	know	that	all	groupsID	are	not	
negative	numbers. Not	forgetting set	Group’s	flag	ableToFight	to	false	and	IndexInHeap	to	-1 –
O(1) (these	two	actions	are	done	for	the	lost	Group	in	HI	GroupsTable).
�������:� log � + log � ������� �� ����� �����.
�������������������: :	Firstly,	check	if	parameters	are	valid	- O(1).	Afterwards we	call	
function	FindMin	in	min	heap	GroupsHeap	– O(1) and	return	received	value.	Notice	that	it	is	
indeed minimal group’s	ID among	all	groups	in	the	system	which	can still	fight	as	we	always	
delete	the	group	of	losers after	fight	from	GroupsHeap.
�������:� 1 �� �ℎ� ����� ����.
����: Firstly,	we	delete	min	heap	GroupsHeap (array) – O(1). Then	we	go	over	all	HT	
GroupsTable,	access	to	through	pointer	to	each	Group and destroy	it:	in	order	to	destroy	one	
Group	we	need	to	delete	recursively	its	Splay	tree	Gladiators	- � �"#$%& .	Afterwards,	we	
delete	recursively	system’s Splay	tree	GladiatorsByID	- � � .
�������: (� 1 + � �"#$%&X
Y
Z[\
) + � � + � 1 = � � + � � =
� � + � �� �ℎ� ����� ����.
Place	complexity:	
GroupsHeap	– � �
GroupsTable	(including	all	Gladiators	with	their	Splay	trees	Gladiators) – � � +
� �"#$%&X
Y
Z[\ = � � + � � = �(� + �)
GladiatorsByID	- � �
�������:�(� + �)
