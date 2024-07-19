#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "./rapidjson/include/rapidjson/document.h"
#include "./rapidjson/include/rapidjson/filereadstream.h"
#include "./rapidjson/include/rapidjson/stringbuffer.h"
#include "./rapidjson/include/rapidjson/writer.h"

using namespace std;

//--------**Definition of the class graph**-----------------------------------------------------------------------------------------------------------------------------

class graph{

    // Private members of the class
    private:
        vector<vector <int>> gra;
        int sizeGraph;
    // Public members of the class
    public:
        // Default constructor
        graph(){}

        graph(vector<vector <int>>& g){
            gra = g;
            sizeGraph = g.size();
        }

        vector<vector <int>> get_graph(){
            return gra;
        }

        int get_size_graph(){
            return sizeGraph;
        }

        // Modified bfs to store the parent of nodes along with the distance from source node
        void bfs(int S, vector<int>& par, 
                vector<int>& dist)
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
        int get_shortest_degree(int S, int D)
        {
            // par[] array stores the parent of nodes
            vector<int> par(sizeGraph, -1);

            // dist[] array stores distance of nodes from S
            vector<int> dist(sizeGraph, 1e9);

            // function call to find the distance of all nodes and their parent nodes
            bfs(S, par, dist);

            // if (dist[D] == 1e9) {
            //     cout << "Source and Destination are not connected";
            //     return -1;
            // }

            // vector path stores the shortest path
            vector<int> path;
            int currentNode = D;
            path.push_back(D);
            while (par[currentNode] != -1) {
                path.push_back(par[currentNode]);
                currentNode = par[currentNode];
            }

            return path.size();

            // // printing path from source to destination
            // for (int i = path.size() - 1; i >= 0; i--)
            //     cout << path[i] << " ";
        }

        ~graph(){}
};

//--------**Definition of the class person**-----------------------------------------------------------------------------------------------------------------------------

class person{
    
    // Private members of the class
    private:
        int ID;
        string Name;
        int YearOfBirth;
        string University;
        string Major;
        string JobPlace;
        vector<int> Connections;

    // Public members of the class
    public:
        // Default constructor
        person(){}

        // Method to configure the person's basic information
        void config_person(int I,string N,int Y,string U,string M,string J){
            ID = I;
            Name = N;
            YearOfBirth = Y;
            University = U;
            Major = M;
            JobPlace = J;
        }

        // Method to configure the person's connections
        void config_connections(vector<int> C){
            for(auto& Con : C){
                Connections.push_back(Con);
            }
        }


        // Method to get the person's ID
        int get_ID(){
            return this->ID;
        }

        // Method to get the person's name
        string get_Name(){
            return this->Name;
        }

        // Method to get the person's year of birth
        int get_YearOfBirth(){
            return this->YearOfBirth;
        }

        // Method to get the person's university
        string get_University(){
            return this->University;
        }

        // Method to get the person's major
        string get_Major(){
            return this->Major;
        }

        // Method to get the person's job place
        string get_JobPlace(){
            return this->JobPlace;
        }

        // Method to get the person's connections
        vector<int> get_connections(){
            return Connections;
        }

        // Destructor
        ~person(){}
};

//--------**readJSON function**-----------------------------------------------------------------------------------------------------------------------------

// Function to read JSON data from a file and populate a vector of person objects
void readJSON(const string& filename, vector<person>& people) {
    // Open the file in binary read mode
    FILE* fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        // Print an error message if the file cannot be opened
        std::cerr << "Could not open file " << filename << std::endl;
        return;
    }

    // Buffer for reading the file
    char readBuffer[65536];
    // Create a FileReadStream object for reading the JSON file
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // Create a Document object to hold the parsed JSON
    rapidjson::Document document;
    // Parse the JSON data from the file stream
    document.ParseStream(is);
    // Close the file after reading
    fclose(fp);

    // Check for parsing errors
    if (document.HasParseError()) {
        // Print an error message if the JSON is invalid
        std::cerr << "Error parsing JSON file" << std::endl;
        return;
    }

    // Iterate through the array of persons in the JSON document
    for (auto& Person : document.GetArray()) {
        // Create a person object
        person p;
        // Configure the person object with data from the JSON
        p.config_person(Person["ID"].GetInt(),
            Person["Name"].GetString(),
            Person["Year of Birth"].GetInt(),
            Person["University"].GetString(),
            Person["Major"].GetString(),
            Person["Job Place"].GetString());
        
        // Create a vector to hold connections
        vector<int> C;
        // Iterate through the connections array in the JSON document
        for (auto& connection : Person["Connections"].GetArray()) {
            // Add each connection to the vector
            C.push_back(connection.GetInt());
        }
        // Configure the connections for the person object
        p.config_connections(C);
        
        // Add the configured person object to the vector of people
        people.push_back(p);
    }
}

