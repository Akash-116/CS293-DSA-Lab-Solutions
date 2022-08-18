#include <iostream>
using namespace std;

#include <stack>
#include <set>
int check=0;
class Node{
public:	
	Node* l = NULL;
	Node* r = NULL;
	char label='\0';
	int min_step=0;
	int min_time=0;
	int step_count=0;
	
	Node(){
	}

	Node(char label){
		this->label=label;
	}

};

Node* merge(Node* a, Node* b,char label){
	//merge both nodes..and give a new node....
	Node* ans=new Node();
	ans->l = a;
	ans->r = b;
	ans->label=label;
	return ans;
}
//this function dosent set the label of node.

Node* ExpTree (string inp){
//create a expression tree in heap memory and return a pointer.....no leakage...only usage

	stack<Node*> box;
	Node* sparel;
	Node* sparer; //???????
	char c;
	for(int i=0; i<inp.size(); i++){
		c=inp[i];
		if(c=='e'){
			Node* h = new Node('e');
			box.push(h);
		}
		else if(c=='+'){
			sparer=box.top();
			box.pop();
			sparel=box.top();
			box.pop();
			box.push(merge(sparel,sparer,'+'));

		}
		else if(c=='*'){
			sparer=box.top();
			box.pop();
			sparel=box.top();
			box.pop();
			box.push(merge(sparel,sparer,'*'));			
		}
	}

	return box.top();
}

int max(int a, int b){
	if(a>b)return a;
	else return b;
}
int min(int a, int b){
	if(a<b)return a;
	else return b;
}

int calcStep (Node* e){// updates the zmiznzstep of every Node.

if(e->label=='e') return 0;

if(e->label=='+'){

	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_step=1;
		}
		if(e->r->label=='+'){
			e->min_step=calcStep(e->r);
		}
		if(e->r->label=='*'){
			e->min_step=1+calcStep(e->r);
		}
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_step=calcStep(e->l);
		}
		if(e->r->label=='+'){
			e->min_step=calcStep(e->r)+calcStep(e->l)-1;
		}
		if(e->r->label=='*'){
			e->min_step=calcStep(e->r)+calcStep(e->l);
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_step=1+calcStep(e->l);
		}
		if(e->r->label=='+'){
			e->min_step=calcStep(e->r)+calcStep(e->l);
		}
		if(e->r->label=='*'){
			e->min_step=1+calcStep(e->r)+calcStep(e->l);
		}
	}
}
if(e->label=='*'){

	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_step=1;
		}
		if(e->r->label=='+'){
			e->min_step=1+calcStep(e->r);
		}
		if(e->r->label=='*'){
			e->min_step=calcStep(e->r);
		}
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_step=1+calcStep(e->l);
		}
		if(e->r->label=='+'){
			e->min_step=1+calcStep(e->r)+calcStep(e->l)-1;
		}
		if(e->r->label=='*'){
			e->min_step=calcStep(e->r)+calcStep(e->l);
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_step=calcStep(e->l);
		}
		if(e->r->label=='+'){
			e->min_step=calcStep(e->r)+calcStep(e->l);
		}
		if(e->r->label=='*'){
			e->min_step=calcStep(e->r)+calcStep(e->l)-1;
		}
	}
}
// count.insert(e->min_step);
return e->min_step;

}
//also need a set containing all the different values of min_step....


int calcTime (Node* e){// updates the zmiznztime of every Node.

if(e->label=='e') return 0;

if(e->label=='+'){
	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_time=1;
		}
		if(e->r->label=='+'){
			e->min_time=calcTime(e->r);
		}
		if(e->r->label=='*'){
			e->min_time=1+calcTime(e->r);
		}
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_time=calcTime(e->l);
		}
		if(e->r->label=='+'){
			e->min_time=max(calcTime(e->r),calcTime(e->l));
		}
		if(e->r->label=='*'){
			e->min_time=max(calcTime(e->r)+1,calcTime(e->l));
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_time=1+calcTime(e->l);
		}
		if(e->r->label=='+'){
			e->min_time=max(calcTime(e->r),1+calcTime(e->l));
		}
		if(e->r->label=='*'){
			e->min_time=1+max(calcTime(e->r),calcTime(e->l));
		}
	}
}
if(e->label=='*'){

	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_time=1;
		}
		if(e->r->label=='+'){
			e->min_time=1+calcTime(e->r);
		}
		if(e->r->label=='*'){
			e->min_time=calcTime(e->r);
		}
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_time=1+calcTime(e->l);
		}
		if(e->r->label=='+'){
			e->min_time=1+max(calcTime(e->r),calcTime(e->l));
		}
		if(e->r->label=='*'){
			e->min_time=max(calcTime(e->r),1+calcTime(e->l));
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_time=calcTime(e->l);
		}
		if(e->r->label=='+'){
			e->min_time=max(calcTime(e->r)+1,calcTime(e->l));
		}
		if(e->r->label=='*'){
			e->min_time=max(calcTime(e->r),calcTime(e->l));
		}
	}
}
return e->min_time;

}

