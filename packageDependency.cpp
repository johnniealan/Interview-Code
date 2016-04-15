#include <iostream>
#include <list>

using namespace std;

class rootpkg
{
    int v;
    list <int> *adj;
    void dfsutils ( int v, bool u[]);
   public:
     string *pkgName;
     rootpkg(int V) { v = V; adj = new list <int> [V]; }
     void search(int vert);
     bool isCycle (int v, bool u[],int parent);
     void addEdge(int v, int w)
     {
        adj[v].push_back(w);
        // uncomment this if you want to check cyclic
        //adj[w].push_back(v);
     }
};

// Function to mark the nodes as visited
void rootpkg::dfsutils (int v, bool u[])
{
    u[v] = true;
    
    list <int> :: iterator iter;
    
    for ( iter = adj[v].begin(); iter != adj[v].end(); ++iter)
    {
       if ( !u[*iter] )
          dfsutils(*iter,u);
    }
}

// Function to check if there is a cycle
bool rootpkg::isCycle (int v, bool u[],int parent)
{
    u[v] = true;
    
    list <int> :: iterator iter;
    
    for ( iter = adj[v].begin(); iter != adj[v].end(); ++iter)
    { 
       if ( ! u[*iter] )
       {
          if ( isCycle(*iter,u,v) )
              return true;
        }
        else if ( u[*iter] && *iter != parent )
        {
            return true;
        }
    }
    return false;
}
// Function to search the dependecy for the package
void rootpkg ::  search ( int vert )
{ 
    bool *u = new bool [v];
    dfsutils(vert, u);
    
    for (int i=0; i < v; i++ )
    {
       if ( u[i] )
         cout << "The dependecy is "<< pkgName[i] << endl;
    }
}

// Main function
int main()
{
     rootpkg pkg(5);
     pkg.pkgName = new string [5];
     pkg.pkgName[0] = "Root Package";
     pkg.pkgName[1] = "Apache";
     pkg.pkgName[2] = "Some library";
     pkg.pkgName[3] = "Core";
     pkg.pkgName[4] = "other library";

     pkg.addEdge(0,1);
     pkg.addEdge(0,2);
     pkg.addEdge(1,3);
     pkg.addEdge(1,4);
     pkg.addEdge(2,4);
     pkg.search(2);
     // uncomment this if you want to check cyclic
     //bool *u = new bool [5];
     //pkg.isCycle(0,u,0) ? cout <<"Cyclic\n" : cout << "Not cyclic\n";
}
