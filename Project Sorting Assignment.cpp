#include <iostream>
#include <chrono> 
using namespace std;

// Function to print the array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " "; // Print each element of the array followed by a space
    }
    cout << endl; // Move to the next line after printing all elements
}

// Insertion Sort
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i]; // Store the current element in a temporary variable
        int j = i - 1; // Initialize a variable to track the position to insert the key

        // Move elements greater than the key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift the element to the right
            j--; // Move to the previous position
        }

        arr[j + 1] = key; // Insert the key at the correct position
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Calculate the size of the left subarray
    int n2 = right - mid; // Calculate the size of the right subarray

    int* L = new int[n1]; // Create a temporary array for the left subarray
    int* R = new int[n2]; // Create a temporary array for the right subarray

    // Copy data to the temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i]; // Copy elements from the original array to the left subarray
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i]; // Copy elements from the original array to the right subarray
    }

    int i = 0, j = 0, k = left; // Initialize pointers for merging

    // Merge the left and right subarrays into the original array in sorted order
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // If the left element is smaller, copy it to the original array
            i++;
        }
        else {
            arr[k] = R[j]; // If the right element is smaller, copy it to the original array
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[] and R[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the memory used by the temporary arrays
    delete[] L;
    delete[] R;
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calculate the middle index

        // Recursively sort the two halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    const int maxSize = 1000; // Maximum size of the arrays

    // Arrays to store data
    int arr10[maxSize] = { /* put your 10 elements here */ }; // Initialize with 10 elements (to be provided)
    int arr100[maxSize] = { /* put your 100 elements here */ }; // Initialize with 100 elements (to be provided)
    int arr1000[maxSize] = { /* put your 1000 elements here */ }; // Initialize with 1000 elements (to be provided)

    // Sorting and timing for 10 elements
    cout << "Sorting and timing for 10 elements:" << endl;
    auto startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    insertionSort(arr10, 10); // Sort the array using Insertion Sort
    auto endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    double timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Insertion Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting
    printArray(arr10, 10); // Print the sorted array

    startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    mergeSort(arr10, 0, 9); // Sort the array using Merge Sort
    endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Merge Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting
    printArray(arr10, 10); // Print the sorted array

    // Sorting and timing for 100 elements
    cout << "\nSorting and timing for 100 elements:" << endl;
    startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    insertionSort(arr100, 100); // Sort the array using Insertion Sort
    endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Insertion Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting

    startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    mergeSort(arr100, 0, 99); // Sort the array using Merge Sort
    endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Merge Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting

    // Sorting and timing for 1000 elements
    cout << "\nSorting and timing for 1000 elements:" << endl;
    startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    insertionSort(arr1000, 1000); // Sort the array using Insertion Sort
    endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Insertion Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting

    startTime = chrono::high_resolution_clock::now(); // Get the current time before starting the sorting
    mergeSort(arr1000, 0, 999); // Sort the array using Merge Sort
    endTime = chrono::high_resolution_clock::now(); // Get the current time after sorting
    timeElapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() / 1000000.0; // Calculate the time elapsed in seconds
    cout << "Merge Sort Time: " << timeElapsed << " seconds" << endl; // Print the time taken for sorting

    return 0;
}
