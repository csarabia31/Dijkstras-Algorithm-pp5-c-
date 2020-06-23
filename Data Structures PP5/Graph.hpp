#ifndef GRAPH_H
#define GRAPH_H
#include "GraphBase.hpp"
#include <map>


typedef std::pair<int, std::string> vPair; 

//edge class with vertices 
class Edge
{
    public:

        
        std::string v1;            
        std::string v2;            
        
        Edge();                         
        ~Edge();                        
        unsigned long weight;
        //bool visited = true;
        //friend class for access
        friend class Graph;         
    
};

//graph class
class Graph : public GraphBase
{
    public:

        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
        //function to print path
        void printPath(std::map<std::string,std::string> root, std::string endLabel , std::vector<std::string> &path);

         
         
        
        //vector for vertices
        std::vector<std::string> v;  
        // declaring the vector of edges
        std::vector<Edge*> adj; 
    
};

#endif