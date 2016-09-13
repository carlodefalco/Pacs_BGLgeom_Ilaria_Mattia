#include<string>
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include<utility>
#include<boost/graph/adjacency_list.hpp>

#include"generic_point.hpp"
#include"edge_property.hpp"

/*!
  @brief Reading from file with list of vertex_set and edges and associated properties
  
  @details
 */
 
 using namespace boost;
 typedef adjacency_list<vecS,vecS,directedS,point<3>,edge_prop_t> Graph;
 typedef graph_traits<Graph>::edge_descriptor edge_descriptor;
 
int main()
{  
  /* I want to read from a file where data 
     is written as
     
     line1: description
     line2: description
     from line 3: no - source_v - target_v - diameter - length - source_coord - target_coord
  */
  std::ifstream file("rattm93a.txt");
  
  std::set<int> vertex_set; // it's a set in order to avoid multiple additions of the same vertex
  bool inserted; //if FALSE the vertex I'm trying to add was already in the set 
  std::pair<std::set<int>::iterator, bool> set_inserter;
  std::set<int>::iterator it;
  
  
  point<3> SRC,TGT; //! they will store vertex coordinates
  
  int edge_num, src, tgt; // they will read the first 3 numbers of each line 
  double diam, length; // they will read the remaining 8
  
  Graph G; 
  edge_descriptor e;
  bool edge_inserted;
  
  // ignore the first two lines of the file
  std::string dummyLine;
  getline(file, dummyLine);
  getline(file, dummyLine);
  
  
  
  // Until I reach end of file
  while (!file.fail() && !file.eof()){
    std::string s;
    getline(file,s); // read the the whole line
    if(s.empty()) continue; // empty line
    std::istringstream tmp(s); // build an input sstream.
    tmp>>edge_num>>src>>tgt>>diam>>length>>SRC>>TGT; // read from the input stream
    if(!tmp.fail()){
    	//! create edge (src, tgt)
    	tie(e, edge_inserted) = add_edge(src, tgt, G);
    	G[e].diam = diam;
    	G[e].length = length;
	
	set_inserter = vertex_set.insert(src);

	if(set_inserter.second)
		{
		 	G[src]=SRC;
		}
	set_inserter = vertex_set.insert(tgt);
	if(set_inserter.second)
		{
			G[tgt]=TGT;
		}
    }
  }

  graph_traits<Graph>::vertex_iterator vb, ve;
  for(tie(vb,ve) = vertices(G); vb != ve; ++vb)
  	std::cout << *vb << std::endl;
  
  //Plot degli archi:
  graph_traits<Graph>::edge_iterator ebegin, eend;
  for( tie(ebegin, eend) = edges(G); ebegin != eend; ebegin++)
  	std::cout << *ebegin << std::endl;
  //and "<<edges.size()<<" edges from file rattm93a.txt:"<<std::endl;
  //std::cout<<"vertex_set:"<<std::endl;
  //for (it = vertex_set.begin(); it != vertex_set.end(); ++it) 
  //std::cout<<"I've read "<<vertices.size()<<" vertices and "<<edges.size()<<" edges from file rattm93a.txt:"<<std::endl;
  //std::cout<<"Vertices:"<<std::endl;
  //for (it = vertices.begin(); it != vertices.end(); ++it) 
  //	std::cout<<*it<<std::endl;
  //for (unsigned int i=0; i<edges.size(); ++i)
  //	std::cout<<"("<<edges[i].first<<","<<edges[i].second<<")"<<std::endl;
  	
return 0;
}
