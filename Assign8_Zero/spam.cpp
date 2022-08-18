
int calcTime (Node* e,int k){// updates the zmiznzstep of every Node.
// 	check++;
// cout<<check<<endl;


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

// cout<< e->min_time;
return e->min_time;
// return 1;
}
