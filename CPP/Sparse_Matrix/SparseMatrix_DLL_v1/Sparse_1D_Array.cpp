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
    assert(list->length==length);
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
    for(Node*node=head;node;node=node->next){
        if(node->val)cout<<node->val<<" ";
    }
    cout<<endl;
}

};

int main() {
 ArrayLinkedList array(10);
array.set_value(50,5);
array.set_value(20,2);
array.set_value(70,7);
array.set_value(40,4);
array.Print();
array.Print_array_nonzero();
ArrayLinkedList array2(10);
array2.set_value(1,4);
array2.set_value(3,7);
array2.set_value(4,6);
array.Add_Array(&array2);
array.Print();
}
