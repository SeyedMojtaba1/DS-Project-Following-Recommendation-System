#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//--------**Graph Class**-----------------------------------------------------------------------------------------------------------------------------

class graph{

    private:
        
    public:
        graph(){}


        // Modified bfs to store the parent of nodes along with the distance from source node
        void bfs(vector<vector<int> >& gra, int S,
                vector<int>& par, vector<int>& dist)
        {
            // queue to store the nodes in the order they are visited
            queue<int> q;
            // Mark the distance of the source node as 0
            dist[S] = 0;
            // Push the source node to the queue
            q.push(S);

            // Iterate till the queue is not empty
            while (!q.empty()) {
                // Pop the node at the front of the queue
                int node = q.front();
                q.pop();

                // Explore all the neighbours of the current node
                for (int neighbour : gra[node]) {
                    // Check if the neighbouring node is not visited
                    if (dist[neighbour] == 1e9) {
                        // Mark the current node as the parent of the neighbouring node
                        par[neighbour] = node;
                        // Mark the distance of the neighbouring node as distance of the current node + 1
                        dist[neighbour] = dist[node] + 1;
                        // Insert the neighbouring node to the queue
                        q.push(neighbour);
                    }
                }
            }
        }

        // Function to print the shortest distance between source vertex and destination vertex
        void printShortestDistance(vector<vector<int> >& gra,int S, int D, int V)
        {
            // par[] array stores the parent of nodes
            vector<int> par(V, -1);

            // dist[] array stores distance of nodes from S
            vector<int> dist(V, 1e9);

            // function call to find the distance of all nodes and their parent nodes
            bfs(gra, S, par, dist);

            if (dist[D] == 1e9) {
                cout << "Source and Destination are not connected";
                return;
            }

            // vector path stores the shortest path
            vector<int> path;
            int currentNode = D;
            path.push_back(D);
            while (par[currentNode] != -1) {
                path.push_back(par[currentNode]);
                currentNode = par[currentNode];
            }

            // printing path from source to destination
            for (int i = path.size() - 1; i >= 0; i--)
                cout << path[i] << " ";
        }

        ~graph(){}
};

//--------**Person Class**-----------------------------------------------------------------------------------------------------------------------------
class person{
    
    private:
        int ID;
        string Name;
        int YearOfBirth;
        string University;
        string Major;
        string JobPlace;
        vector<int> Connections;

    public:
        person();

        void add_person(int ,string ,int ,string ,string ,string ,int*);

        ~person();
};

//--------**Main Function**-----------------------------------------------------------------------------------------------------------------------------

int main(){
    
}