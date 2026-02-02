#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node*prev{};
    Node*next{};
  int val{};
Node(int val):val(val){}
};

class ArrayLinkedList{
private:
Node*head{};
Node*tail{};
int length{};
public:
ArrayLinkedList(int length):length(length){
int len=length;
while(len){
Node*temp=new Node(0);
if(len==length){
    head=tail=temp;
}
else {
    tail->next=temp;
    temp->next=nullptr;
    temp->prev=tail;
    tail=temp;
}
len--;
}
}

void set_value(int value,int index){
int i=0;
for(Node*node=head;node;node=node->next,++i){
if(i==index){
node->val=value;
break;
}
}
}

void Get_value(int index){
int i=0;
for(Node*node=head;node;node=node->next,i++)
{
    if(i==index){
        cout<<node->val<<endl;
        break;
    }
}
}

void Print(){
for(Node*node=head;node;node=node->next)cout<<node->val<<" ";
cout<<endl;
}

void Add_Array(const  ArrayLinkedList*list){
Node*temp=list->head;
int list_i=0;
for(Node*list_node=temp;list_node;list_node=list_node->next,++list_i){
    if(list_node->val!=0){
            int curr_i=0;
            for(Node*curr_node=head;curr_node;curr_node=curr_node->next,++curr_i){
                 if(curr_i==list_i){
                 curr_node->val+=list_node->val;
                       break;
                }
            }
}
}
}
void Print_array_nonzero(){
    bool chk=0;
    for(Node*node=head;node;node=node->next){
        if(node->val){
        cout<<node->val<<" ";
        chk=1;
        }
    }
    if(chk)cout<<endl;
}

};


class SparseMatrix{
private:
Node*head{};
Node*tail{};
int rows{},columns{};
vector<ArrayLinkedList*>_2D_Array;
public:
SparseMatrix(int rows,int columns):rows(rows),columns(columns){

_2D_Array.resize(rows);

for(int i=0;i<rows;i++){
_2D_Array[i]=new ArrayLinkedList(columns);
}
    }


void set_value(int value,int row,int column){
for(int i=0;i<rows;i++){
    if(i==row){
         _2D_Array[i]->set_value(value,column);
        }
    }
}


void Print(){
for(int i=0;i<rows;i++){
   _2D_Array[i]->Print();
   
}
}

void Add( const SparseMatrix&matrix){
vector<ArrayLinkedList*>_2D_Temp=matrix._2D_Array;
for(int i=0;i<rows;i++){
    _2D_Array[i]->Add_Array(_2D_Temp[i]);
}
}
void Print_array_nonzero(){
     cout<<"Print Matrix: "<<rows<<" x " <<columns<<endl;
    for(int i=0;i<rows;i++){
          {
            _2D_Array[i]->Print_array_nonzero();
           
          }
}
}

};
int main() {
SparseMatrix mat(10,10);
 mat.Print();
    cout<<"**********************\n";
mat.set_value(5,3,5);
mat.set_value(7,3,7);
mat.set_value(2,3,2);
mat.set_value(0,3,2);
mat.set_value(6,5,6);
mat.set_value(4,5,4);
mat.set_value(3,7,3);
mat.set_value(1,7,1);
mat.Print();
    cout<<"**********************\n";
mat.Print_array_nonzero();

    cout<<"**********************\n";
SparseMatrix mat2(10,10);
mat2.Print();
    cout<<"**********************\n";
mat2.set_value(5,1,9);
mat2.set_value(6,3,8);
mat2.set_value(9,9,9);
mat2.Print();
   cout<<"**********************\n";
mat.Add(mat2);
mat.Print_array_nonzero();
}
