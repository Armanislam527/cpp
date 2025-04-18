#include <iostream>
	using namespace std;

	int main() {
	    int A[] = {1, 2, 3, 4};
	    int n = 4;

	    cout << "Relation R1 (a divides b):\n";
    	for (int i = 0; i < n; i++) {
      	  for (int j = 0; j < n; j++) {
  	          if (A[j] % A[i] == 0) {
   	             cout << "(" << A[i] << ", " << A[j] << ") ";
    	        }
   	     }
 	   }

    	cout << "\n\nRelation R2 (a <= b):\n";
  	  for (int i = 0; i < n; i++) {
    	    for (int j = 0; j < n; j++) {
      	      if (A[i] <= A[j]) {
      	          cout << "(" << A[i] << ", " << A[j] << ") ";
        	    }
    	    }
  	  }

  	  return 0;
	}