#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct edge_info {
    int row_index;
    int column_index;
    double weight;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_edges;
        int size_of_graph;
		
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    graph = new double*[n];
    size_of_graph = n;
    num_edges = 0;
    for (int i=0; i<n; i++){
        graph[i] = new double[n];
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            graph[i][j] = INF;
        }
    }
}

Weighted_graph::~Weighted_graph() {
    for (int i=0; i<size_of_graph; i++){
        delete [] graph[i];
    }
    delete [] graph;
}

int Weighted_graph::degree(int u) const {
    
    if (u < 0 || u > (size_of_graph-1)){
        throw illegal_argument();
    }
    
    int deg_count = 0;
    int index = u;
    
//    for(int i=0; i<size_of_graph; i++){
//        for(int j=0; j<size_of_graph; j++){
//            cout << graph[i][j] << "|";
//        }
//        cout << endl;
//    }
    
    for (int i=0; i<size_of_graph; i++) {
//        if (i == index){
//            deg_count--;
//        }
        if (graph[i][index] != INF){
            deg_count++;
        }
    }
    
    
    for (int i=0; i<size_of_graph; i++) {
        if (graph[index][i] != INF){
            deg_count++;
        }
    }
    
	return deg_count;

}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if (i > size_of_graph-1 || j > size_of_graph-1){
        throw illegal_argument();
    }
    
    if (i < 0 || j < 0){
        throw illegal_argument();
    }
    
    if (i == j){
        return true;
    }
    
    if (graph[i][j] != INF && i < j){
        graph[i][j] = INF;
        num_edges--;
        return true;
    }
    
    if(i > j){
        if (graph[j][i] != INF){
            graph[j][i] = INF;
            num_edges--;
            return true;
        }
    }
    
	return false;
}

void Weighted_graph::clear_edges() {
    for (int i=0; i<size_of_graph; i++){
        for (int j=0; j<size_of_graph; j++){
            graph[i][j] = INF;
        }
    }
    
    num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    if (i > (size_of_graph-1) || j > (size_of_graph-1)){
        throw illegal_argument();
    }
    
    if (i < 0 || j < 0 || d < 0){
        throw illegal_argument();
    }
    
    if (i == j) {
        return false;
    }
    
    if (i > j) {
        if (graph[j][i] == INF) {
            graph[j][i] = d;
            num_edges++;
            return true;
        } else if (graph[j][i] != INF){
            graph[j][i] = d;
            return true;
        }
    }
    
    if (graph[i][j] == INF){
        graph[i][j] = d;
        num_edges++;
        return true;
    } else if (graph[i][j] != INF){
        graph[i][j] = d;
        return true;
    }

    
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	
   // cout<<"num edges is " << num_edges << endl;
    
    edge_info* edges = new edge_info[num_edges];
    
    int index_to_insert = 0;
    
    int edges_examined = 0;
    
    double weight_of_mst = 0;
    
    for (int i=0; i<size_of_graph; i++){
        for (int j=0; j<size_of_graph; j++){
            if (graph[i][j] != INF){
                edges[index_to_insert].row_index = i;
                edges[index_to_insert].column_index = j;
                edges[index_to_insert].weight = graph[i][j];
                index_to_insert++;
            }
        }
    }
   // cout<< "index_to_insert is  " <<index_to_insert <<endl;
    
    //using insertion sort in the code below
    int j;
    edge_info temp;
    
    for (int i=0; i<=num_edges; i++){
        j = i;
        
        while (j > 0 && (edges[j].weight < edges[j-1].weight)){
            temp = edges[j];
            edges[j] = edges[j-1];
            edges[j-1] = temp;
            j--;
        }
    }
    
//    for (int i=0; i<num_edges; i++){
//        cout << edges[i].row_index << "|" << edges[i].column_index << "|" << edges[i].weight << endl;
//    }
    
    Disjoint_set disjoint_set(size_of_graph);
    
    for (int i=0; i<num_edges; i++){
        if (disjoint_set.num_sets() == 1){
            break;
        }
        edges_examined++;
        if (disjoint_set.find_set(edges[i].row_index) != disjoint_set.find_set(edges[i].column_index)){
            disjoint_set.union_sets(edges[i].row_index, edges[i].column_index);
            weight_of_mst = weight_of_mst + edges[i].weight;
        }
    }
    
    delete[] edges;
    
	return std::pair<double, int>( weight_of_mst, edges_examined );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
