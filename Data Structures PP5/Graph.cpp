#include <limits.h>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include <string>
#include <iostream>
#include "Graph.hpp"


typedef std::pair<int, std::string> vPair;
//edge constructor
Edge::Edge()
{           
            
            v1 = " ";
            v2 = " ";
            weight = 0;
            
}

//destructor
Edge::~Edge(){}

//adding vertex to the vector
void Graph::addVertex(std::string label)
{

    
    for(auto vertex : v)
    {
        if(vertex == label)
         return;
    }
    v.push_back(label);
}


//removinfg vertex
void Graph::removeVertex(std::string label)
{
    unsigned int i;

    //create new edge
    Edge *edge = new Edge(); 

    //find vertex and erase using index
    for(i = 0; i < v.size(); i++)
    {
            
        if(v.at(i) == label)
        {
            
            v.erase(v.begin()+i);

            for(i = 0; i < adj.size(); i++)
            {
                edge = adj.at(i);
                if(edge->v1 == label || edge->v2 == label)
                    {
                        adj.erase(adj.begin()+i);
                    }
            }
        }
    }

}


//adding an edge to a graph
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    //bool variables
    bool b1 = false;
    bool b2 = false; 
       

    //found
    for(unsigned int i = 0; i < v.size(); ++i)
    {
        if(v.at(i) == label1)
        {
            b1 = true;
        }
        if(v.at(i) == label2)
        {
            b2 = true;
        }
    }
        
    //adding edge in between 2 vertices
    if(b1 == true && b2 == true)
    {
        Edge *edge = new Edge();
        edge->v1 = label1;
        edge->v2 = label2;
        edge->weight = weight;
        adj.push_back(edge);
        return;
    }         
}
    

//remove edge from graph
void Graph::removeEdge(std::string label1, std::string label2)
{
    
    unsigned int i;
    Edge *edge = new Edge(); 

    //finding edge and erasing
    for(i = 0; i < adj.size(); i++)
    {
        edge = adj.at(i); 

        if(edge->v1 == label1 && edge->v2 == label2)
        {     
            
            adj.erase(adj.begin()+i);               
            return;
        }
    }        
    return;
}


 //shortest path function
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
{
      
    //priority queue to be used
    std::priority_queue< std::pair<int, std::string>, std::vector<std::pair<int, std::string>> , std::greater<std::pair<int, std::string>> > Q;
    //maps
    std::map<std::string,int> v2; 
    std::map<std::string,std::string> rootNode; 

    //set labels
    for (const auto label : v)
    {
        //long max is like infinity
        v2[label] = LONG_MAX; 
        //set the root nodes value to empty
        rootNode[label] = "empty"; 
    }    
      
    //male the start labels distance to 0 push into q
    Q.push(make_pair(0, startLabel)); 
    v2[startLabel] = 0; 

    //as long as q is not empty
    while (!Q.empty()) 
    { 
        //get vertex from top store into x1
        std::string x1 = Q.top().second; 
        Q.pop(); 
      
        //iterator for the pair
        std::list< std::pair<int, std::string> >::iterator it; 
        std::string y1;

            
        //get values and weight
        for( auto it : adj)
        {
            if(it->v1 == x1)
            {
                y1 = it->v2;
            }
            else if(it->v2 == x1)
            {
                y1 = it->v1;
            }
            else 
                continue;
            int weight = it->weight;

                
            //make pairs if v2 > v2+weight
            if (v2[y1] > v2[x1] + weight) 
            { 
                
                rootNode[y1] = x1;
                v2[y1] = v2[x1] + weight; 
                Q.push(make_pair(v2[y1], y1)); 
            }            
        } 
    } 
    
    //push back into path
    path.push_back(startLabel);
    printPath(rootNode,endLabel,path);
    return v2[endLabel];
}

//function to print the path
void Graph::printPath(std::map<std::string,std::string> root, std::string endLabel , std::vector<std::string> &path) 
{ 
      
        if (root[endLabel] == "empty") 
            return; 
        printPath(root, root[endLabel],path); 
        path.push_back(endLabel);
      
}
    