Project Explanation
This project simulates a social network, allowing users to find connection suggestions based on their profiles. It reads input data from a JSON file, constructs a graph representing the network, and then computes and prints suggested connections for each person in the network. Below are the key components and their functionalities:

1. Person Class
The person class holds individual user data. Each person has an ID, name, year of birth, university, major, job place, and a list of connections.

Attributes:

ID: An integer representing the person's unique identifier.
Name: A string representing the person's name.
YearOfBirth: An integer representing the person's birth year.
University: A string representing the university the person attended.
Major: A string representing the person's major.
JobPlace: A string representing the person's job place.
Connections: A vector of integers representing IDs of connected persons.
Methods:

config_person: Configures the person's basic information.
config_connections: Configures the person's connections.
Getter methods for each attribute.
2. Graph Class
The graph class represents the network as an adjacency list.

Attributes:

gra: A 2D vector representing the adjacency list of the graph.
sizeGraph: An integer representing the size of the graph.
Methods:

bfs: Performs a breadth-first search to find the shortest path from a source node to all other nodes.
get_shortest_degree: Returns the shortest path length (in terms of edges) between two nodes.
Getter methods for the graph and its size.
3. Similarity and Scoring Functions
Functions to determine the similarity between two persons and score the strength of a potential connection.

Similarity Functions:

check_similarity_university: Checks if two persons attended the same university.
check_similarity_major: Checks if two persons had the same major.
check_similarity_jobplace: Checks if two persons work at the same job place.
check_similarity_yearbirth: Checks if two persons were born within a certain range of years.
check_proximity_to: Uses the graph to determine the shortest path between two persons.
Scoring Function:

score_of_suggestion: Aggregates the similarity scores to generate an overall connection score.
4. Main Function
Reads input data, constructs the graph, and generates connection suggestions.

Steps:
Reads JSON data from an input file to populate a vector of person objects.
Constructs the graph by determining the edges based on the connections of each person.
For each person in the network, it computes and prints connection suggestions based on the scoring system.
Sample Input and Output
The project uses a JSON file as input. Here's an example of the JSON structure:

json
Copy code
[
  {
    "ID": 1,
    "Name": "Alice",
    "Year of Birth": 1990,
    "University": "University A",
    "Major": "Computer Science",
    "Job Place": "Company X",
    "Connections": [2, 3]
  },
  {
    "ID": 2,
    "Name": "Bob",
    "Year of Birth": 1992,
    "University": "University B",
    "Major": "Mathematics",
    "Job Place": "Company Y",
    "Connections": [1]
  }
]
Example of Output
Given the input data, the program might output:

mathematica
Copy code
For ID 1
Bob : 1'st
ID : 2

For ID 2
Alice : 1'st
ID : 1
Additional Details
JSON Parsing: Utilizes the rapidjson library to parse JSON input files.
Edge Determination: Populates the graph adjacency list based on the connections defined for each person.
Connection Suggestion: Based on predefined similarity metrics and the shortest path in the graph, it suggests connections ranked by score.
