#include <bits/stdc++.h>
#include <iostream>

using namespace std;

// Function to return the index of the
// parent node of a given node
int parent(int i) {
    return (i - 1) / 2;
}

// Function to return the index of the
// left child of the given node
int leftChild(int i) {
    return ((2 * i) + 1);
}

// Function to return the index of the
// right child of the given node
int rightChild(int i){
    return ((2 * i) + 2);
}

// Function to shift up the node in order
// to maintain the heap property
void shiftUp(int i, vector<int> &arr) {
    while (i > 0 && arr[parent(i)] < arr[i]) {

        // Swap parent and current node
        swap(arr[parent(i)], arr[i]);

        // Update i to parent of i
        i = parent(i);
    }
}

// Function to shift down the node in
// order to maintain the heap property
void shiftDown(int i, vector<int> &arr, int &size) {
    int maxIndex = i;

    // Left Child
    int l = leftChild(i);

    if (l <= size && arr[l] > arr[maxIndex]) {
        maxIndex = l;
    }

    // Right Child
    int r = rightChild(i);

    if (r <= size && arr[r] > arr[maxIndex]) {
        maxIndex = r;
    }

    // If i not same as maxIndex
    if (i != maxIndex) {
        swap(arr[i], arr[maxIndex]);
        shiftDown(maxIndex, arr, size);
    }
}

// Function to insert a new element
// in the Binary Heap
void insert(int p, vector<int> &arr, int &size) {
    size = size + 1;
    arr.push_back(p);

    // Shift Up to maintain heap property
    shiftUp(size, arr);
}

// Function to extract the element with
// maximum priority
int extractMax(vector<int> &arr, int &size) {
    int result = arr[0];

    // Replace the value at the root
    // with the last leaf
    arr[0] = arr[size];
    size = size - 1;

    // Shift down the replaced element
    // to maintain the heap property
    shiftDown(0, arr, size);
    return result;
}

// Function to change the priority
// of an element
void changePriority(int i, int p, vector<int> &arr, int &size) {
    int oldp = arr[i];
    arr[i] = p;

    if (p > oldp) {
        shiftUp(i, arr);
    }
    else {
        shiftDown(i, arr, size);
    }
}

// Function to get value of the current
// maximum element
int getMax(vector<int> &arr) {
    return arr[0];
}

// Function to remove the element
// located at given index
void remove(int i, vector<int> &arr, int &size) {
    arr[i] = getMax(arr) + 1;

    // Shift the node to the root
    // of the heap
    shiftUp(i, arr);

    // Extract the node
    extractMax(arr, size);
}

int main() {

    /*         45
            /      \
           31      14
          /  \    /  \
         13  20  7   11
        /  \
       12   7
    Create a priority queue shown in
    example in a binary max heap form.
    Queue will be represented in the
    form of array as:

    45 31 14 13 20 7 11 12 7 */

    // Insert the element to the
    // priority queue

    vector<int> arr;
    int size = -1;
    insert(45, arr, size);
    insert(20, arr, size);
    insert(14, arr, size);
    insert(12, arr, size);
    insert(31, arr, size);
    insert(7, arr, size);
    insert(11, arr, size);
    insert(13, arr, size);
    insert(7, arr, size);

    int i = 0;

    // Priority queue before extracting max
    cout << "Priority Queue : ";
    while (i <= size) {
        cout << arr[i] << " ";
        i++;
    }

    cout << endl;

    // Node with maximum priority
    cout << "Node with maximum priority : "
         << extractMax(arr, size) << endl;

    // Priority queue after extracting max
    cout << "Priority queue after "
         << "extracting maximum : ";
    int j = 0;
    while (j <= size) {
        cout << arr[j] << " ";
        j++;
    }

    cout << endl;

    // Change the priority of element
    // present at index 2 to 49
    changePriority(2, 49, arr, size);
    cout << "Priority queue after "
         << "priority change : ";
    int k = 0;
    while (k <= size) {
        cout << arr[k] << " ";
        k++;
    }

    cout << endl;

    // Remove element at index 3
    remove(3, arr, size);
    cout << "Priority queue after "
         << "removing the element : ";
    int l = 0;
    while (l <= size) {
        cout << arr[l] << " ";
        l++;
    }
    return 0;
}