//--------**Function to determine the edges**-----------------------------------------------------------------------------------------------------------------------------

// Function to determine edges for a graph based on people's connections
void determine_edges(vector<person>& people,  vector<vector <int>>& gra){
    int i=0;
    // Iterate through each person in the people vector
    for (auto& pe : people) {
        int j = 0;
        // Iterate through each connection of the current person
        for (const auto& conn : pe.get_connections()){
            // Assign the connection ID to the graph matrix
            gra[i][j] = conn;
            j++;
        }
        i++; 
    }
}

//--------**Similarity Chech Functions**-----------------------------------------------------------------------------------------------------------------------------

int check_similarity_university(person& original,person& subsidiary){
    if(original.get_University() == subsidiary.get_University()){
        return 2;
    }
    else{
        return 0;
    }
}

int check_similarity_major(person& original,person& subsidiary){
    if(original.get_Major() == subsidiary.get_Major()){
        return 2;
    }
    else{
        return 0;
    }
}

int check_similarity_jobplace(person& original,person& subsidiary){
    if(original.get_JobPlace() == subsidiary.get_JobPlace()){
        return 2;
    }
    else{
        return 0;
    }
}

int check_similarity_yearbirth(person& original,person& subsidiary){
    if((original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) < 5 
        && (original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) > -5){
            return 2;
    }
    else if(((original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) < 10 
        && (original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) > 5)
        || ((original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) > -10 
        && (original.get_YearOfBirth() - subsidiary.get_YearOfBirth()) < -5)){
            return 1;
    }
    else{
        return 0;
    }
}

int check_proximity_to(graph& gra, person& original, person& subsidiary){
    if(gra.get_shortest_degree(original.get_ID(), subsidiary.get_ID()) == 2){
        return 2;
    }
    else if(gra.get_shortest_degree(original.get_ID(), subsidiary.get_ID()) == 3){
        return 1;
    }
    else{
        return 0;
    }
}

//--------**Scoring And Decision Function**-----------------------------------------------------------------------------------------------------------------------------

int score_of_suggestion(graph& gra, person& original, person& subsidiary){
    int score = 0;
    score += check_similarity_university(original,subsidiary);
    score += check_similarity_major(original,subsidiary);
    score += check_similarity_jobplace(original,subsidiary);
    score += check_similarity_yearbirth(original,subsidiary);
    score += check_proximity_to(gra, original, subsidiary);
    return score;
}

vector<int> list_of_suggestion(graph &gra, vector<person>& peo, person& original){
    bool isConnect;
    for(int i = 0; i < gra.get_size_graph() ; i++){
        isConnect = false;
        for(int j = 0 ; j < original.get_connections().size() ; j++){
            if(i == original.get_connections()[j]-1){
                isConnect = true;
            }
        }
        if(isConnect == true){
            continue;
        }
        if(i == original.get_ID()-1){
            continue;
        }
        else if(score_of_suggestion(gra, original, peo[i]) >= 10){
            cout << peo[i].get_Name() << " : 1'st" << endl << "ID : " << peo[i].get_ID() << endl << endl;
        }
        else if(score_of_suggestion(gra, original, peo[i]) >= 6 && score_of_suggestion(gra, original, peo[i]) < 10){
            cout << peo[i].get_Name() << " : 2'nd" << endl << "ID : " << peo[i].get_ID() << endl << endl;
        }
        else if(score_of_suggestion(gra, original, peo[i]) >= 3 && score_of_suggestion(gra, original, peo[i]) < 6){
            cout << peo[i].get_Name() << " : 3'rd" << endl << "ID : " << peo[i].get_ID() << endl << endl;
        }
        else{
            continue;
        }
    }
}

//--------**Main Function**-----------------------------------------------------------------------------------------------------------------------------

int main(){
    vector<person> people;
    readJSON("E:/DS Project/inputFile.json", people);

    vector<vector <int>> gra(people.size(), vector<int>(people.size(),-1));
    determine_edges(people, gra);

    graph Graph(gra);
    
    for(int i = 1 ; i <= people.size() ; i++){
        cout<<"For ID "<<i<<endl;
        list_of_suggestion(Graph, people, people[i]);
    }
    // cout<<people.size();
    // list_of_suggestion(Graph, people, people[6]);


    // for(int i=0 ; i < gra.size() ; i++){
    //     for(int j=0 ; gra[i][j] != -1 ; j++){
    //         cout<<gra[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

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