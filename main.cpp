#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

// Node is Movie
struct Movie
{
    int IMBD;
    string title;
    string year;
    int quantity;
    Movie *parent;
    Movie *left;
    Movie *right;
    Movie *nextRank;
    Movie *prevRank;
    // Node Constructor
    Movie(int initIMBD, string inittitle, string inityear, int initquantity, Movie *initparent=nullptr,
          Movie *initleft=nullptr, Movie *initright=nullptr, Movie *ininext = nullptr, Movie *iniprev = nullptr):
               IMBD(initIMBD), title(inittitle), year(inityear), quantity(initquantity), parent(initparent),
                left(initleft), right(initright) {};
};

// Movie class

class Movielist
{
    private:
        Movie *root;
        Movie *head;
    public:
        // Movie Tree Functions
        Movielist();
        ~Movielist();
        Movie *initialroot();
        Movie *buildtree(int ranking, string newtitle, string newyear, int newquantity);
        void printtree(Movie *node);
        void searchMovies(string desMovie, int renting);
        Movie *deleteMovie(string desMovie, Movie *node);
        int countMovies(Movie *node);
        void deletetree(Movie *node);
        Movie *findminimum(Movie *node);
        void leftrotate(Movie *node);
        // Linked List Functions
        void insertLL(Movie *node);
        void printLL();
        void delnodeLL(string desMovie);

};

Movielist::Movielist()
{
    root = nullptr;
    head = nullptr;

}

Movielist::~Movielist()
{


}

Movie *Movielist::initialroot()
{
    return root;
}

Movie *Movielist::findminimum(Movie *node)
{
    Movie *walker = node;
    while (walker->left != nullptr)
    {
        walker = walker->left;
    }
    return walker;
}

Movie *Movielist::buildtree(int ranking, string newtitle, string newyear, int newquantity)
{
    Movie *newnode = new Movie(ranking, newtitle, newyear, newquantity);
    insertLL(newnode);
    if (root == nullptr)
    {
        root = new Movie(ranking, newtitle, newyear, newquantity);
    }
    else
    {   // use walker to traverse the tree
        Movie *walker = root;
        while ( walker != nullptr)
        {
            if ( strcmp(newtitle.c_str(), walker->title.c_str() ) < 0 )
            {
                if (walker->left == nullptr)
                {
                    walker->left = newnode;
                    newnode->parent = walker;
                    break;
                }
                else
                {
                    walker = walker->left;
                }

            }
            else
            {
                if (walker->right == nullptr)
                {
                    walker->right = newnode;
                    newnode->parent = walker;
                    break;
                }
                else
                {
                    walker = walker->right;
                }

            }

        }
    }
    return root;
}

void Movielist::printtree(Movie *node)
{
    if (node != nullptr)
    {
        if( node->left )
        {
            printtree(node->left);
        }
        cout << "Movie: " << node->title << " "<< node->quantity << endl;

        if( node->right )
        {
            printtree(node->right);
        }
    }
    else
    {
        return;
    }
}

void Movielist::searchMovies(string desMovie, int renting)
{
    int found = 0;
    Movie *walker = root;
    while ( walker != nullptr )
    {
        if ( strcmp( desMovie.c_str(), walker->title.c_str() ) == 0 )
        {
            found = 1;
            if (renting == 1)
            {
                cout << "Movie has been rented" << endl;
                walker->quantity = walker->quantity - 1;
            }
            cout << "Movie Info" << endl;
            cout << "===========" << endl;
            cout << "Ranking: " << walker->IMBD << endl;
            cout << "Title: " << walker->title << endl;
            cout << "Year: " << walker->year << endl;
            cout << "Quantity: " << walker->quantity << endl;
            if (walker->quantity == 0)
            {
                deleteMovie(walker->title,root);
            }
            break;
        }
        if ( strcmp( desMovie.c_str(), walker->title.c_str() ) < 0 )
        {
            walker = walker->left;
        }
        if ( strcmp( desMovie.c_str(), walker->title.c_str() ) > 0)
        {
            walker = walker->right;
        }
    }
    if (found == 0)
    {
        cout << "Movie not found." << endl;
    }
}

