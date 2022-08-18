#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Kid;
class Course;

class Course{
public:
	string name;
	int slot;
	int max_kids;
	int num_kids=0;
 	vector<Kid*> Kids;

Course(){  //for arrays.
	return ;
}

Course(string namex){  //givnig search val as Course(course) in find. 
	name =namex;
}

Course(const Course& b){ //for find() to work
	name=b.name;
}

bool operator==(const Course& b){  //for find.
	if(name==b.name) return true;
	else return false;
}

bool operator<(const Course& b){  //for sort.
	if(name<b.name) return true;
	else false;
}

};


class Kid{
public:	
	string name;
	vector<int> slots;
	int max_course;
	int num_courses=0;
	vector<Course*> Courses;
Kid(){         //for arrays
	return;
}
Kid(string namex){  //for val in find()
	name=namex; 
}

Kid(const Kid& b){  //for find
	name=b.name;
}

bool operator==(const Kid& b){   //for  find
	if(name==b.name) return true;
	else return false;
}
bool operator<(const Kid& b){  // for sort
	if(name<b.name)return true;
	else return false;
}

};


void Print(Kid &a, Kid &b){
	sort(a.Courses.begin(),a.Courses.end());
	sort(b.Courses.begin(),b.Courses.end());
	vector<Course*> v(a.Courses.size()+b.Courses.size()); 
	vector<Course*>::iterator it, st; 

	it = set_intersection(a.Courses.begin(),a.Courses.end(), 
	                      b.Courses.begin(),b.Courses.end(), 
	                      v.begin()); 
	vector<string> answer;
	for (st = v.begin(); st != it; ++st) 
	    answer.push_back((*st)->name);
	sort(answer.begin(),answer.end());
	for(int i=0; i<answer.size(); i++)
		cout<<answer[i]<<" "; 
	cout << endl; 

}

void Print(Course &a, Course &b){
	sort(a.Kids.begin(),a.Kids.end());
	sort(b.Kids.begin(),b.Kids.end());
	vector<Kid*> v(a.Kids.size()+b.Kids.size()); 
	vector<Kid*>::iterator it, st; 

	it = set_intersection(a.Kids.begin(),a.Kids.end(), 
	                      b.Kids.begin(),b.Kids.end(), 
	                      v.begin()); 

	vector<string> answer;
	for (st = v.begin(); st != it; ++st) 
	    answer.push_back((*st)->name);
	sort(answer.begin(),answer.end());
	for(int i=0; i<answer.size(); i++)
		cout<<answer[i]<<" "; 
	cout << endl; 


}

void Print(Course &C){
	string *ans=new string[C.num_kids];
	for(int i=0; i<C.num_kids; i++)
		ans[i]=C.Kids[i]->name;
	sort(ans,ans+C.num_kids);
	for(int i=0; i<C.num_kids; i++)
		cout<<ans[i]<<" "; 
	cout << endl; 

// 	vector<string> answer;
// 	for (auto itr=C.Kids.begin(); itr!=C.Kids.end(); itr++) 
// 	    answer.push_back((*itr)->name);
// 	sort(answer.begin(),answer.end());
// 	   for(int i=0; i<answer.size(); i++)
//      	cout<<answer[i]<<" "; 
//      cout << endl; 
}

void Print(Kid &K){

	string* ans=new string[K.num_courses];
	for(int i=0; i<K.num_courses; i++)
		ans[i]=K.Courses[i]->name;
	sort(ans,ans+K.num_courses);
	for(int i=0; i<K.num_courses; i++)
		cout<<ans[i]<<" "; 
	cout << endl; 




	// vector<string> answer;
 //    for (auto itr=K.Courses.begin(); itr!=K.Courses.end(); itr++) 
 //        answer.push_back((*itr)->name);
 //    sort(answer.begin(),answer.end());
 //    for(int i=0; i<answer.size(); i++)
 //    	cout<<answer[i]<<" "; 
 //    cout << endl; 
 
}

void Reg(Kid &K, Course &C){
// cout<<K.name<<endl;
if(K.num_courses==K.max_course){
	cout<<"fail"<<endl;return;
}
else if(find(K.slots.begin(),K.slots.end(),C.slot)!=K.slots.end()){
	cout<<"fail"<<endl;return;
}
else if(C.max_kids!=-1 && C.num_kids==C.max_kids){
	cout<<"fail"<<endl;return;
}
else if(find(K.Courses.begin(),K.Courses.end(),&C)!=K.Courses.end()){
	cout<<"fail"<<endl;return;
}
K.slots.push_back(C.slot);
K.num_courses++;
K.Courses.push_back(&C);
C.num_kids++;
C.Kids.push_back(&K);
cout<<"success"<<endl;
return;
}

void Drop(Kid &K, Course &C){
if(find(K.Courses.begin(),K.Courses.end(),&C)==K.Courses.end()){
	cout<<"fail"<<endl;return;
}
K.slots.erase(find(K.slots.begin(),K.slots.end(),C.slot));
K.num_courses--;
K.Courses.erase(find(K.Courses.begin(),K.Courses.end(),&C));	
C.num_kids--;
C.Kids.erase(find(C.Kids.begin(),C.Kids.end(),&K));
cout<<"success"<<endl;
}

int wc(string a){
 	int count=0;
 	stringstream S(a);
 	string spam;
	while(S>>spam)
		count++;
	return count;
 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
ios_base::sync_with_stdio(false);
cin.tie(NULL);

int num_courses,num_kids,max_course;
long long int t;
cin >> num_courses >> num_kids >> max_course >> t;

Course *Courses = new Course[num_courses];
for(int i=0; i<num_courses; i++){
	cin >> Courses[i].name;
	cin >> Courses[i].slot;
	cin >> Courses[i].max_kids;
}

Kid *Kids = new Kid[num_kids];
for(int i=0; i<num_kids; i++){
	cin >> Kids[i].name;
	Kids[i].max_course = max_course;
}

string op;
getline(cin, op);
	
for(long long int t_count =0; t_count < t; t_count++ ){

	getline(cin, op);

	if(op[0]=='R'){
		stringstream S(op);
		string roll,course;
		S >> roll >> roll >> course;
		Reg(  *find(Kids,Kids+num_kids,Kid(roll))  ,  *find(Courses,Courses+num_courses,Course(course))  );
	}
	else if(op[0]=='D'){
		stringstream S(op);
		string roll,course;
		S >> roll >> roll >> course;
		Drop(  *find(Kids,Kids+num_kids,Kid(roll))  ,  *find(Courses,Courses+num_courses,Course(course))  );
	}
	else {
		if(wc(op)==2){
			stringstream S(op);
			string roll;
			S >> roll >> roll;
			if(roll.size()==9)
				Print(  *find(Kids, Kids+num_kids, Kid(roll))  );
			else Print(  *find(Courses, Courses+num_courses, Course(roll))  );
		}
		else{
			stringstream S(op);
			string roll1,roll2;
			S >> roll1 >> roll1 >> roll2;
			if(roll1.size()==9)
				Print(  *find(Kids, Kids+num_kids, Kid(roll1))  ,  *find(Kids, Kids+num_kids, Kid(roll2))  );
			else Print(  *find(Courses, Courses+num_courses, Course(roll1))  ,  *find(Courses, Courses+num_courses, Course(roll2))  );

		}
	}

}

}