int calcStep (Node* e,int k){// updates the zmiznzstep of every Node.
// 	check++;
// cout<<check<<endl;
if(e->label=='e') return 0;

int stepl=calcStep(e->l,k);
int stepr=calcStep(e->r,k);

if(e->label=='+'){
	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_step=1;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			if(e->r->step_count!=k-1){
				e->min_step=stepr;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_step=stepr+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='*'){
			e->min_step=1+stepr;
			e->step_count=1;
		}
	}
	if(e->l->label=='+'){ 
		if(e->r->label=='e'){
			if(e->l->step_count!=k-1){
				e->min_step=stepl;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_step=stepl+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='+'){
			if(e->r->step_count!=k-1 || e->l->step_count!=k-1){///tough!!!!
				if(e->r->step_count+e->l->step_count<k-1){
					e->min_step=stepr+stepl-1;
					e->step_count=1+e->l->step_count+e->r->step_count;
				}
				else{
					e->min_step=stepr+stepl;
					e->step_count=1+min(e->l->step_count,e->r->step_count);
				}
			}
			else{
				e->min_step=stepr+stepl+1;
				e->step_count=1;

			}
		}
		if(e->r->label=='*'){
			if(e->l->step_count!=k-1){
				e->min_step=stepr+stepl;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_step=stepr+stepl+1;
				e->step_count=1;
			}
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_step=1+stepl;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			if(e->r->step_count!=k-1){
				e->min_step=stepr+stepl;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_step=stepr+stepl+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='*'){
			e->min_step=1+stepr+stepl;
			e->step_count=1;
		}
	}
}
if(e->label=='*'){
	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_step=1;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			e->min_step=1+stepr;
			e->step_count=1;
		}
		if(e->r->label=='*'){
			if(e->r->step_count!=k-1){
				e->min_step=stepr;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_step=stepr+1;
				e->step_count=1;
			}
		} //done
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_step=1+stepl;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			e->min_step=1+stepr+stepl-1;
			e->step_count=1;
		}
		if(e->r->label=='*'){
			if(e->r->step_count!=k-1){
				e->min_step=stepr+stepl;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_step=stepr+stepl+1;
				e->step_count=1;
			}
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			if(e->l->step_count!=k-1){
				e->min_step=stepl;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_step=stepl+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='+'){
			if(e->l->step_count!=k-1){
				e->min_step=stepr+stepl;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_step=stepr+stepl+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='*'){
			if(e->r->step_count!=k-1 || e->l->step_count!=k-1){///tough!!!!
				if(e->r->step_count + e->l->step_count < k-1){
					e->min_step=stepr+stepl-1;
					e->step_count=1+e->l->step_count+e->r->step_count;
				}
				else{
					e->min_step=stepr+stepl;
					e->step_count=1+min(e->l->step_count,e->r->step_count);
				}
			}
			else{
				// cout<<"bloody";
				e->min_step=stepr+stepl+1;
				e->step_count=1;
			}
		}
	}
}
// cout<< e->min_step;
return e->min_step;
// return 1;

}