Movie *Movielist::deleteMovie(string desMovie, Movie *node)
{   int found = 0;
    if (root->title == desMovie)
    {   found = 1;
        // If root has no children
        if ( root->left == nullptr && node->right == nullptr )
        {
            delete root;
            root = nullptr;
        }
        // If root has two children
        else if( root->left != nullptr && root->right != nullptr )
            {

                Movie *mini = findminimum(root->right);
                if (mini == root->right)
                {
                    mini->left = root->left;
                    root->left->parent = mini;
                    mini->parent = root->parent;
                    delete root;
                    root = mini;
                }
                else
                {
                    mini->parent->left = mini->right;
                    mini->parent = root->parent;
                    if (mini->right != nullptr)
                    {
                        mini->right->parent = mini->parent;
                    }
                    mini->left = root->left;
                    mini->right = root->right;
                    delete root;
                    root = mini;
                }
            }
    }
    else
    {
        while (node != nullptr)
        {
            if ( node->title == desMovie )
            {   found = 1;
                // Case: No child
                if ( node->left == nullptr && node->right == nullptr )
                {
                    if ( node == node->parent->left)
                    {
                        node->parent->left = nullptr;
                    }
                    if ( node == node->parent->right)
                    {
                        node->parent->right = nullptr;
                    }
                    delete node;
                    break;

                }
                // Case: Two Children
                else if( node->left != nullptr && node->right !=nullptr )
                    {

                        Movie *mini = findminimum(node->right);
                        if (mini == node->right)
                        {
                            if ( node == node->parent->left)
                            {
                                node->parent->left = mini;
                                mini->parent = node->parent;
                                delete node;
                                break;
                            }
                            if ( node == node->parent->right)
                            {
                                node->parent->right = mini;
                                mini->parent = node->parent;
                                delete node;
                                break;
                            }
                        }
                        else
                        {
                            if (node == node->parent->left)
                            {
                                mini->parent->left = mini->right;
                                mini->parent = node->parent;
                                mini->right->parent = mini->parent;
                                node->parent->left = mini;
                                mini->left = node->left;
                                mini->right = node->right;
                                node->right->parent = mini;
                                node->left->parent = mini;
                                delete node;
                                break;
                            }

                            if (node == node->parent->right)
                            {
                                mini->parent->left = mini->right;
                                mini->parent = node->parent;
                                mini->right->parent = mini->parent;
                                node->parent->right = mini;
                                mini->left = node->left;
                                mini->right = node->right;
                                node->right->parent = mini;
                                node->left->parent = mini;
                                delete node;
                                break;
                            }
                        }
                    }
                // Case: One Child
                else
                {   // If the node is a left child
                    if (node == node->parent->left)
                    {
                        if (node->left != nullptr && node->right == nullptr)
                        {
                            Movie *temp = node->left;
                            node->parent->left = temp;
                            temp->parent = node->parent;
                            delete node;
                            break;
                        }
                        if (node->left == nullptr && node->right != nullptr)
                        {
                            Movie *temp = node->right;
                            node->parent->left = temp;
                            temp->parent = node->parent;
                            delete node;
                            break;
                        }
                    }

                    if (node == node->parent->right)
                    {
                        if (node->left != nullptr&& node->right == nullptr)
                        {
                            Movie *temp = node->left;
                            node->parent->right = temp;
                            temp->parent = node->parent;
                            delete node;
                            break;
                        }

                        if (node->left == nullptr && node->right != nullptr)
                        {
                            Movie *temp = node->right;
                            node->parent->right = temp;
                            temp->parent = node->parent;
                            delete node;
                            break;
                        }
                    }
                }
            }
            else if ( strcmp(desMovie.c_str(), node->title.c_str()) < 0)
                {
                    node = node->left;
                }
            else if ( strcmp(desMovie.c_str(), node->title.c_str()) > 0)
                {
                    node = node->right;
                }
        }
    }
    if (found == 0) cout << "Movie not found." << endl;
    return root;
}

int Movielist::countMovies(Movie *node)
{
    if (node == nullptr) return 0;
    else
    {
        return 1 + countMovies(node->left) + countMovies(node->right);
    }

}

