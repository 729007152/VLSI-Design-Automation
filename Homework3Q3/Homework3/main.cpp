#include<iostream>
#include<climits>

using namespace std;

/**  @Brief: At a given node location, this function will iterate through all the nodes in the graph and check to see which ones are neighboring
  *          the current node(i.e share an edge with the current node). Then out of all the neighboring nodes, this function will pick the closest
  *          node to traverse.
  *  @Input:  distanceFromSource-Indicates the current distance from the source node
  *          visited-Array keeping track of which node has been visited
  *          numNodes-How many node are in the graph
  *  @Return: closestNeighborNode-Which node is the closest to the current node
  */
int shortestNodeSearch(int* distanceFromSource, bool* visited, int numNodes){    //search for the next node with the shortest distance
    int closestNeighborNode = -1;
    for(int candidateNode=0; candidateNode<numNodes; candidateNode++){
        if(!visited[candidateNode] && (closestNeighborNode==-1 || distanceFromSource[candidateNode] < distanceFromSource[closestNeighborNode])){ // if node i hasn't been visited and is not initialized or if current minimum node is shorter then out previous then update minVertex with i
            closestNeighborNode = candidateNode;
        }
    }
    return closestNeighborNode;
}

/**  @Brief: This function performs Dijkstra's Algorithm. It traverses the graph by starting
  *           at the source node(node 6) and jumps to the next node by checking to see which neighboring
  *           no is the closest and has never been visited.
  *  @Input:  edge-2d array that holds all existing edge weight/length in the graph
  *          visited-Array keeping track of which node has been visited
  *          numNodes-How many node are in the graph
  *  @Return: closestNeighborNode-Which node is the closest to the current node
  */
void dijkstra(int** edges, int numNodes){
    int* distance = new int[numNodes];
    bool* visited = new bool[numNodes];

    for(int i=0; i<numNodes; i++){
        distance[i] = INT_MAX;  // Set to infinity
        visited[i] = false;     // Initialize all nodes to 'not visited'
    }

    distance[5] = 0;            // source  node is node 6

    cout << "Path: ";

    for(int firstNode=0; firstNode<numNodes-1; firstNode++){
        int closestNode = shortestNodeSearch(distance, visited, numNodes);
        visited[closestNode] = true;
        for(int currentNode=0; currentNode<numNodes; currentNode++){
            if(edges[closestNode][currentNode] != 0 && !visited[currentNode]){ //Checks to see if there exist a shared edge between node 'i' and node 'j' and checks if node j was ever traversed
                int dist = distance[closestNode] + edges[closestNode][currentNode];
                if(dist < distance[currentNode]){ // Is the current node on a closer path?
                    distance[currentNode] = dist;
                }
            }
        }
        cout << closestNode + 1 << " ";
    }
    cout << endl;
    cout << "The following is a table of each node and its shortest distance from node 6" << endl;
    for(int i=0; i<numNodes; i++){
        cout << i + 1 << " " << distance[i] << endl;
    }
}

int main(){
    int numNodes=8;
    int** edges = new int*[numNodes];
    for(int i=0; i<numNodes; i++){
        edges[i] = new int[numNodes];
        for(int j=0; j<numNodes; j++){
            edges[i][j] = 0;
        }
    }
    // Insert edge length given in the problem
    // Note: All nodes must be subtracted by 1 since array indexing in cpp starts at zero
    // While out node's numbering starts at one.
    edges[6-1][1-1] = 7;
    edges[1-1][6-1] = 7;

    edges[6-1][3-1] = 3;
    edges[3-1][6-1] = 3;

    edges[1-1][3-1] = 4;
    edges[3-1][1-1] = 4;

    edges[1-1][2-1] = 3;
    edges[2-1][1-1] = 3;

    edges[1-1][4-1] = 7;
    edges[4-1][1-1] = 7;

    edges[1-1][7-1] = 8;
    edges[7-1][1-1] = 8;

    edges[2-1][3-1] = 4;
    edges[3-1][2-1] = 4;

    edges[2-1][4-1] = 1;
    edges[4-1][2-1] = 1;

    edges[2-1][5-1] = 8;
    edges[5-1][2-1] = 8;

    edges[2-1][7-1] = 3;
    edges[7-1][2-1] = 3;

    edges[3-1][4-1] = 6;
    edges[4-1][3-1] = 6;

    edges[4-1][5-1] = 2;
    edges[5-1][4-1] = 2;

    edges[5-1][7-1] = 4;
    edges[7-1][5-1] = 4;

    edges[5-1][8-1] = 6;
    edges[8-1][5-1] = 6;

    edges[4-1][7-1] = 5;
    edges[7-1][4-1] = 5;

    edges[7-1][8-1] = 9;
    edges[8-1][7-1] = 9;
    cout << endl;
    dijkstra(edges, numNodes);

    return 0;
}
