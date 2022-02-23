#include<stdio.h>
#include<omp.h>

// void merge(){

// }

int merge(int array[], int lowerLimit, int mid, int upperLimit){
    int i, j, k;
    // Storing the length of the 2 subarrays in size_1 & size_2
    int size_1, size_2;
    
    size_1 = mid - lowerLimit + 1;
    size_2 = upperLimit - mid;

    // Creating 2 temporary subarrays
    int leftSubArray[size_1], rightSubArray[size_2];

    // Copying data from 'array' to temporary subArrays

    for(i = 0; i < size_1; i++)
        leftSubArray[i] = array[lowerLimit + i];
    for(j = 0; j < size_2; j++)
        rightSubArray[j] = array[mid + 1 + j];

    // Merge the temporary subArrays into the initial array
    i = 0; // Initial index of the first subArray - leftSubArray
    j = 0; // Initial index of the second subArray - secondSubArray
    k = lowerLimit; // initial index of the merged subArray

    while(i < size_1 && j < size_2){
        if(leftSubArray[i] <= rightSubArray[j]){
            array[k] = leftSubArray[i];
            i++;
            k++;
        }
        else{
            array[k] = rightSubArray[j];
            j++;
            k++;
        }
    }

    // To copy any remaining elements in the leftSubArray - if any

    while(i < size_1){
        array[k] = leftSubArray[i];
        i++;
        k++;
    }

    // To copy any remaining elements in the rightSubArray - if any

    while(j < size_2){
        array[k] = rightSubArray[j];
        j++;
        k++;
    }
}


int mergeSort(int array[], int lowerLimit, int upperLimit){
    if (lowerLimit < upperLimit){
        int mid;

        #pragma omp parallel sections
        {

                // Determining the mid-value of the array size
                    mid = lowerLimit + (upperLimit - lowerLimit)/2;

                // Dividing the array into 2 halves to be sorted - using recursion
                #pragma omp section
                {
                    printf("Thread ID = %d, lowerLimit = %d, mid = %d\n", omp_get_thread_num(), lowerLimit, mid);
                    mergeSort(array, lowerLimit, mid);
                }
                #pragma omp section
                {
                    printf("Thread ID = %d, mid + 1 = %d, upperLimit = %d\n", omp_get_thread_num(), mid + 1, upperLimit);
                    mergeSort(array, mid + 1, upperLimit);
                }
        }
        // Calling the merge function to add the 2 sub-arrays
            merge(array, lowerLimit, mid, upperLimit);
    }
    else
        printf("The entered limit ranges are invalid \n");
}



void printArray(int array[], int size){
    int i;
    printf("The sorted array is now as follows  : ");
    for(i = 0; i < size; i++)
        printf("%d", array[i]);
    printf("\n");
}

int main(){
    // #pragma omp parallel{

    // }

    int size, array[100];

    // Defining the size of the array
    printf("Enter the size of the array : ");
    scanf("%d", &size);
    printf("Array Size is : %d\n", size);


    int i;
    printf("Enter the array elements : \n");
    // Taking array input
    for(i = 0; i < size; i++)
        scanf("%d", &array[i]);

    // Calling the mergeSort function
    mergeSort(array, 0, size - 1);
    printArray(array, size);
}