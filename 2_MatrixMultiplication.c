#include<stdio.h>
#include<omp.h>


void displayMatrix(int resultantMatrix[], int rowSize){
    printf("\nThe Resultant Matrix is as follows : \n");
    int i;

    for(i = 0; i < rowSize; i++){
        printf(" %d ", resultantMatrix[i]);
    }
    printf("\n");
}


void matrixMultiplication(int matrix[][100], int rowSize, int columnSize, int vector[], int vectorSize){
    int parallelResult[100];
    int serialResult[100];
    int i, j, k;

    // Initialising the parallelResultl and serialResult values to = 0
    for(i = 0; i < rowSize; i++){
        parallelResult[i] = 0;
        serialResult[i] = 0;
    }

    // Multiplying the Matrix by the Vector using - Parallel Computation
    #pragma omp parallel for
    for(i = 0; i < rowSize; i++)
            for(j = 0; j < columnSize; j++){
        parallelResult[i] = parallelResult[i] + matrix[i][j] * vector[j];
    }

    // Multiplying the Matrix by the Vector using - Serial Computation

    for(i = 0; i < rowSize; i++)
        for(j = 0; j < columnSize; j++)
            serialResult[i] = serialResult[i] + matrix[i][j] * vector[j];


    // Calling the displayMatrix to display the parallelResult and serialResult
    displayMatrix(parallelResult, rowSize);
    displayMatrix(serialResult, rowSize);

    // To check whether the parallelResult and the serialResult obtained are the same or not
    for(i = 0; i < rowSize; i++){
        if(parallelResult[i] == serialResult[i])
            continue;
        else{
            printf("\nThe results obatined during the parallel computation is differen than that obtained during serial computation \n");
            break;
        }
    }
}

void main(){
    int rowSize, columnSize, vectorSize;
    int matrix[100][100], vector[100];

    // Defining the size of the Matrix and the Vector
    printf("Enter the Row and Column Size of the Matrix : ");
    scanf("%d %d", &rowSize, &columnSize);

    printf("\nEnter the size of the Vector : ");
    scanf("%d", &vectorSize);

    if(rowSize <= 0 || columnSize <= 0 || vectorSize <= 0){
        printf("\nPlease make sure that the size of the matrix or the vector is +ve \n");
    }
    else if(columnSize != vectorSize){
        printf("\nThe column size of the Matrix should be = to the size of the vector to be multiplied with\n");
    }
    else{
        printf("\nEnter the Matrix below : \n");
        int i, j;
        for(i = 0; i < rowSize; i++)
            for(j = 0; j < columnSize; j++)
                scanf("%d", &matrix[i][j]);


        printf("\nEnter the inputs for the Vector below : \n");
        for(i = 0; i < vectorSize; i++)
            scanf("%d", &vector[i]);

        // Displaying the Matrix and the Vector
        printf("\nThe Matrix is as follows : \n");
        for(i = 0; i < rowSize; i++)
            for(j = 0; j < columnSize; j++)
                printf("%d ", matrix[i][j]);
            print("\n");

        printf("\nThe Vector is as follows : \n");
        for(i = 0; i < vectorSize; i++)
            printf("%d ", vector[i]);

        // Calling the Matrix Multiplication function
        matrixMultiplication(matrix, rowSize, columnSize, vector, vectorSize);
    }
}
