# Duong_CSCI2270_FinalProject
Final Project: Redbox 101

This project's purpose is to allow management and inquiry in a movie database.
The project will input a list of movies and create a binary search tree.
Each Movie Node:
	IMBD Rank
	Title
	Year
	Quantity
	parent
	leftChild
	rightChild
	nextRank
	prevRank


The tree allows: 
	insertion of a new movie
	deletion of a movie
	search of a specific movie
	renting of a specific movie
	counting the number of movies

Each node will also be doubly linked based on their IMBD RANK.
From head to tail will be #1 Movie to the last ranked movie.
The linked list will have the same operations as the tree.

The Nodes will also be linked in a graph. They will be linked by genre such as
horror, fantasy, etc. So if the user wants to know movies related to one such movie,
the graph will allow display of related movies. 
