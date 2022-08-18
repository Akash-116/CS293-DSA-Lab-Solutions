//takes input and gives output.
//check takes "input","output" and echos correct or wrong.


#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


void distribute (vector<int> &bag, int k, int m){
	int q,r;

	q = bag[m]/k;
	r = bag[m] % k;
	bag[m] = q;
	for (int i = 1; i < k; i++)
		bag[(m+i) % k] += q;
	for (int i = 1; i <= r; i++)
		bag[(m+i) % k]++;
	return;

}


int main(int argc, char *argv[])
{
	ofstream fout("outfile") ;


	int n, k;
	cin >> n >> k;
	vector<int> bag(k);	
	for (int i = 0; i < k; i++) cin >> bag[i];
	// input taken successfully
	// let position 0 be maximised!


	bool flag = true; //chechking the "To-Be" Condition
	int q = n/k;
	for (int i = 0; i < k; i++)
		if ((bag[i] < q) || (bag[i] > q+1)) {flag = false; break;}
	if(flag) return 0;


	int z_pos;

	while (z_pos!=k){
		for(z_pos=1;z_pos<k;z_pos++){
			if (bag[z_pos]!=0){
				distribute(bag,k,z_pos);
				fout << z_pos << " ";
				break;
			}
		}
	}
	fout << 0;
			
}

