#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    
    numVertices = vertexPositions.size(); 
    numEdges = edges.size();
    
    adjList.resize(numVertices);
    vertices.resize(numVertices);
    
    for (int i=0; i<numVertices; i++){
        // BE CAREFUL: VERTICES ARRAY CAN BE SPARSE, NOT EVERY INDEX IS A VERTEX
        vertices[i].id = i;
        vertices[i].position3D = vertexPositions[i];
    }
    for (int i=0; i<numEdges; i++){
        adjList[edges[i].vertexId0].push_back(&vertices[edges[i].vertexId1]);
        adjList[edges[i].vertexId1].push_back(&vertices[edges[i].vertexId0]);
    }
    
    /*std::list<Vertex*>::iterator pos = adjList[0].begin();
    for(; pos != adjList[0].end(); pos++)
    std::cout <<"id is: "<< (*pos)->id << std::endl;*/
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double totalDis = 0;
    for (int i=0; i<numVertices; i++){
        std::list<Vertex*> myList = adjList[i];
        for (std::list<Vertex*>::const_iterator iter = myList.begin();
        iter != myList.end(); ++iter){
            totalDis += vertices[i].position3D.Distance(vertices[i].position3D, (*iter)->position3D);
        }
    }
    return (double) (totalDis/2) / numEdges;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    return (double) numEdges / numVertices;
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return numVertices;
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    return numEdges;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    int verEdgeCount = 0;
    if (vertexId >= adjList.size() )
        return -1;

    for (std::list<Vertex*>::const_iterator iter = adjList[vertexId].begin();
        iter != adjList[vertexId].end(); iter++){
            verEdgeCount++;
        }
    return verEdgeCount;
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
        if (vertexId >= adjList.size() )
        return ;

    for (std::list<Vertex*>::const_iterator iter = adjList[vertexId].begin();
        iter != adjList[vertexId].end(); iter++){
            outVertexIds.push_back((*iter)->id);
        }
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    std::vector<double> distance;
    std::vector<int> previous;

    outputColorAllVertex.resize(numVertices);
    distance.resize(numVertices);
    previous.resize(numVertices);
    for (int i=0; i<numVertices; i++){
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    
    if (vertexIdFrom >= adjList.size() || vertexIdTo >= adjList.size())
        return ;
        
    BinaryHeap pq;
    for (int i=0; i<numVertices; i++){
        distance[i] = INFINITY; 
        previous[i] = -1; 
    }
    // Set the cost of the start vertex to zero
    distance[vertexIdFrom] = 0;
    // add all vertices to pq;
    for (int i=0; i<numVertices; i++){
        pq.Add(vertices[i].id, distance[i]);
    }
    
    while(pq.HeapSize() > 0) {
          // EXTRACT_MIN vertex at the head of PQ
          Vertex v;
          int outUniqueId = 0 ;
          double outWeight = 0;
          pq.PopHeap(outUniqueId, outWeight);
          v.id = outUniqueId;
          v.position3D = vertices[outUniqueId].position3D;
         
        // search neighbors
        std::list<Vertex*> myList = adjList[v.id];
        // for each neighbour w of v
        for (std::list<Vertex*>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter){
            double new_dist = distance[v.id] + vertices[v.id].position3D.Distance(vertices[v.id].position3D, (*iter)->position3D);
              // relaxation
              if (new_dist < distance[(*iter)->id] ) {
                 // DECREASE_KEY
                 // update
                 distance[(*iter)->id] = new_dist;
                 previous[(*iter)->id] = v.id;
                 // may require bubbleUp
                 pq.ChangePriority((*iter)->id,new_dist);
              }
        }
    }
    int index = vertexIdTo;
    while(index >= 0){
        outputColorAllVertex[index].r = color.r;
        outputColorAllVertex[index].g = color.g;
        outputColorAllVertex[index].b = color.b;
        index = previous[index];
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
      std::vector<int> previous;
    std::vector<bool> mark;
    std::vector<int> depthVec;
    //std::cout<<maxDepth<<std::endl;

    outputColorAllVertex.resize(numVertices);
    previous.resize(numVertices);
    mark.resize(numVertices);
    depthVec.resize(numVertices);
    for (int i=0; i<numVertices; i++){
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    
    if (vertexId >= adjList.size())
        return ;
        
    for (int i=0; i<numVertices; i++){
        previous[i] = -1;
        mark[i] = false;
        depthVec[i] = -1;
    }
    int depth = -1;
    BinaryHeap pq;
    int myWeight = 0;
	pq.Add(vertexId, myWeight++);
	depthVec[vertexId] = depth+1;
	
	mark[vertexId] = true;
    int tempVertex;
   
    while (pq.HeapSize() > 0){
	    Vertex v;
        int outUniqueId = 0;
        double outWeight = 0;
        pq.PopHeap(outUniqueId, outWeight);
        v.id = outUniqueId;
        v.position3D = vertices[outUniqueId].position3D;
        
        // ------------- COLORING --------------------------- 
        // **************************************************
        double distance = 0;
        double multiply = 0;
        int index = v.id;
        //std::cout<<depthVec[v.id]<<std::endl;
        
        int first_index = v.id;
        int second_index = previous[first_index];
        
        while(first_index >= 0 && second_index>=0){
            distance += vertices[v.id].position3D.Distance(vertices[first_index].position3D, vertices[second_index].position3D);
            first_index = second_index;
            second_index = previous[second_index];
        }

        if (type == FILTER_GAUSSIAN){
            multiply = (double) 1 / std::exp(((double) (distance*distance) / (alpha*alpha)));
        }
        if (type == FILTER_BOX){
            multiply = ((distance<=alpha && -1 *alpha<=distance) ? 1: 0);
        }
        outputColorAllVertex[v.id].r = (unsigned char) (((double) color.r) * multiply);
        outputColorAllVertex[v.id].g = (unsigned char) (((double)  color.g) * multiply);
        outputColorAllVertex[v.id].b = (unsigned char) (((double) color.b) * multiply);
        // *****************************************************
        // ---------------------------------------------------- 
            
	    std::list<Vertex*> myList = adjList[v.id];  // sort myList to have increasing ids
	   
	    // myList.sort();
	    
	    std::vector<int> sortedIndices;
	    
	    for (std::list<Vertex*>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter){
            sortedIndices.push_back((*iter)->id);
	    }
	    
	    int i, j;
        bool swapped;
        for (i = 0; i < sortedIndices.size()-1; i++)
        {
            swapped = false;
            for (j = 0; j < sortedIndices.size()-i-1; j++)
            {
                if (sortedIndices[j] > sortedIndices[j+1])
                {
                    int temp = sortedIndices[j];
                    sortedIndices[j] = sortedIndices[j+1];
                    sortedIndices[j+1] = temp;
                   swapped = true;
                }
            }
     
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        }
        depth = depthVec[v.id];
		for (int i=0; i<sortedIndices.size(); i++){
		    tempVertex = sortedIndices[i];
			if (!mark[tempVertex]){
                mark[tempVertex] = true;
		        previous[tempVertex] = v.id ;
		        if (depth + 1 <= maxDepth)
		            pq.Add(tempVertex, myWeight++);
		        depthVec[tempVertex] = depth+1;
            }
		}

		
		/*
		depth = depthVec[v.id];
		for (std::list<Vertex*>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter){
            tempVertex = (*iter)->id;
			if (!mark[tempVertex]){
                mark[tempVertex] = true;
		        previous[tempVertex] = v.id ;
		        if (depth + 1 <= maxDepth)
		            pq.Add(tempVertex, myWeight++);
		        depthVec[tempVertex] = depth+1;
            }
		}
		*/
		
		 sortedIndices.resize(0);
	}

}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
        std::vector<int> previous;
    std::vector<bool> mark;
    std::vector<int> depthVec;
    //std::cout<<maxDepth<<std::endl;

    outputColorAllVertex.resize(numVertices);
    previous.resize(numVertices);
    mark.resize(numVertices);
    depthVec.resize(numVertices);
    for (int i=0; i<numVertices; i++){
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }
    
    if (vertexId >= adjList.size())
        return ;
        
    for (int i=0; i<numVertices; i++){
        previous[i] = -1;
        mark[i] = false;
        depthVec[i] = -1;
    }
    int depth = -1;
    BinaryHeap pq;
    int myWeight = 0;
	pq.Add(vertexId, myWeight++);
	depthVec[vertexId] = depth+1;
	
	mark[vertexId] = true;
    int tempVertex;
   
    while (pq.HeapSize() > 0){
	    Vertex v;
        int outUniqueId = 0;
        double outWeight = 0;
        pq.PopHeap(outUniqueId, outWeight);
        v.id = outUniqueId;
        v.position3D = vertices[outUniqueId].position3D;
        
        // ------------- COLORING --------------------------- 
        // **************************************************
        double distance = 0;
        double multiply = 0;
        int index = v.id;
        //std::cout<<depthVec[v.id]<<std::endl;
        
        distance = vertices[v.id].position3D.Distance(vertices[v.id].position3D, vertices[vertexId].position3D);

        if (type == FILTER_GAUSSIAN){
            multiply = (double) 1 / std::exp(((double) (distance*distance) / (alpha*alpha)));
                    outputColorAllVertex[v.id].r = (unsigned char) (((double) color.r) * multiply);
        outputColorAllVertex[v.id].g = (unsigned char) (((double)  color.g) * multiply);
        outputColorAllVertex[v.id].b = (unsigned char) (((double) color.b) * multiply);
        }
        if (type == FILTER_BOX){
            if (distance<=alpha && -1 *alpha<=distance){
                                multiply = 1;
                outputColorAllVertex[v.id].r = color.r;
                outputColorAllVertex[v.id].g = color.g;
                outputColorAllVertex[v.id].b = color.b;
            }

            else{
                                multiply = 0;
            // multiply = ((distance<=alpha && -1 *alpha<=distance) ? 1: 0);
            }

        }

        // *****************************************************
        // ---------------------------------------------------- 
            
	    std::list<Vertex*> myList = adjList[v.id];  // sort myList to have increasing ids
	   
	    // myList.sort();
	    
	    std::vector<int> sortedIndices;
	    
	    for (std::list<Vertex*>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter){
            sortedIndices.push_back((*iter)->id);
	    }
	    
	    int i, j;
        bool swapped;
        for (i = 0; i < sortedIndices.size()-1; i++)
        {
            swapped = false;
            for (j = 0; j < sortedIndices.size()-i-1; j++)
            {
                if (sortedIndices[j] > sortedIndices[j+1])
                {
                    int temp = sortedIndices[j];
                    sortedIndices[j] = sortedIndices[j+1];
                    sortedIndices[j+1] = temp;
                   swapped = true;
                }
            }
     
            // IF no two elements were swapped by inner loop, then break
            if (swapped == false)
                break;
        }
        depth = depthVec[v.id];
		for (int i=0; i<sortedIndices.size(); i++){
		    tempVertex = sortedIndices[i];
			if (!mark[tempVertex]){
                mark[tempVertex] = true;
		        previous[tempVertex] = v.id ;
		        if (depth + 1 <= maxDepth)
		            pq.Add(tempVertex, myWeight++);
		        depthVec[tempVertex] = depth+1;
            }
		}

		
		/*
		depth = depthVec[v.id];
		for (std::list<Vertex*>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter){
            tempVertex = (*iter)->id;
			if (!mark[tempVertex]){
                mark[tempVertex] = true;
		        previous[tempVertex] = v.id ;
		        if (depth + 1 <= maxDepth)
		            pq.Add(tempVertex, myWeight++);
		        depthVec[tempVertex] = depth+1;
            }
		}
		*/
		
		 sortedIndices.resize(0);
	}
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}