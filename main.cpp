#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "./rapidjson/include/rapidjson/document.h"
#include "./rapidjson/include/rapidjson/filereadstream.h"
#include "./rapidjson/include/rapidjson/stringbuffer.h"
#include "./rapidjson/include/rapidjson/writer.h"

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
        person(){}

        void config_person(int I,string N,int Y,string U,string M,string J){
            ID = I;
            Name = N;
            YearOfBirth = Y;
            University = U;
            Major = M;
            JobPlace = J;
        }

        void config_connections(vector<int> C){
            for(auto& Con : C){
                Connections.push_back(Con);
            }
        }


        int get_ID(){
            return this->ID;
        }

        string get_Name(){
            return this->Name;
        }

        int get_YearOfBirth(){
            return this->YearOfBirth;
        }

        string get_University(){
            return this->University;
        }

        string get_Major(){
            return this->Major;
        }

        string get_JobPlace(){
            return this->JobPlace;
        }

        vector<int> get_connections(){
            return Connections;
        }

        ~person(){}
};

//--------**readJSON function**-----------------------------------------------------------------------------------------------------------------------------

void readJSON(const string& filename, vector<person>& people) {
    FILE* fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        std::cerr << "Could not open file " << filename << std::endl;
        return;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);

    if (document.HasParseError()) {
        std::cerr << "Error parsing JSON file" << std::endl;
        return;
    }

    for (auto& Person : document.GetArray()) {
        person p;
        p.config_person(Person["ID"].GetInt(),
            Person["Name"].GetString(),
            Person["Year of Birth"].GetInt(),
            Person["University"].GetString(),
            Person["Major"].GetString(),
            Person["Job Place"].GetString());
        
        vector<int> C;
        for (auto& connection : Person["Connections"].GetArray()) {
            C.push_back(connection.GetInt());
        }
        p.config_connections(C);
        
        people.push_back(p);
    }
}

//--------**Function to determine the edges**-----------------------------------------------------------------------------------------------------------------------------

void determine_edges(vector<person>& people,  vector<vector <int>>& gra){
    int i=0;
    for (auto& pe : people) {
        int j = 0;
        for (const auto& conn : pe.get_connections()){
            gra[i][j] = conn;
            j++;
        }
        i++;
    }
}

//--------**Main Function**-----------------------------------------------------------------------------------------------------------------------------

int main(){
    vector<person> people;
    readJSON("E:/DS Project/inputFile.json", people);

    vector<vector <int>> gra(people.size(), vector<int>(people.size(),-1));
    determine_edges(people, gra);

    for(int i=0 ; i < gra.size() ; i++){
        for(int j=0 ; gra[i][j] != -1 ; j++){
            cout<<gra[i][j]<<" ";
        }
        cout<<endl;
    }

    // for (auto& pe : people) {
    //     std::cout << "ID: " << pe.get_ID() << std::endl;
    //     std::cout << "Name: " << pe.get_Name() << std::endl;
    //     std::cout << "Year of Birth: " << pe.get_YearOfBirth() << std::endl;
    //     std::cout << "University: " << pe.get_University() << std::endl;
    //     std::cout << "Major: " << pe.get_Major() << std::endl;
    //     std::cout << "Job Place: " << pe.get_JobPlace() << std::endl;
    //     std::cout << "Connections: ";
    //     for (const auto& conn : pe.get_connections()) {
    //         std::cout << conn << " ";
    //     }
    //     std::cout << std::endl << std::endl;
    // }
}