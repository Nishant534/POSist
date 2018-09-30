#include <iostream>
#include <time.h>
#include<vector>
#include<string.h>
using namespace std;
struct Owner{
	string name;
	string address;
	string mobile;
	//string mobile;
	float value;
	string password;
	int ownerNum;
	
};
struct node{
	time_t dt;
	Owner *owner;
	int NodeNumber;
	int nodeId;
	node *refNodeId;
	vector<int> childNodeId;
	vector<node*> refChildNodeId;
	
};
node *GetNode(int num,Owner *own){
	node *np=new node;
	np->dt=time(0);
	np->owner=own;
	np->NodeNumber=num;
	np->nodeId=(num);
	vector<node*> v;
	np->refChildNodeId=v;
	np->refNodeId=NULL;
	vector<int> s;
	np->childNodeId=s;
	return np;
}

void Func3(node *child,int id,vector<node*> &v){
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			v[i]->refChildNodeId.push_back(child);
			v[i]->childNodeId.push_back(child->nodeId);
			child->refNodeId=v[i];
			break;
		}	
	}
}
string encrypt(string s,int n){
	string sol=s;
	for(int i=0;i<sol.length();i++){
		sol[i]+=n;
	}
	return sol;
}
string decrypt(string data,int n){
	string sol=data;
	for(int i=0;i<sol.length();i++){
		sol[i]-=n;
	}
	return sol;
}
Owner *getOwner(int num,string name, string address, string mobile,  float value,string pass){//string mobile,
	
	Owner *own=new Owner;
	own->ownerNum=num;
	own->address=encrypt(address,num);
	own->address=encrypt(name,num);
	own->address=encrypt(mobile,num);
	own->address=encrypt(mobile,num);
	own->value=value;
	own->password=encrypt(pass,num);
	return own;	
}
bool Func4(vector<Owner*> &owners,Owner *currOwner,vector<node*> &v){
	cout<<"Pleae enter the Node Id : ";
			int id;
			cin>>id;
			bool f=false;
			for(int i=0;i<v.size();i++){
				if(v[i]->nodeId==id){
					if(currOwner==v[i]->owner){
						f=true;
					}
					break;
				}	
			}
		
			return f;
}
//deleting particular node using nodeId
void Func5(vector<Owner*> &owners, Owner *currOwner, vector<node*> &v){
	cout<<"Please enter the Node ID : "<<endl;
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(Func4(owners,currOwner,v)){
				
				f=true;
				node *parent=v[i]->refNodeId;
				vector<node*> child=parent->refChildNodeId;
				for(int k=0;k<child.size();k++){
					if(child[k]->nodeId==id){
						child.erase(child.begin()+i);
						
						break;
					}
				}
				
			}else{
				cout<<"You are not the owner of the current node!"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"The node was removed successfully!"<<endl;
	}else{
		cout<<"Not found!"<<endl;
	}
}
void Func6(vector<Owner*> &owners,Owner *currOwner, vector<node*> &v){
	cout<<"\n\nPlease enter the following : "<<endl;
	int id,userId;
	cout << "Node ID : ";
	cin>>id;
	cout << "\nUser ID : ";
	cin>>userId;
	bool f=false;
	for(int i=0;i<v.size();i++){
		if(v[i]->nodeId==id){
			if(Func4(owners,currOwner,v)){
				
				
				node *np=v[i];
				for(int k=0;k<owners.size();k++){
					if(owners[k]->ownerNum==userId){
						np->owner=owners[k];
						f=true;
						break;
					}	
				}
				
			}else{
				cout<<"You are not the owner of the current node!"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"Owner change was successful!"<<endl;
	}else{
		cout<<"Couldn't find the node!"<<endl;
	}
}
void Func7(vector<node*> v){
	
}
void dfs(node *root,int &n,int num){
	if(root==NULL){
		n=max(n,num);
	}
	int count=num+1;
	vector<node*> child=root->refChildNodeId;
	for(int i=0;i<child.size();i++){
		dfs(child[i],n,num+1);
	}
	n=max(n,count);
}
void mergeSet(vector<node*> &first, vector<node*> &second,Owner *currOwner){
	//merge sets of same owner
	int i=0,j=0;
	while(i<first.size() && j<second.size()){
		while(i<first.size() && first[i]->owner!=currOwner){
			i++;
		}
		while(j<second.size() && second[j]->owner!=currOwner){
			j++;
		}
		int n1=-1,n2=-1;
		dfs(second[j],n2,0);
		dfs(first[i],n1,0);
		if(n1>n2){
			second[j]->refNodeId=first[i];
			first[i]->refChildNodeId.push_back(second[j]);
			second.erase(second.begin()+j);
			i++;
		}else{
			first[i]->refNodeId=second[j];
			second[j]->refChildNodeId.push_back(first[i]);
			second.erase(second.begin()+j);
			j++;
		}
	}
	
}
int main(){
	St:
    int num=0,nOwners=0;
    vector<vector<node*> > set;
    vector<node*> v;
    vector<Owner*> owners;
    int q;

    Owner *currOwner;
    bool f=false;
    
    while(!f){
    	cout<<"Menu :\n 1 -> Enter the system \n 2 -> Register / Sign-up\n";
    	
    cin>>q;
    	if(q==1){
			cout<<"Password and Security key required!!\n";
	    	string pass;
	    	int key;
	    	cout << "Please enter the password:\t";
	    	cin>>pass;
	    	cout << endl;
	    	cout << "Please enter the key:\t";
			cin>>key;
			cout <<endl;
	    	for(int i=0;i<owners.size();i++){
	    		if(owners[i]->ownerNum==key){
	    			if(pass==decrypt(owners[i]->password,owners[i]->ownerNum)){
	    				f=true;
	    				currOwner=owners[i];
	    				break;
					}
				}
			}
			cout<<"\t\t\tLogin Failed!!\n\n"<<endl;
		}else{
			cout <<"\n\nPlease enter the following details : \n";
			cout<<"Name :"<<endl;
			string name,address,mobile,pass;//mobile,
			float value;
			cin>>name;
			
			cout<<"\nAddress :"<<endl;
			cin>>address;
			cout<<"\nMobile1, Mobile2 :";
			cin>>mobile>>mobile;
			cout<<"\nValue :";
			cin>>value;
			cout<<"\npassword :";
			cin>>pass;// mobile,
			currOwner=getOwner(nOwners++,name, address, mobile, value,pass);
			owners.push_back(currOwner);
			cout<<"\nPLEASE NOTE :\n YOUR SECURITY KEY IS : "<<currOwner->ownerNum<<endl;
			f=true;
			cout << endl;
		}
	}
    
    
    while(1){
    	cout<<"\t\tEnter the Query now : ";
		cin>>q;
		if(q==1){
			//create genesis node 
			vector<node*> v;
			v.push_back(GetNode(num++,currOwner));
			set.push_back(v);
		}else if(q==2){
			//push a set of child nodes
			int n=0;
			cout<<"\nEnter the number of nodes: ";
			cin>>n;
			vector<node*> v(1);
			for(int i=0;i<n;i++){
				v[0]=(GetNode(num++,currOwner));	
				set.push_back(v);
			}
			cout<<"\n Nodes pushed successfully!!"<<endl;
		}else if(q==3){
			//adding node to any set
			node *np=GetNode(num++,currOwner);
			v.push_back(np);
			cout<<"\nEnter the set number : ";
			int setNo;
			cin>>setNo;
			set[setNo].push_back(np);
			
		}else if(q==4){
			//verify owner
			bool f=false;
			for(int i=0;i<set.size();i++){
				f=Func4(owners,currOwner,set[i]);
				if(f){
					cout<<"\nOwner verification successful! User is the owner!"<<endl;
				}		
			}
			if(!f){			
				cout<<"\nOwner couldn't be verified! User is not the owner!"<<endl;
			}
		}else if(q==5){
			//edit the node/ delete node 
			Func5(owners,currOwner,v);
			
		}else if(q==6){
			// transfer owner
			Func6(owners,currOwner,v);
			
			
		}else if(q==7){
			//longest chain of genesis node
			int mx=-1;
			for(int i=0;i<set.size();i++){
				
				dfs(set[i][0],mx,0);	
			}
			cout<<"\nThe Maximum Chain is : "<<mx<<endl;
			
		}else if(q==8){
			//longest chain of sub node
			cout<<"Please enter the Node ID : "<<endl;
			int id;
			cin>>id;
			int ans=-1;
			bool f=false;
			for(int i=0;i<set.size();i++){
				for(int j=0;j<set[i].size();j++){
					if(set[i][j]->nodeId==id){
						f=true;
						dfs(set[i][j],ans,0);
						break;
					}
				}
				if(f){
					break;	
				}
			}
		}else if(q==9){
			//merge nodes
			cout<<"Please enter the following : \nFirst set number : ";
			int f,s;
			cin>>f;
			cout << "Second set number : ";
			cin>>s;
			cout << endl;
			mergeSet(set[f],set[s],currOwner);
			
		}else if(q==10){
			//log out
			currOwner=NULL;
			goto St;
		}else {
			break;
		}
	}
    return 0;
}
