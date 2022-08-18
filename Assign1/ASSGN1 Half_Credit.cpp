#include<iostream>
using namespace std;
#include<list>

class Circular_List{
  list<int> ring;
  int p=0;
  int size;//pointer in the circular loop of vector 
  
  public:
  
  Circular_List(int n){
      for(int i=1; i<n+1; i++) ring.push_back(i);
      size = n;
  }
  
  void operator++(int){ //postfix operator
      p++;
      p=(p%size);
  }
  
  void Remove(){
      size--;
      list<int>::iterator itr=ring.begin();
      advance(itr,p);
      ring.erase(itr);
      p=p%size;
  }
  
  int value(){			//all okay
      return ring.front();
  }

};



int J(int n, int k){
    class Circular_List C(n);
    
    for(int i=0; i<n-1; i++){
        for(int j=1; j<k; j++) C++;
        C.Remove();
    }
     return C.value();
}




int main(int argc, char* argv[]){
    int n,k;
    cin>>n>>k;
    cout<<J(n,k);
    
}