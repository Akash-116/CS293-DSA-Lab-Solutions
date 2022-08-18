#include<iostream>
using namespace std;

int f(int n, int k){
	int i1;

	if(n==1) return 1;
	else if(n<k) return (f(n-1,k)+k-1)%n+1;
	else i1 = f(n-int(n/k),k);

	int i1r;
	int h; //say n = k*() + h
	h= n % k;
	
	int n_old;
	if(n/k == 0) n_old = n-1;
	else n_old = n-(n/k);

	i1r = ((i1+n_old-h-1)%n_old) + 1;
	int ans;
	ans = i1r + ((i1r-1)/(k-1));

	 return ans; 
}

int main()  {
	int n,k;
	cin >> n >> k;
	cout << f(n,k);
}