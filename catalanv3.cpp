#include <stdlib.h>
#include <assert.h>
#include <cstdint>
#include <iostream>
#include <vector>
#include <stack>

// this is actually catalan-1 for the purpose of counting array.
using namespace std;

unsigned long int catalan(int n)
{
  // Base case
  if (n <= 1) return 1;

  // catalan(n) is sum of catalan(i)*catalan(n-i-1)
  unsigned long int res = 0;
  for (int i=0; i<n; i++)
    res += catalan(i)*catalan(n-i-1);

  return res;
}

int prevCat = 0;
vector<int *> all_ptrs;
stack<int> kstack;

void triangulation(int n){

  auto *prev = all_ptrs[n-6];
  const int cn = n-3;
  const int currCat = catalan(n-2);

  int* curr = (int*)malloc(currCat * cn * 2 * sizeof(int));

  all_ptrs.vector::push_back(curr);

  int rowToFill=0, k=0;

  for (unsigned long int i = 0; i<prevCat; i++){
  // for every t
      kstack.push(0);
      kstack.push(n-3);
      for (int j =0; j<n-4; j++){ 
      // k from 1 to n-3, find (k,n-2)
      // if find k
        auto p = std::min(prev[i*(n-4)*2+j*2],prev[i*(n-4)*2+j*2+1]);
        auto q = std::max(prev[i*(n-4)*2+j*2+1],prev[i*(n-4)*2+j*2]);
        if (q==n-2){
          kstack.push(p);
        } 
      }
      while (!kstack.empty()){
        k = kstack.top();
        int counter = 0; // goes to n-3
        if (k==0){
          curr[rowToFill*(n-3)*2+counter*2] = 0;
          curr[rowToFill*(n-3)*2+counter*2+1] = n-2;
          counter++;
        }
        if (k==n-3){
          curr[rowToFill*(n-3)*2+counter*2] = n-3;
          curr[rowToFill*(n-3)*2+counter*2+1] = n-1;
          counter++;
        }
        for (int j = 0; j<n-4; j++){
          auto p = std::min(prev[i*(n-4)*2+j*2],prev[i*(n-4)*2+j*2+1]);
          auto q = std::max(prev[i*(n-4)*2+j*2+1],prev[i*(n-4)*2+j*2]);
          // 1. (p,q) both unequal to n-2, copy it to curr
          if((prev[i*(n-4)*2+j*2]!=n-2) &&(prev[i*(n-4)*2+j*2+1]!=n-2)){
             curr[rowToFill*(n-3)*2+counter*2] = p;
             curr[rowToFill*(n-3)*2+counter*2+1] = q;
             counter++;
          }
          // 2. add (p, n-1) if (p, n-2) exist, for 1<=p<=k
          if((q==n-2)&&(p>=1) && (p<=k)){
             curr[rowToFill*(n-3)*2+counter*2] = p;
             curr[rowToFill*(n-3)*2+counter*2+1] = n-1;
             counter++;
          }
          // 3. add (p, n-2) if (p, n-2) exists, for k<=p<n-3
          if ((q==n-2)&&(p>=k) && (p<n-3)) {
             curr[rowToFill*(n-3)*2+counter*2] = p;
             curr[rowToFill*(n-3)*2+counter*2+1] = n-2;
             counter++;
          }
        }

        kstack.pop();
        rowToFill++;
      }
    } 

  // free memory
  free(all_ptrs[n-6]);
  prevCat = currCat;
  std::cout <<"rowToFill: " <<rowToFill <<std::endl;
  for (int i = 0; i<currCat ; i++){
    for (int j = 0; j<n-3; j++){
      std::cout <<"(" << *(curr+i*(n-3)*2+j*2+0) <<"," <<*(curr+i*(n-3)*2+j*2+1) <<") ,";
    }
    std::cout << "\n";
  }
}

int main(){
  int n=0;
  std::cout << "Enter n: ";
  cin >> n;
  std::cout<<"running now\n";

  // base n=5
  // int *curr;
  int tri[5][2][2] = {{{0,2},{0,3}},
                     {{1,3},{1,4}},
                     {{2,4},{2,0}},
                     {{3,0},{3,1}},
                     {{4,1},{4,2}}};


  int *curr = (int*)malloc(5*2*2*sizeof(int));
  for (int i = 0;i<5;i++){
    for (int j = 0; j<2; j++){
      for (int k = 0; k<2; k++){
        curr[i*2*2+j*2+k] = tri[i][j][k];
      }
    }
  }


  all_ptrs.push_back(curr);
  prevCat = 5;

  // greater than 5
  for (int i=6; i<=n; i++){
    std::cout << "n = "<<i << std::endl;
    triangulation(i);
  }
  std::cout << "ending now\n";
  return 0;
}