void Movielist::deletetree(Movie *node)
{
    if (node != nullptr)
    {
        deletetree(node->left);
        deletetree(node->right);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

// HERE ENDS THE TREE STUFF //
void Movielist::insertLL(Movie *node)
{
        if (head == nullptr)
        {
            head = node;
        }
        else if (head->IMBD >= node->IMBD)
        {
            node->nextRank = head;
            head->prevRank = node;
            head = node;
        }
        else
        {
            Movie *walker = head;
            while (walker != nullptr)
            {
                if ( (walker->IMBD >= node->IMBD) && (walker->nextRank != nullptr) )
                {
                        node->nextRank = walker;
                        node->prevRank = walker->prevRank;
                        walker->prevRank->nextRank = node;
                        walker->prevRank = node;
                        break;
                }
                if ( walker->nextRank == nullptr && node->IMBD > walker->IMBD)
                {
                    walker->nextRank = node;
                    node->prevRank = walker;
                    node->nextRank = nullptr;
                    break;
                }
                walker = walker->nextRank;
            }
        }
}

void Movielist::printLL()
{
    Movie *walker = head;
    while (walker != nullptr)
    {
        cout <<  walker->IMBD << ". " << walker->title << endl;
        if (walker->nextRank != nullptr)
        {
            walker = walker->nextRank;
        }
        else
        {
            break;
        }
    }
    return;
}

void Movielist::delnodeLL(string desMovie)
{
    if (head->title == desMovie)
    {
        Movie *tmp = head;
        head = head->nextRank;
        head->prevRank = nullptr;
        delete tmp;
    }
    else
    {
        Movie *walker = head;
        while (walker != nullptr)
        {
            if (walker->title == desMovie && walker->nextRank != nullptr)
            {
                walker->prevRank->nextRank = walker->nextRank;
                walker->nextRank->prevRank = walker->prevRank;
                break;
            }
            if (walker->title == desMovie && walker->nextRank == nullptr)
            {
                walker->prevRank->nextRank = nullptr;
            }
            walker = walker->nextRank;
        }
    }
    return;
}
// END OF LINKED LIST FUNCTIONS
template<class T>
struct vertex;

template<class T>
struct adjVertex{
    vertex<T> *v;
    int weight;
    int len;
};

template<class T>
struct vertex{
    T name;
    std::vector<adjVertex<T> > adj;
    std::vector< T > genre;
};

template<class T>
class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(T v1, T v2);
        void addVertex(T name);
        void displayEdges();
        void listvertices();
        void addgenre(T title, T newgenre);
        void buildedges();
        void clearvector();
        void deletevertex(T title);
        void relatedmovies(T title);
    protected:
    private:
        std::vector<vertex<T> > vertices;
};

template<class T>
Graph<T>::Graph()
{

}

template<class T>
Graph<T>::~Graph()
{
    //dtor

}

template<class T>
void Graph<T>::addEdge(T v1, T v2)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == v1)
        {
            for(int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j].name == v2 && i != j)
                {

                    adjVertex<T> av;
                    av.v = &vertices[j];
                    vertices[i].adj.push_back(av);

                }
            }
        }
    }

}

template<class T>
void Graph<T>::addVertex(T n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex<T> v;
        v.name = n;
        vertices.push_back(v);

    }
}

template<class T>
void Graph<T>::addgenre(T _title, T newgenre)
{
    for (int i = 0; i<vertices.size(); i++)
    {
        if (vertices[i].name == _title)
        {
            vertices[i].genre.push_back(newgenre);
            break;
        }
    }
}

template<class T>
void Graph<T>::listvertices()
{
	for (int i = 0; i<vertices.size(); i++)
	{
		cout << vertices[i].name << endl;
		for (int j = 0; j<vertices[i].genre.size(); j++)
        {
            cout << vertices[i].genre[j] << " ";
        }
        cout << endl;
        cout << endl;
	}
}



template<class T>
void Graph<T>::displayEdges()
{
    string separator = "-->";

    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        cout<< vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout<< vertices[i].adj[j].v->name <<"***";
        }
        cout<<endl;
    }
}

template<class T>
void Graph<T>::buildedges()
{
    for (int i = 0; i<vertices.size(); i++)
    {
        for (int l = 0; l<vertices.size(); l++)
        {   bool bond = false;
            for (int j = 0; j<vertices[i].genre.size(); j++)
            {
                for (int m = 0; m<vertices[l].genre.size(); m++)
                {
                    if( vertices[i].genre[j] == vertices[l].genre[m] )
                    {
                        bond = true;
                    }

                }
            }
            if (bond == true)
            {
                addEdge(vertices[i].name, vertices[l].name);
            }
        }
    }
}

template<class T>
void Graph<T>::clearvector()
{
    for (int i = 0; i<vertices.size(); i++)
    {
        vertices[i].adj.clear();
    }
}

