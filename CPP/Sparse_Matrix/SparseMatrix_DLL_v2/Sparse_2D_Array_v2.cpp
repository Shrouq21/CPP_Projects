#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define el '\n'
#define ll long long
#define mn INT_MIN
#define mx INT_MAX
struct ColumnNode {
	int Data{};
	int Index{};
	ColumnNode* PrevNode{};
	ColumnNode* NextNode{};
	ColumnNode(int Data, int Index) :Data(Data), Index(Index) {}

};

class ColumnList {
private:
	ColumnNode* head{};
	ColumnNode* tail{};
	int ListLength{};
	void link(ColumnNode* F, ColumnNode* S) {
		if (F)F->NextNode = S;
		if (S)S->PrevNode = F;
	}
	ColumnNode* embed_after(ColumnNode* prev_node, int index, int data) {
		ColumnNode* middle = new ColumnNode(data, index);
		ColumnNode* next_node = prev_node->NextNode;
		link(prev_node, middle);
		if (next_node)link(middle, next_node);
		else {
			tail = middle;
			tail->NextNode = nullptr;
		}
		return middle;
	}
	ColumnNode* GetColumn(int index, bool Create_If_Missing) {
		ColumnNode* curr = head;
		ColumnNode* target = new ColumnNode(0, index);
		while (curr->NextNode and curr->NextNode->Index < index)curr = curr->NextNode;
		bool found = (curr->NextNode and index == curr->NextNode->Index);
		if (found) {
			return curr->NextNode;
		}
		if (!Create_If_Missing) {
			return nullptr;
		}
		return embed_after(curr, index, 0);
	}
public:
	ColumnList(int Length) :ListLength(Length) {
		head = tail = new ColumnNode(0, -1);
	}
	void Print() {
		ColumnNode* Row = head->NextNode;
		for (int i = 0; i < ListLength; i++) {
			if (Row and Row->Index == i) {
				cout << Row->Data << " ";
				Row = Row->NextNode;
			}
			else
				cout << 0 << " ";


		}
		cout << el;
	}
	void print_row_nonzero() {
		for (auto* curr = head->NextNode; curr; curr = curr->NextNode)cout << curr->Data << " ";
		cout << el;
	}
	void SetValue(int index, int data) {
		ColumnNode* node = GetColumn(index, true); node->Data = data;
	}
	int GetValue(int index) {
		ColumnNode* node = GetColumn(index, false);
		if (!node)return 0;
		else
			return node->Data;
	}
	void Add(ColumnList& List) {
		assert(List.ListLength == ListLength);
		ColumnNode* NodeList = List.head->NextNode;
		for (auto* curr = NodeList; curr; curr = curr->NextNode) {
			ColumnNode* Node = GetColumn(curr->Index, true);
			Node->Data += curr->Data;
		}
	}
};


struct RowNode {
	RowNode* Prev{}, * Next{};
	ColumnList ColList;
	int Index{};
	RowNode(int index, int col_sz) :Index(index), ColList(col_sz) {}

};
class SparseMatrix {
private:
	RowNode* head{};
	RowNode* tail{};
	int Rows{}, Cols{}, Length{};
	void link(RowNode* F, RowNode* S) {
		if (F)F->Next = S;
		if (S)S->Prev = F;
	}
	RowNode* embed_after(RowNode* prev, int index) {
		Length++;
		RowNode* Middle = new RowNode(index, Cols);
		RowNode* next = prev->Next;
		link(prev, Middle);

		if (next) {
			link(Middle, next);
		}
		else
		{
			tail = Middle;
			tail->Next = nullptr;
		}
		return Middle;

	}

	RowNode* get_row(int index, bool Create_If_Missing) {
		RowNode* curr = head;
		while (curr->Next and curr->Next->Index < index)curr = curr->Next;
		bool found = curr->Next and curr->Next->Index == index;
		if (found)return curr->Next;
		if (!Create_If_Missing)return nullptr;
		return embed_after(curr, index);
	}
public:
	SparseMatrix(int rows, int cols) :Rows(rows), Cols(cols) {
		head = tail = new RowNode(-1, cols);
		++Length;
	}
	void SetValue(int data, int row, int column) {
		assert(row >= 0 and row < Rows);
		assert(column >= 0 and column < Cols);
		RowNode* curr = get_row(row, true);
		curr->ColList.SetValue(column, data);

	}
	int GetValue(int row, int column) {
		assert(row >= 0 and row < Rows);
		assert(column >= 0 and column < Cols);
		RowNode* curr = get_row(row, false);
		if (!curr)return 0;
		else
		{
			return curr->ColList.GetValue(column);
		}
	}
	void print_matrix() {
		cout << "Matrix " << Rows << " X " << Cols << endl;
		for (int i = 0; i < Rows; i++) {
			RowNode* curr = get_row(i, false);
			if (curr) {
				curr->ColList.Print();
			}
			else
			{
				for (int i = 0; i < Cols; i++)cout << 0 << " ";
				cout << endl;
			}

		}

	}
	void print_matrix_nonzero() {
		cout << "Matrix " << Rows << " X " << Cols << endl;
		for (auto* curr = head->Next; curr; curr = curr->Next) {
			curr->ColList.print_row_nonzero();
		}
	}
	void Add(SparseMatrix& matrix) {
		assert(matrix.Cols == Cols and matrix.Rows == Rows);
		RowNode* curr = matrix.head->Next;
		for (int i = 0; i < Rows; i++) {
			if (curr->Index == i) {
				RowNode* temp = get_row(i, true);
				temp->ColList.Add(curr->ColList);
				curr = curr->Next;
			}
		}
	}

};

void test_col() {
	ColumnList collst(12);
	collst.SetValue(10, 10);
	collst.SetValue(5, 5);
	collst.SetValue(2, 2);
	collst.SetValue(7, 7);
	collst.SetValue(4, 4);
	//collst.print_row();
	collst.print_row_nonzero();
	collst.Add(collst);
	collst.print_row_nonzero();
}

void test_sparse() {
	SparseMatrix mat(10, 10);
	mat.SetValue(5, 3, 5);
	mat.SetValue(7, 3, 7);
	mat.SetValue(2, 3, 2);
	mat.SetValue(0, 3, 2);
	mat.SetValue(6, 5, 6);
	mat.SetValue(4, 5, 4);
	mat.SetValue(3, 7, 3);
	mat.SetValue(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print_matrix();
	mat.print_matrix_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.SetValue(5, 1, 9);
	mat2.SetValue(6, 3, 8);
	mat2.SetValue(9, 9, 9);
	mat.Add(mat2);
	mat.print_matrix_nonzero();
}

int main()
{
	test_col();
	test_sparse();
	cout << "NO RTE\n";

}
