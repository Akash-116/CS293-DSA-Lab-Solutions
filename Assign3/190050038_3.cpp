#include<iostream>
#include<vector>

using namespace std;

int main (int argc, char* argv[]) {
	
	int n,t;
	cin >> n >> t;
	// n is the main culprit, gotta calculate stuff based on it!
	vector<vector<long long int>> data(n, vector<long long int>(n)); //data[size of seq][max of seq]

	for(int n0=0; n0<n; n0++) 	{  //setting the trivial elements
		for(int m0=0; m0<n; m0++) {
			if(n0==0) data[n0][m0]=1;
			else if(m0 >= n-n0) data[n0][m0]=0; 
		} 
	}

	for(int n0=1; n0<n; n0++) {			//setting the recursively calculated elements
		for (int m0=0; m0<n-n0; m0++){
			data[n0][m0] = data[n0-1][m0]*(m0+1) + data[n0-1][m0+1];
		}
	}
	// setting the data info is done!!!!



	for(int tst_cs=0; tst_cs<t; tst_cs++) {  //loop to run testcases
		
		char check;
		cin >> check;

		
		if(check == 'R'){		//if sequence is inputed and rank is to be outputed.
			vector<int> seq(n);				
			for(int i=0; i<n; i++) cin >> seq[i];
			int n0 = n-2;
			int m0_prev =  0  ;
			int m0_now = 0;
			long long int rank = 0;
			for (   ; n0 >=0; n0--) {
				int term = seq[n-n0-1];
				if( seq[n-n0-2] > m0_prev ) m0_prev = seq[n-n0-2];
				for(int q = term-1; q >= 0; q--){
					m0_now = m0_prev;
					if(q > m0_now) m0_now = q;
					rank = rank + data[n0][m0_now];
				}
			}
			cout << rank << endl;
		}


		if(check == 'U'){  //if rank is inputted and seq is to be outputted.
			long long int inp_rank;
			cin >> inp_rank;
			long long int rank_prev = 0, rank = 0;
			int m0_prev =  0  ;
			int m0_now = 0;		
			int n0 = n-2;
			cout << 0 << " ";
			for (    ; n0 >= 0; n0--){
				int q=0;
				for(    ; q <= m0_prev+1; q++){
					if(q > m0_prev) m0_now = q;
					rank = rank_prev + data[n0][m0_now];
					if(rank > inp_rank){break;}
					rank_prev = rank;
				}
				cout << q << " " ;
				m0_prev = m0_now;
			}
			cout << endl;
		}
	}


}