template<class T>
void Graph<T>::deletevertex(T title)
{
    for(int i = 0; i<vertices.size(); i++)
    {
        if (vertices[i].name == title)
        {
            vertices.erase(vertices.begin()+i);
        }
    }
}

template<class T>
void Graph<T>::relatedmovies(T title)
{
    for (int i = 0; i<vertices.size(); i++)
    {
        if (vertices[i].name == title)
        {   cout << "Related Movies" << endl;
            for (int j = 0; j<vertices[i].adj.size(); j++)
            {
                cout << vertices[i].adj[j].v->name << endl;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    Movielist Redbox;
    Graph <string> RedboxG;
    string _IMBD, _title, _year, _quantity, _genre, word;
    string filename = "Assignment5Movies.txt";
    int program = 1, option;
    fstream redboxlist;
    redboxlist.open( filename.c_str() );
    Movie *mainroot = Redbox.initialroot();
    while ( redboxlist.good() )
    {
        getline(redboxlist, _IMBD, ',');
        getline(redboxlist, _title, ',');
        getline(redboxlist, _year, ',');
        getline(redboxlist, _quantity, ',');
        RedboxG.addVertex(_title);
        getline(redboxlist, _genre,'\n');
        istringstream iss(_genre);
        while( iss >> word)
        {
            RedboxG.addgenre(_title, word);
        }
        mainroot = Redbox.buildtree( atoi( _IMBD.c_str() ), _title, _year, atoi( _quantity.c_str() ) );
    }
    redboxlist.close();
    RedboxG.buildedges();

    while (program == 1)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. See Related Movies" << endl;
        cout << "3. Rent a movie" << endl;
        cout << "4. Print the inventory" << endl;
        cout << "5. Print Movies by Rank" << endl;
        cout << "6. Print Edges" << endl;
        cout << "7. Add New Movie" << endl;
        cout << "8. Delete a movie" << endl;
        cout << "9. Count the movies" << endl;
        cout << "10. Quit" << endl;

        cin >> option;
        cin.ignore();
        if (option == 1)
        {
            cout << "Enter title: " << endl;
            string intitle;
            getline(cin, intitle);

            Redbox.searchMovies(intitle,0);
        }

        if(option == 2)
        {
            cout << "Enter title" << endl;
            string intitle;
            getline(cin, intitle);
            RedboxG.relatedmovies(intitle);
        }

        if (option == 3)
        {
            cout << "Enter title: " << endl;
            string intitle;
            getline(cin, intitle);

            Redbox.searchMovies(intitle,1);
        }

        if (option == 4)
        {
            Redbox.printtree(mainroot);
        }

        if (option == 5)
        {
            Redbox.printLL();
        }

        if(option == 6)
        {
            RedboxG.displayEdges();
        }

        if (option == 7)
        {
            string intitle;
            string inIMBD;
            string inyear;
            string inquantity;
            string ingenre;
            string newword;
            cout << "Enter Title" << endl;
            getline(cin, intitle);
            cout << "Enter IMBD Rank" << endl;
            getline(cin, inIMBD);
            cout << "Enter Year" << endl;
            getline(cin, inyear);
            cout << "Enter Amount" << endl;
            getline(cin, inquantity);
            cout << "Enter genre(s)" << endl;
            getline(cin, ingenre);
            RedboxG.addVertex(intitle);
            istringstream iss(ingenre);
            while( iss >> newword)
            {
                cout << _title << " " << newword << endl;
                RedboxG.addgenre(intitle, newword);
            }
            RedboxG.clearvector();
            RedboxG.buildedges();

            mainroot = Redbox.buildtree( atoi( inIMBD.c_str() ), intitle, inyear, atoi(inquantity.c_str() ) );
        }

        if (option == 8)

        {
            cout << "Enter Title" << endl;
            string intitle;
            getline(cin, intitle);
            Redbox.delnodeLL(intitle);
            mainroot = Redbox.deleteMovie(intitle, mainroot);
            RedboxG.deletevertex(intitle);
            RedboxG.clearvector();
            RedboxG.buildedges();
        }

        if (option == 9)
        {
            int nummovies = Redbox.countMovies(mainroot);
            cout << "Tree contains: " << nummovies << " movies." << endl;
        }

        if (option == 10)
        {
            cout << "Goodbye!" << endl;
            Redbox.deletetree(mainroot);
            program = 0;
        }
    }

Redbox.~Movielist();
RedboxG.~Graph();
}
