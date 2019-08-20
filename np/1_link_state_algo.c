/*
    Program: Link State Routing Algorithm
    Author: Gangadhara Shetty P J

    Algorithm:
    ---------
    1. Initialization
        N = {A}     // A is a root node.
    2. for all nodes v
         if v adjacent to A
         then D(v) = c(A,v)
         else D(v) = infinity
       loop
    3. find w not in N such that D(w) is a minimum.
    4. Add w to N
    5. Update D(v) for all v adjacent to w and not in N:
    6. D(v) = min(D(v) , D(w) + c(w,v))
    7. Until all nodes in N ( go to step 3 if there is a node which is not in network)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 9999

int cost[100][100], distance[100], nodes_added[100] = {0},
parent[100], source, num_nodes;

void initialize()
{
    int i;
    nodes_added[source] = 1;    // adding source node to a network
    parent[source] = source;      // making parent of source node as itself

    for(i=0; i<num_nodes; i++)
        if( cost[source][i] == INFINITY )   // STEP 2
            distance[i] = INFINITY;
        else
            distance[i] = cost[source][i], parent[i] = source;
}

int GetMinimumNodeNotInNetwork()
{
    int min = -1, i;
    for(i=0; i<num_nodes; i++)
    {
        if( !nodes_added[i] )   // to check nodes which are not added network
            if(min==-1) min = i;
            else if( distance[min] > distance[i] ) min=i;
    }
    return min;
}

// returns true if therre is any node which is not added to network
bool anyExtraNodes()
{
    int i;
    for(i=0; i<num_nodes; i++)
        if( !nodes_added[i] )
            return true;
    return false;
}

void updateDistanceForAdjacentNodes(int node)
{
    int i;
    for(i=0; i<num_nodes; i++)
    {
        if( cost[node][i] != INFINITY )
        {
            if(distance[i] > distance[node]+cost[node][i])  // STEP 6
in Algorithm
            {
                distance[i] = distance[node]+cost[node][i];
                parent[i] = node;
            }
        }
    }
}

/*
    backtracking path for each node
    ex: parent = {0, 0, 4, 0, 3, 4}
    path from 0 to 5 = parent[5] -> parent[parent[5]] ->
parent[parent[parent[5]]] .... till you get the source node in reverse
order
    parent[5] = 4
    parent[4] = 3
    parent[3] = 0
    so path is 0 -> 3 -> 4 -> 5
*/
void display()
{
    int i, node;
    printf("From:\tCost :\tPath\n");
    for(i=0; i<num_nodes; i++){
        printf("%d to %d\t%d :\t",source, i, distance[i]);

        printf("%d", node);
        while( node != source){
            printf(" <- %d", parent[node]);
            node = parent[node];
        }
        printf("\n");
    }
}

int main()
{
    int i, j, node;

    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);

    printf("Enter the source node: ");
    scanf("%d", &source);

    printf("Enter the cost matrix: \n");
    for(i=0; i<num_nodes; i++)
        for(j=0; j<num_nodes; j++)
            scanf("%d", &cost[i][j]);

    initialize();   // STEP 1 and 2 in Algorithm

    while( anyExtraNodes() )    // condition for STEP 7 in Algorithm
    {
        node = GetMinimumNodeNotInNetwork();    // STEP 3 in Algorithm

        nodes_added[node] = 1;  // STEP 4 in Algorithm

        updateDistanceForAdjacentNodes(node);   // STEP 4 and 5 in Algorithm
    }

    display();
    return 0;
}



/*

Sample Output:
--------------

Enter the number of nodes: 6
Enter the source node: 0
Enter the cost matrix:
0 2 5 1 9999 9999
2 0 3 2 9999 9999
5 3 0 3 1 5
1 2 3 0 1 9999
9999 9999 1 1 0 2
9999 9999 5 9999 2 0

From:   Cost :  Path
0 to 0  0 :     0
0 to 1  2 :     1 <- 0
0 to 2  3 :     2 <- 4 <- 3 <- 0
0 to 3  1 :     3 <- 0
0 to 4  2 :     4 <- 3 <- 0
0 to 5  4 :     5 <- 4 <- 3 <- 0

*/