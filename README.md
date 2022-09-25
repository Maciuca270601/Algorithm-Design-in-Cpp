Student: Maciuca Alexandru Petru
Group: 324CA
Homework: Gigel si Grafurile
Course: PA

# About the code

    The homework is divided in three problems, and there 
	is an additional problem.

## The implementation

    *Problem 1: Curatare*
		I complete all minDistances from all robots to all the dirty cells,
		and all minDistances from all the dirty cells to all the remaining
		dirty cells.

		This is helping me in bkt that generates all solutions because
		in order for a robot 'i'  to clean a dirty cell 'j', it has to 
		reach that specific cell and to perform the algorithm from that point.
		Because i am saving also all the minDistances from all dirty cells
		to the others remaining dirty cells, I can update robot 'i' distances
		without having to recalculate them over and over again.

		Once all dirty cells have been cleaned I compare the times of all
		robots and choose the biggest one so all roads can be completed by
		all robots. If my new solutio is better than my previous, I update
		the result.

		minDistance algorithm has been inspired from GeeksForGeeks and slightly
		modified to fit my problem.

	Complexity:  O((R * D * M * N) + (D^2 * M * N) + (R! * D ^ (D - 1)))
	,where: R = nr of robots
			D = nr of dirty cells
			M, N dimensions of the matrix
			first paranthesis is for the robot to dirty bfs
			second paranthesis is for the dirty to dirty bfs
			third paranthesis is for the bkt algorithm


	*Problem 2: Fortificatii*
		The begining of the program is the set up for a Dijkstra.
		My idea was to perform only one dijkstra from the capital to all
		the other cells so I had to modify the way the graph is created.

		If node1 is a simple city and node2 is also a simple city, there is
		a bidirectional road between them. If node1 is a barbarian and node2
		is a simple city then there is a single road from simple city to 
		barbarian city.

		Then I traverse all barbarian cities in order to find all of their
		neighbors and add the distances between those neighbors and 
		the capital + the distance between the barbarian city and the neighbor.

		Once I have completed my array, I have used a function that will
		distribute the towers in the graph. It pretty much tries to make
		the minimum of that array the biggest possible it can be.

		Dijkstra algorithm has been inspired from Lab 9 pseudocode.

	Complexity: O(N * E + b * b' +  counter ^ 2)
	,where: N = nr of cities
			E = nr of roads
			b = nr of barbarian cities
			b' = nr of simple cities that are neighbors of the barbarian cities
			counter = nr of values in the auxilary array

	*Problem 3: Beamdrone*
		The begining of the program is the set up for a slightly modified BFS.
		It traverses the same number of nodes so it has the same complexity as
		minDistance from first problem but it tries to reach all cells from
		rows and columns before reaching a wall, instead of just one cell.

		All cost remain 0, and if there is any perpedincular road, the cost
		adds 1 to its initial value.

		minDistance algorithm has been inspired from GeeksForGeeks modified 
		to fit my problem.
	
	Complexity: O(M * N)
	,where: M, N dimensions of the matrix

	*Problem 4: Curse*
		The begining of the program is the set up for a topSort.
		The way I extract the dependencies is by checking everytime
		that a change between trainings was not previously selected.

		TopSort algorithm has been inspired from Lab10 oficial solutions.

	Complexity: O(((A - 1) * M) + (N * A))
	,where: A = nr of trainings
			M = nr of cars
			N = nr of roads
			first paranthesis is for the topSort
			second paranthesis is for the extract dependencies algorithm
		
### DIFFICULTIES
    I had some difficulties with solving the problems withing the time limit.
	The algorithm in general was correct but extremely slower on bigger tests.
