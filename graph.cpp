

#include <cstdint>
#include <vector>
//#include <optional>
#include <limits>
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>

template <typename V, typename E>
class Graph{
public:
    class VerticesIterator{
        private:
            VerticesIterator(Graph<V, E> &graph, std::size_t current_vertex_id = 0u);

        public:
            // ...

        friend class Graph<V, E>;

        private:
        // ...

        public:
            bool operator==(const VerticesIterator &vi) const;
            bool operator!=(const VerticesIterator &vi) const { return !(*this == vi); }
            VerticesIterator& operator++();
            VerticesIterator operator++(int);
            V& operator*() const;
            V* operator->() const;
    };

    class EdgesIterator{
        private:
            EdgesIterator(Graph<V, E> &graph, std::size_t nm_row, std::size_t nm_col);

        public:
            // ...

            friend class Graph<V, E>;

        private:
            // ...

        public:
            bool operator==(const EdgesIterator &ei) const;
            bool operator!=(const EdgesIterator &ei) const { return !(*this == ei); }
            EdgesIterator& operator++();
            EdgesIterator operator++(int);
            E& operator*() const;
            E* operator->() const;
    };

public:
    Graph();
    // ...

//private:
    std::vector<std::vector<E>> edges;
    int vertid=0;
    std::vector<V> vertices;

public:
    //VerticesIterator
    void insertVertex(const V &vertex_data);
    //std::pair<EdgesIterator, bool>
    void insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
    bool removeVertex(std::size_t vertex_id);
    bool removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
    bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const;
    std::size_t nrOfVertices() const;
    std::size_t nrOfEdges() const;
    void printNeighborhoodMatrix() const;
    VerticesIterator vertex(std::size_t vertex_id);
    EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id);
    VerticesIterator begin() { return beginVertices(); }
    VerticesIterator end() { return endVertices(); }
    VerticesIterator beginVertices();
    VerticesIterator endVertices();
    EdgesIterator beginEdges();
    EdgesIterator endEdges();
};

template<typename V, typename E>
Graph<V,E>::Graph(){

}

template<typename V, typename E>
void Graph<V,E>::insertVertex(const V &vertex_data){
    vertices.push_back(vertex_data);
    edges.push_back({0});
    for(int i=0; i<vertices.size();i++){
        edges[i].resize(vertices.size());
        edges[i][vertices.size()-1 ]  = 0;
    }

}

template<typename V, typename E>
void Graph<V,E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label , bool replace){
    edges[vertex1_id][vertex2_id] = label;
}

template<typename V, typename E>
bool Graph<V,E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id){
    if (edges[vertex1_id][vertex2_id] != 0){
        edges[vertex1_id][vertex2_id] = 0;
        return true;
    }
    else return false;

}

template<typename V, typename E>
void Graph<V,E>::printNeighborhoodMatrix() const{
     std::cout<<std::endl;
    for(n : edges){
        for ( s : n){
            std::cout << s << " ";
        }
    std::cout<<std::endl;
    }
     std::cout<<std::endl;
}

template<typename V, typename E>
 bool Graph<V,E>::removeVertex(std::size_t vertex_id){

        if(vertices.size() <= vertex_id){
            return false;
        }
        else
            edges[vertex_id].resize(0);
            return true;

 }
template<typename V, typename E>
std::size_t Graph<V,E>::nrOfVertices() const{
    return vertices.size();
}

template<typename V, typename E>
std::size_t Graph<V,E>::nrOfEdges() const{
    int i=0;
    for (i1 : edges){
        for( i2 : i1){
            if(i2 != 0) i++;
        }
    }
    return i;
}





int main()
{
    Graph<std::string, int> g;
    g.insertVertex("V1");
    g.insertVertex("V2");
    g.insertVertex("V3");
    g.insertVertex("V4");
    g.insertEdge(0, 0, 1);
    g.insertEdge(0, 1, 2);
    g.insertEdge(1, 2, 3);
    g.insertEdge(2, 2, 4);
    g.insertEdge(3, 2, 5);
    g.insertEdge(3, 0, 6);
    g.insertEdge(0, 3, 7);
    g.insertEdge(1, 3, 8);

     g.printNeighborhoodMatrix();
    std::cout << (g.removeEdge(0, 1) ? "Udalo sie" : "Nie udalo sie") << std::endl;
        g.printNeighborhoodMatrix();
    std::cout << (g.removeEdge(1, 0) ? "Udalo sie" : "Nie udalo sie") << std::endl;
        g.printNeighborhoodMatrix();
    std::cout << (g.removeVertex(2) ? "Udalo sie" : "Nie udalo sie") << std::endl;
     g.printNeighborhoodMatrix();
   std::cout << (g.removeVertex(5) ? "Udalo sie" : "Nie udalo sie") << std::endl;
     g.printNeighborhoodMatrix();
    std::cout << "Nr of vertices: " << g.nrOfVertices() << std::endl;
    std::cout << "Nr of edges: " << g.nrOfEdges() << std::endl;
    //g.printNeighborhoodMatrix();
    return 0;
}
