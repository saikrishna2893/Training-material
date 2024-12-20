#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void danglingPointer() {
    int* ptr = new int(42);
    std::cout <<"memory address: "<< ptr << " value: "<< *ptr << std::endl;
    delete ptr;  // Memory is deallocated
    cout << "value after freeing up pointer: " << *ptr << endl;  // Dangling pointer usage: Undefined behavior
    //ptr = nullptr; //Set the pointer to nullptr after freeing it.
    //Use smart pointers (e.g., std::unique_ptr or std::shared_ptr) in C++.
}

void allocateMemory(int** ptr) {
    //Stack allocation
    int a = 10;
    int * ptr1 = &a;
    //Heap allocation (Dynamic allocation) : new/malloc/calloc
    *ptr = new int(42); // Initializes to zero by default
    cout << "Printing values of ptr" << endl;
    std::cout <<"Zero value: "<< **ptr <<" first value"<< (*ptr)[0] <<" Second value: " << (*ptr)[1] << std::endl;

    // *ptr = (int*)calloc(42, sizeof(int));
    int* arr = (int*)malloc(5);//calloc(5, sizeof(int)) // Allocate memory for an array
    cout << "values of pointer" << endl;
    for (int i = 0; i < 5; ++i)
    {
      cout << arr[i] << "\t";
    }
    delete[] arr; // Free memory
}

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

void useSmartPointer() {
    unique_ptr<int> ptr = make_unique<int>(42);
    cout << "smart pointer Value: " << *ptr << endl;
}

void swap(int* a, int* b){
  //Function to be filled
  int t = *b;
  *b = *a;
  *a = t;
}

void printValue(void* ptr, char type) {
    if (type == 'i')
        cout << "Integer: " << *(int*)ptr << endl;
    else if (type == 'f')
        cout << "Float: " << *(float*)ptr << endl;
}


template <typename T>
class SharedPtr {
    T* ptr;
    int* refCount;

public:
    SharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)) {}

    SharedPtr(const SharedPtr& sp) {
        ptr = sp.ptr;
        refCount = sp.refCount;
        (*refCount)++;
    }

    ~SharedPtr() {
        (*refCount)--;
        if (*refCount == 0) {
            delete ptr;
            delete refCount;
        }
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};


int main() {

    //Dangling pointer
    danglingPointer();

    //Pointer arithmetic
    int arr[] = {10, 20, 30};
    int* ptr = arr;

    cout << "Initial value: " << *ptr << " Initial address: " << ptr << endl;
    ptr++;  // Move to the next integer
    cout << "After increment: " << *ptr << " Address after increment: " << ptr << endl;

    //Double pointers
    int* p = nullptr;
    allocateMemory(&p);  // Passing the address of the pointer
    cout << "Allocated memory value: " << *p << endl;
    delete p;  // Free allocated memory

    //Function pointers
    int (*operation)(int, int);  // Function pointer declaration
    operation = add;
    cout << "Addition: " << operation(3, 4) << endl;

    operation = multiply;
    cout << "Multiplication: " << operation(3, 4) << endl;

    // Smart pointers: manage the lifetime of dynamically allocated memory 
    // and ensure proper deallocation. They reduce the risk of memory leaks and dangling pointers.
    useSmartPointer();  // Memory automatically freed

    //C++ program to swap two integers using pointers.
    int x = 10, y = 20;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(&x, &y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    //Void pointers
    // void* is a generic pointer type in C/C++ that can point to any data type. 
    // However, it cannot be dereferenced directly and requires type casting.
    int i = 42;
    float f = 3.14;

    printValue(&i, 'i');
    printValue(&f, 'f');

    //Shared Pointer
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2 = sp1;
    cout << *sp1 << endl;

    //Exception handling
    try {
      int* bigArray = new int[1000000000000]; //May throw a bad_alloc
      int v = 100;
      int a = 0;
      //cout << v/a << endl;
    } catch (const std::exception& e) {
      //std::cerr << "Exception: " << e.what() << std::endl;
      std::cout << "Exception: " << e.what() << std::endl;
}

_CrtDumpMemoryLeaks();

    return 0;
}

