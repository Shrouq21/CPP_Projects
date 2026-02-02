#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define el '\n'
#define ll long long
#define mn INT_MIN
#define mx INT_MAX
struct ArrayList {
	ArrayList* next;
	ArrayList* prev;
	int idx{};
	int data{};
	ArrayList(int data,int idx):data(data),idx(idx){}
};


class ArrayLinkedlist {
private:
	ArrayList* head{};
	ArrayList* tail{};
	int length{};
	int ArrayLength{};
	void link( ArrayList* arr,  ArrayList* arr1) {
		if (arr)arr->next = arr1;
		if (arr1)arr1->prev = arr;
	}
	ArrayList*embed_after(ArrayList* prev_node,int data,int index) {
		ArrayList* after_node = prev_node->next;
		ArrayList* middle = new ArrayList(data, index);
		link(prev_node, middle);
		if (after_node) {
			link(middle, after_node);
		}
		else {
			tail = middle;
			tail->next = nullptr;
		}
		length++;
		return middle;
	}
	ArrayList* get_index(int index,bool  Create_If_Missing) {

		ArrayList* first = head;
		while (first->next and first->next->idx < index)
			first = first->next;
		bool found = (first->next and first->next->idx == index);
		if (found)return first->next;
        if(!Create_If_Missing)return nullptr;
	return	embed_after(first, 0, index);
	}

public:
	ArrayLinkedlist(int Array_len) :ArrayLength(Array_len) {
		head = tail = new ArrayList(0, -1);
		head->next = tail->next = nullptr;
		++length;
	}
	void Print() {
		ArrayList* curr = head->next;
		for (int i = 0; i < ArrayLength; i++) {
			if (curr and curr->idx == i) {
				cout << curr->data << " ";
				curr = curr->next;
			}
			else cout << 0 << " ";
			
		}
		cout << endl;
	}
	void Print_nonzero() {
		for (auto* Node = head->next; Node; Node = Node->next) {
			cout << Node->data << " ";
		}
		cout << endl;
	}
	void set_value(int data, int idx) {
		get_index(idx,true)->data = data;
	}
	int  get_value(int idx) {
		ArrayList* Node = get_index(idx,false);
		if (!Node)return 0;
		return Node->data;
	}

	void Add(ArrayLinkedlist& list) {
		assert(ArrayLength == list.ArrayLength);
		ArrayList* arr = list.head->next;
		for (auto* Node = arr; arr; arr = arr->next) {
			ArrayList* R = get_index(Node->idx,true);
			R->data += Node->data;
		}
	}
};

void test_index() {
	ArrayLinkedlist array(10);	
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	array.Print();
	
	array.Print_nonzero();
	
	cout << array.get_value(7) << "\n";	

	ArrayLinkedlist array2(10);
	array2.set_value(1, 4);
	array2.set_value(3, 7);
	array2.set_value(4, 6);

	array.Add(array2);
	array.Print();
	
}

int main()
{
	test_index();
	cout << "NO RTE\n";
	
}