int calcTime (Node* e,int k){// updates the zmiznzstep of every Node.
// 	check++;
// cout<<check<<endl;
if(e->label=='e') return 0;

int timel=calcTime(e->l,k);
int timer=calcTime(e->r,k);

if(e->label=='+'){
	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_time=1;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			if(e->r->step_count!=k-1){
				e->min_time=timer;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_time=timer+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='*'){
			e->min_time=1+timer;
			e->step_count=1;
		}
	}
	if(e->l->label=='+'){ 
		if(e->r->label=='e'){
			if(e->l->step_count!=k-1){
				e->min_time=timel;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_time=timel+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='+'){
			if(timer==timel){
				if(min(e->l->step_count,e->r->step_count)==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=timer;
					e->step_count=1+min(e->l->step_count,e->r->step_count);
				}
			}
			else if(max(timer,timel)==timer){
				if(e->r->step_count==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=timer;
					e->step_count=1+e->r->step_count;
				}
			}
			else{
				if(e->l->step_count==k-1){
					e->min_time=1+timel;
					e->step_count=1;
				}
				else{
					e->min_time=timel;
					e->step_count=1+e->l->step_count;
				}
			}
		}
		if(e->r->label=='*'){
			if(e->l->min_time < 1+e->r->min_time){
				e->min_time = 1+ e->r->min_time;
				e->step_count=1;
			}
			else{
				if(e->l->step_count==k-1){
					e->min_time=1+timel;
					e->step_count=1;
				}
				else{
					e->min_time=1+timel;
					e->step_count=1+e->l->step_count;
				}
			}
		}
	}
	if(e->l->label=='*'){
		if(e->r->label=='e'){
			e->min_time=1+timel;
			e->step_count=1;
		}
		if(e->r->label=='+'){
			if(e->r->min_time < 1+e->l->min_time){
				e->min_time = 1+ e->l->min_time;
				e->step_count=1;
			}
			else{
				if(e->r->step_count==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=1+timer;
					e->step_count=1+e->r->step_count;
				}
			}
		}
		if(e->r->label=='*'){
			e->min_time=1+max(timel,timer);
			e->step_count=1;
		}
	}
}

if(e->label=='*'){
	if(e->l->label=='e'){
		if(e->r->label=='e'){
			e->min_time=1;
			e->step_count=1;
		}
		if(e->r->label=='*'){
			if(e->r->step_count!=k-1){
				e->min_time=timer;
				e->step_count=1+e->r->step_count;
			}
			else{
				e->min_time=timer+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='+'){
			e->min_time=1+timer;
			e->step_count=1;
		}
	}
	if(e->l->label=='*'){ 
		if(e->r->label=='e'){
			if(e->l->step_count!=k-1){
				e->min_time=timel;
				e->step_count=1+e->l->step_count;
			}
			else{
				e->min_time=timel+1;
				e->step_count=1;
			}
		}
		if(e->r->label=='*'){
			if(timer==timel){
				if(min(e->l->step_count,e->r->step_count)==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=timer;
					e->step_count=1+min(e->l->step_count,e->r->step_count);
				}
			}
			else if(max(timer,timel)==timer){
				if(e->r->step_count==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=timer;
					e->step_count=1+e->r->step_count;
				}
			}
			else{
				if(e->l->step_count==k-1){
					e->min_time=1+timel;
					e->step_count=1;
				}
				else{
					e->min_time=timel;
					e->step_count=1+e->l->step_count;
				}
			}
		}
		if(e->r->label=='+'){
			if(e->l->min_time < 1+e->r->min_time){
				e->min_time = 1+ e->r->min_time;
				e->step_count=1;
			}
			else{
				if(e->l->step_count==k-1){
					e->min_time=1+timel;
					e->step_count=1;
				}
				else{
					e->min_time=1+timel;
					e->step_count=1+e->l->step_count;
				}
			}
		}
	}
	if(e->l->label=='+'){
		if(e->r->label=='e'){
			e->min_time=1+timel;
			e->step_count=1;
		}
		if(e->r->label=='*'){
			if(e->r->min_time < 1+e->l->min_time){
				e->min_time = 1+ e->l->min_time;
				e->step_count=1;
			}
			else{
				if(e->r->step_count==k-1){
					e->min_time=1+timer;
					e->step_count=1;
				}
				else{
					e->min_time=1+timer;
					e->step_count=1+e->r->step_count;
				}
			}
		}
		if(e->r->label=='+'){
			e->min_time=1+max(timel,timer);
			e->step_count=1;
		}
	}
}

// cout<< e->min_time;
return e->min_time;
// return 1;
}

string postTransverse(Node* t){
	if(t==NULL)return "";

	else {string ans=(postTransverse(t->l).append(postTransverse(t->r)));
			ans.push_back(t->label);
		return ans;}
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Node* expTree;
	// set<int> count;
 
	string postorder;
	cin >> postorder;

	expTree = ExpTree(postorder);
	// cout<<postTransverse(expTree);
	cout<<calcStep(expTree)<<" ";
	cout<<calcTime(expTree)<<endl;
	// cout<<calcStep(expTree)<<" ";


	int t;
	cin>>t;
	int k;  //bound on the number of operands in one step.

	for(int i=0; i<t; i++){
		cin>>k;

		cout<<calcStep(expTree,k)<<" ";
		cout<<calcTime(expTree,k)<<endl;
	}

}