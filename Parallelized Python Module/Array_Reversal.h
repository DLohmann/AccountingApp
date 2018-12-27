
#include <thread>
//#define debug_reversal

#ifdef debug_reversal
#include <stdio.h>
#endif


//#include <Python.h>

/*
The purpose of this module is to learn 
- Python extensions in C++
- Multithreaded programming in C++
- SSE Instructions for Intel processors in C++
- C++ standard templates that can be compiled for different parameter types.

The task is to reverse an array
*/


/*
static PyObject * reverseArray (PyObject * self, PyObject * args) {
	const char * command;
	int sts;
	if (!PyArg_ParseTuple(args, "s????? array??????", &command)) {
		return NULL;
	}
	sts = system(command);
	
	
}
*/

// The most simple and basic array reversal algorithm
int basic_reversal (int * arr, int length) {
	#ifdef debug_reversal
	printf ("Basic reversal called!!! arr = %p, length = %d\n", arr, length);
	#endif
	int temp;
	for (int i = 0; i < (length/2); i++) {
		
		#ifdef debug_reversal
		printf ("arr[%d] = %d\n", i, arr[i]);
		#endif
		
		temp = arr[i];
		arr[i] = arr[length - 1 - i];
		arr[length - 1 - i] = temp;
	}
	return 0;
}

/*
void thread_reverse (int thr_id , int ** thread_begin_sections, int ** thread_end_sections, int length ) {
	int * front_ptr = thread_begin_sections[thr_id];
	int * back_ptr = thread_end_sections[thr_id];
	while (front_ptr < thread_end_sections[thr_id]) {
		
		
	}
	
}
*/

/*
void thread_reverse (int thread_id, int * arr, int length) {
	int * startPtr = arr + thread_id*length
}
*/


void thread_reverse (int thread_id, int * arr, int length, int startIndex, int endIndex) {
	for (int i = startIndex; i <= endIndex; i++) {
		int temp = arr[i];
		arr[i] = arr[length - 1 - i];
		arr[length - 1 - i] = temp;
	}
}

void helloWorld () {
	printf("Hello World!\n");
}

// [0, 1, 2, ..., N/4, ..., N/2, ..., 3*N/4, ..., N-2, N-1], length = N
//  ^leftPtr      ^leftMidPtr
int multithreaded_reversal (int * arr, int length) {
	
	// For every 200 elements, allocate a thread to reverse them. 
	// Complexity TODO: Limit this to at most 4 threads?
	// Optimization TODO: Find the critical number of elements N, so that for every N elements in the array, a new thread should be allocated.
	int numThreads = 2;	//length/200;
	std::thread reversing_threads [2];

	// Create and set each thread
	int reverseChunkSize = length / (2*numThreads); // Each thread gets an equal amount of elements to reverse. 
	for (int i = 0; i < numThreads; i++) {
		// 2nd version of thread_reverse
		//reversing_threads[i] = thread(thread_reverse, i, arr, length);
		

		// 3rd version of thread_reverse
		int startIndex =  i    * reverseChunkSize;
		int endIndex   = (i+1) * reverseChunkSize;
		reversing_threads[i] = std::thread(helloWorld);
		//reversing_threads[i] = std::thread(thread_reverse, i, arr, length, startIndex, endIndex);
		
	}
	
	// TODO: Reverse all threads in the middle of the array (if the array is not a multiple of 2*200, then there will be some (less than 200) unreversed elements here)


	//Join the main thread to all the reversing threads
	for (int i = 0; i < numThreads; i++) {
		reversing_threads[i].join();
	}

	// 1st version of thread_reverse
	
	//int * leftPtr = arr;
	//int * leftMidPtr = arr + length/4;
	
	// Each thread reverses the elements from it's begin section to it's end section
	//int * thread_begin_sections [] = {arr,            arr + length/4};
	//int * thread_end_sections   [] = {arr + length/4, arr + length/2};
	
	//thread
	
	//int * rightPtr = arr + length - 1;
	
	
	
	
	//thread leftThread;
	
	return 0;
}

int reverseArray (int * arr, int length) {
	
	//return basic_reversal (arr, length);
	multithreaded_reversal(arr, length);
	//return 0; // Return 0 if no error
}

