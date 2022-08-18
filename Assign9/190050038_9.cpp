#include <iostream>
using namespace std;
#include <set>
#include <string>
#include <vector>

bool Unique=true;
class triplet{
public:
	int first;
	int second;
	int third;
	friend ostream operator >> (ostream &output, triplet &);

	triplet(int f, int s, int t){
		first=f;
		second=s;
		third=t;
	}
};


// ostream& operator <<( ostream &output, const triplet &s1){
// 	output << "("<<s1.first<<","<<s1.second<<","<<s1.third<<")";
// 	return output;
// }

struct Compare1{ //based on first and second and third
	bool operator()(triplet const& t1, triplet const& t2){
		if (t1.first > t2.first) return false;
		if (t1.first < t2.first) return true;
		else {
			if(t1.second > t2.second)return false;
			if(t1.second < t2.second)return true;
			else{ 
				if(t1.third < t2.third)return true;
				else return false;
			}
		}
	}
};
struct Compare2{ //based on first and NOT second and third
	bool operator()(triplet const& t1, triplet const& t2){
		if (t1.first > t2.first) return false;
		if (t1.first < t2.first) return true;
		else{
			if(t1.second < t2.second)return false;
			if(t1.second > t2.second)return true;
			else{ 
				if(t1.third<t2.third)return true;
				else return false;
			}
		}
	}
};
struct CompareA{ //based on second and third
	bool operator()(triplet const& t1, triplet const& t2){
		// if (t1.first<t2.first) return true;
		// else

			if(t1.second > t2.second)return false;
			if(t1.second < t2.second)return true;
			else {
				if(t1.third<t2.third)return true;
				else return false;
			}
	}
};
struct CompareC{ //based on NOT second and third
	bool operator()(triplet const& t1, triplet const& t2){
		// if (t1.first<t2.first) return true;
		// else
			if(t1.second < t2.second) return false;
			if(t1.second > t2.second) return true;
			else {
				if(t1.third < t2.third)return true;
				else return false;
			}
	}
};


struct Compare{
	bool operator()(triplet const& t1, triplet const& t2){
		if(t1.first>=t2.second) return false;
		else return true;
	}
};


bool compareAC(set<triplet,CompareA> &A, set<triplet,CompareC> &C, vector<int>* ans1, vector<int>* ans2, int n){

	if(A.size()<=C.size()){
		for(set<triplet,CompareA>::iterator p=A.begin(); p!=A.end(); p++ ){
			ans1->push_back(p->third);
			
			triplet tA = *p;
			tA.third = 0;
			set<triplet,CompareC>::iterator pt = C.upper_bound(tA);

			if(pt==C.end()) return false;
			else{
				ans2->push_back(pt->third);
				C.erase(pt);
			}
		}
		A.clear();
		return true;

	}
	else{
		for(set<triplet,CompareC>::iterator p=C.begin(); p!=C.end(); p++ ){
			ans2->push_back(p->third);

			triplet tC = *p;
			tC.third = 0;
			set<triplet,CompareC>::iterator pt = A.upper_bound(tC);

			if(pt==A.end()) return false;
			else{
				ans1->push_back(pt->third);
				A.erase(pt);
			}
		}
		C.clear();
		return true;
	}
}



int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


	int n; cin>>n;
	vector<int>*ans1=new vector<int>;
	vector<int>*ans2=new vector<int>;
	int *a=new int[n];
	int *b=new int[n];
	int *c=new int[n];
	int *d=new int[n];
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++) cin >> b[i];
	for(int i=0; i<n; i++) cin >> c[i];
	for(int i=0; i<n; i++) cin >> d[i];

	set<triplet,Compare1>* S1 = new set<triplet,Compare1>;
	set<triplet,Compare2>* S2 = new set<triplet,Compare2>;

	for(int i=0; i<n; i++){

		S1->insert(triplet(a[i],b[i],i+1));
		S2->insert(triplet(c[i],d[i],i+1));
	}


	// delete[] a;
	// delete[] b;
	// delete[] c;
	// delete[] d;


	// cout<<"S1 is :"<<endl;
	// for(set<triplet,Compare1>::iterator p=S1->begin(); p!=S1->end(); p++){
	// 	cout<<*p<<endl;
	// }

	// cout<<endl<<endl;

	// cout<<"S2 is :"<<endl;
	// for(set<triplet,Compare2>::iterator p=S2->begin(); p!=S2->end(); p++){
	// 	cout<<*p<<endl;
	// }

	set<triplet,CompareA> A;
	set<triplet,CompareC> C;

	set<triplet,Compare1>::iterator pA = S1->begin();
	set<triplet,Compare2>::iterator pC = S2->begin();

	int pAf = pA->first;
	int pCf = pC->first;
	bool Possible=true;

	while(pA!=S1->end() || pC!=S2->end()){
		if(A.size()==0){
			while(pA->first == pAf &&  pA!=S1->end()){
				A.insert(*pA);
				pA++;
			}
			if(pA!=S1->end())pAf=pA->first;
		}

		if(C.size()==0){
			while(pC->first == pCf && pC!=S2->end()){
				C.insert(*pC);
				pC++;
			}
			if(pC!=S2->end())pCf=pC->first;
		}

		Possible = compareAC(A,C,ans1,ans2,n);

		if(!Possible){
			cout<<"impossible"<<endl;
			break;
		}

	}
//////////////////////////////////////////////////part-2///////////////////////////////////


/////////////////////////////////////////part-2///////////////////////////////////////////////////////////////////////////

	if(Possible){
	set<triplet,Compare>* T = new set<triplet,Compare>;
	delete S2;
	delete S1;
	vector<triplet> S3;
	vector<triplet> S4;

for(int i=0; i<n; i++){
	S3.push_back(triplet(a[(*ans1)[i]-1],b[(*ans1)[i]-1],0));
	S4.push_back(triplet(c[(*ans2)[i]-1],d[(*ans2)[i]-1],0));
}


	int pi=0;	
	int pif=S4[pi].first;
	int count;

	while(pi!=n){
	count=0;
		// if(T->size()==0){
			while(S4[pi].first == pif &&  pi!=n){
				T->insert(triplet(S3[pi].second,S4[pi].second,0));
				pi++;
				count++;
			}
			if(pi!=n)pif=S4[pi].first;
		// }


	if(T->size()<count) Unique=false;
	// cout<<"size   " <<T->size() <<"   "<< count<<endl;

	T->clear();

	}


		for(vector<int>::iterator p=ans1->begin(); p!=ans1->end(); p++){
			cout<<*p<<" ";
		}
		cout<<endl;
		for(vector<int>::iterator p=ans2->begin(); p!=ans2->end(); p++){
			cout<<*p<<" ";
		}
		cout<<endl;
		if(Unique)cout<<"unique"<<endl;
		else cout<<"not unique"<<endl;


	for(int i=0; i<n-1; i++){
			if(a[(*ans1)[i]-1]>a[(*ans1)[i+1]-1]) cout<<endl<<"error1";
			if(c[(*ans2)[i]-1]>c[(*ans2)[i+1]-1]) {
				cout<<endl<<"error2";
				// cout<<c[(*ans1)[i]-1]<<c[(*ans1)[i+1]-1];
			}
	}
	for(int i=0; i<n; i++)
			if(d[(*ans2)[i]-1]>b[(*ans1)[i]-1]) cout<<endl<<"error3";

		// }




	}


}