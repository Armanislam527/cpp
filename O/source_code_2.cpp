#include <iostream>
	using namespace std;

	int main() {
	    int A[] = {1, 2, 3};
	    int B[] = {1, 2};
 	   int matrix[3][2] = {0};

  	  cout << "Ordered pairs in relation R (a > b):\n";
   	 for (int i = 0; i < 3; i++) {
    	    for (int j = 0; j < 2; j++) {
    	        if (A[i] > B[j]) {
    	            cout << "(" << A[i] << ", " << B[j] << ")\n";
     	           matrix[i][j] = 1;
      	      }
      	  }
   	 }

   	 cout << "\nMatrix Representation:\n";
   	 for (int i = 0; i < 3; i++) {
   	     for (int j = 0; j < 2; j++) {
   	         cout << matrix[i][j] << " ";
    	    }
     	   cout << endl;
   	 }

   	 return 0;
	}