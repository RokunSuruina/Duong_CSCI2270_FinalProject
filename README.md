This Final Project stores movies from a text file named "Assignment5Movies.txt".
Each movie in the text file contains: IMBD rank, title, year, quantity, genre(s). Note if there are multiple genres they are seperated by a whitespace.
In essence this project allows the user to manager a movie store, where the user can find a desired movie, rent a movie, add to the inventory, delete from the inventory, see what movies are related to another movie, and count how many movies are available.
The movies are first inserted into a binary search tree. Each movie node has: the IMBD rank, title, year, a pointer to the left child, a pointer to a right child, a pointer to a parent, a pointer to the next rank (next higher IMBD rank), and a pointer to the previous rank (previous lower IMBD rank). The pointers to the next or previous rank allows the nodes to be connected in a linked list which is sorted by its rank, such as the head being #1 movie and the tail being the lowest rank movie.
The movies are also instanced in a graph which displays which movies are related to eachother by genre.
================== INSTRUCTIONS====================
1) Please download: < main.cpp >, < Assignment5Movies.txt > by clicking the green "Clone or Download" bottom on the right hand of the repository. The files should be downloaded in a .zip file.
2) Extract the entire folder to an easy to access location (like your Desktop)
3) Open CodeBlocks IDE, go to File->open, find the folder (where you put it) and open < main.cpp >
4) Build and Run the file.
You may also choose to run this in the terminal, in which case:
Repeat 1 & 2), open the directory that contains the folder and use command "g++ -std=c++11 main.cpp -o Redbox" then "/.Redbox"

You should get a menu with 10 options.
1. Find a movie
2. See Related Movies
3. Rent a movie
4. Print the Inventory
5. Print Movies by Rank
6. Print Edges
7. Add New Movie
8. Delete a movie
9. Count the movies
10. Quit

The program will be expecting an input. THIS INPUT MUST BE AN INTEGER 1-10 OR THE PROGRAM WILL CRASH

Inputting the corresponding integer will give the corresponding option.
1. Find a movie ---- selecting this option will prompt you to enter the title of a movie. THIS MUST BE A STRING OR THE PROGRAM WILL CRASH. If you enter a title, and it is in the database, the screen will provide information on that movie. If you enter a title and the movie is not in the database, it will return "Movie not found". After the corresponding display, it will return to the menu to select another option.

2. See Related movies ----- selecting this option will prompt you to enter the title of a movie. AGAIN THE INPUT MUST BE A STRING OR THE PROGRAM CRASHES. If you enter a title and it's in the database, it will return you a list of movies that are related to the entered movie by one or more genres. If the movie you enter is not in the database, it will return you an empty list.

3. Rent a movie --- selecting tis will prompt you for a title. MUST BE A STRING. If the movie is in the database, you will "rent" the movie, decreasing its quantity by 1. If the quanity becomes 0, it will delete the movie. If you enter a movie not in the database, it will return "Movie not found".

4. Print the Inventory ---- selecting this will print the movies in alphabetical order along with the quantity of that movie that is available.

5. Print Movies by Rank ---- selecting this will print the movies based on their IMBD rank, printing from highest rank to lowest rank

6. Print Edges ---- selecting this will print the movie graphs. This option is like option 2, but for all movies at once. Again this shows movies relating to other movies by one or more genres.

7. Add a New Movie ---- selecting this means you can add to the data base. After selecting, the program prompts a title, then an IMBD ranking, a year, the quantity being added, and the genres of the movie. The movie will be appended to the tree, inserted into the Linked List, and added to the graph. You can see where the movie is by options 4, 5, or 6.

8. Delete a Movie ---- selecting this deletes from the database. The program will prompt for a title, and that will delete the movie from the tree, linked list and graph. 

9. Counts the Movies ---- selecting this will count the number of movies avaiable to be selected.

10. Quit ---- exits the program

Known issues: 
---sometimes the counting function is wrong, when you delete a movie for example "The Dark Knight", it reportes 44 movies remain, instead of 49.
--- when quitting the program does not close smoothly. I'm not sure why.
