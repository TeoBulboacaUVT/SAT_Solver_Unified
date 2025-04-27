#include <iostream>
#include <algorithm> // for std::swap
#include <chrono> // For measuring execution time
using namespace std;

class cset {
public:
    cset(); // Default constructor
    ~cset(); // Destructor to free memory
    void append(int element); // Append a single element
    void append(const cset& otherList); // Append another list
    int length(); // Get the number of elements
    void reverse(); // Reverse the list
    friend void print(const cset& list); // Friend function to print the list

private:
    int *a; // Pointer to dynamically allocated array
    int len; // Number of elements in the list
    int capacity; // Current capacity of the array
    void resize(); // Resize the array when full
};

// Default constructor
cset::cset() {
    len = 0; // Initialize the list length to 0
    capacity = 10; // Initial capacity
    a = new int[capacity]; // Allocate memory for the array
}

// Destructor to free memory
cset::~cset() {
    delete[] a; // Free the allocated memory
}

// Resize the array when it's full
void cset::resize() {
    capacity *= 2; // Double the capacity
    int *newArray = new int[capacity]; // Allocate a new array
    for (int i = 0; i < len; i++) {
        newArray[i] = a[i]; // Copy elements to the new array
    }
    delete[] a; // Free the old array
    a = newArray; // Update the pointer to the new array
}

// Append a single element to the list
void cset::append(int element) {
    if (len == capacity) { // Check if the array is full
        resize(); // Resize the array
    }
    a[len] = element;
    len++;
}

// Append another list to the current list
void cset::append(const cset& otherList) {
    for (int i = 0; i < otherList.len; i++) {
        append(otherList.a[i]); // Use the existing append method
    }
}

// Get the number of elements in the list
int cset::length() {
    return len;
}

// Reverse the elements in the list
void cset::reverse() {
    for (int i = 0; i < len / 2; i++) {
        swap(a[i], a[len - i - 1]);
    }
}

// Friend function to print the list
void print(const cset& list) {
    cout << "[";
    for (int i = 0; i < list.len; i++) {
        cout << list.a[i];
        if (i < list.len - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Main function to test the cset class
int main() {
    auto start = chrono::high_resolution_clock::now(); // Start the timer

    cset a, b;

    a.append(3);
    a.append(2);
    print(a); // Should print [3, 2]

    b.append(4);
    b.append(6);
    a.append(b);
    print(a); // Should print [3, 2, 4, 6]

    cout << "Length is " << a.length() << endl; // Should print "Length is 4"

    a.reverse();
    print(a); // Should print [6, 4, 2, 3]

    // Test dynamic resizing
    for (int i = 0; i < 20; i++) {
        a.append(i);
    }
    print(a); // Should print a longer list

    auto end = chrono::high_resolution_clock::now(); // End the timer
    chrono::duration<double> elapsed = end - start; // Calculate elapsed time
    cout << "Execution time: " << elapsed.count() << " seconds" << endl;

    return 0;
}