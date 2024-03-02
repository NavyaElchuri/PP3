#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void HW3(int SOURCE, int n, int edge[n][n], int *distance) {
    int i, j, count, tmp, least, leastPos;
    int *found = (int *)calloc(n, sizeof(int));

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        found[i] = 0;
        distance[i] = edge[SOURCE][i];
    }

    found[SOURCE] = 1;
    count = 1;

    while (count < n) {
        least = 987654321;
        
        #pragma omp parallel for private(tmp) // Parallelize this loop and make 'tmp' private to each thread
        for (i = 0; i < n; i++) {
            if (!found[i]) {
                tmp = distance[i];
                if (tmp < least) {
                    least = tmp;
                    leastPos = i;
                }
            }
        }

        found[leastPos] = 1;
        count++;

        #pragma omp parallel for // Parallelize this loop
        for (i = 0; i < n; i++) {
            if (!found[i]) {
                distance[i] = fmin(distance[i], least + edge[leastPos][i]);
            }
        }
    } /* End of while */

    free(found);
}

int main() {
    int n = 6; // Number of vertices
    int SOURCE = 0; // Source vertex

    int edge[6][6]; // Define and initialize the edge matrix (replace with your data)
    edge[0][0] = 0; edge[0][1] = 2; edge[0][2] = 1; edge[0][3] = 4; edge[0][4] = 5; edge[0][5] = 6; 
    edge[1][0] = 2; edge[1][1] = 0; edge[1][2] = 5; edge[1][3] = 5; edge[1][4] = 9; edge[1][5] = 7;
    edge[2][0] = 1; edge[2][1] = 5; edge[2][2] = 0; edge[2][3] = 3; edge[2][4] = 2; edge[2][5] = 11;
    edge[3][0] = 4; edge[3][1] = 5; edge[3][2] = 3; edge[3][3] = 0; edge[3][4] = 1; edge[3][5] = 6;
    edge[4][0] = 5; edge[4][1] = 9; edge[4][2] = 2; edge[4][3] = 1; edge[4][4] = 0; edge[4][5] = 4;
    edge[5][0] = 6; edge[5][1] = 7; edge[5][2] = 11; edge[5][3] = 6; edge[5][4] = 4; edge[5][5] = 0;
    // Fill the edge matrix with appropriate values
    // Example: Replace this with your actual edge weights
  

    int distance[6]; // Assuming 'n' is 6 in this example

    // Call Dijkstra's algorithm
    HW3(SOURCE, n, edge, distance);

    // Print the calculated distances
    printf("Calculated Distances:\n");
    for (int i = 0; i < n; i++) {
        printf("Distance from vertex %d to vertex %d: %d\n", SOURCE, i, distance[i]);
    }

    return 0;
}
