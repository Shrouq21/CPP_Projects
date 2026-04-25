#include<bits/stdc++.h>
using namespace std;

struct Node {
    Node* prev{};
    Node* next{};
    int val{};
    Node(int val) :val(val) {}
};

class ArrayLinkedList {
private:
    Node* head{};
    Node* tail{};
    int length{};
public:
    ArrayLinkedList(int length) :length(length) {
        int len = length;
        while (len) {
            Node* temp = new Node(-1);
            if (len == length) {
                head = tail = temp;
            }
            else {
                tail->next = temp;
                temp->next = nullptr;
                temp->prev = tail;
                tail = temp;
            }
            len--;
        }
    }

    void set_value(int value, int index) {
        int i = 0;
        for (Node* node = head; node; node = node->next, ++i) {
            if (i == index) {
                node->val = value;
                break;
            }
        }
    }

   int Get_value(int index) {
    assert(index>=0 and index<length);
        int i = 0;
        for (Node* node = head; node; node = node->next, i++)
        {
            if (i == index) {
              return node->val;
                
            }
        }
    }

    void Print() {
        for (Node* node = head; node; node = node->next)
            if (node->val == -1)cout << 0 << " ";
            else
                cout << node->val << " ";
        cout << endl;
    }

    void Add_Array(const  ArrayLinkedList* list) {
        assert(list->length == length);
        Node* temp = list->head;
        int list_i = 0;
        for (Node* list_node = temp; list_node; list_node = list_node->next, ++list_i) {
            if (list_node->val != -1) {
                int curr_i = 0;
                for (Node* curr_node = head; curr_node; curr_node = curr_node->next, ++curr_i) {
                    if (curr_i == list_i) {
                        if (curr_node->val == -1)curr_node->val = list_node->val;
                        else
                            curr_node->val += list_node->val;
                        break;
                    }
                }
            }
        }
    }

    void Print_array_nonzero() {
        bool chk = 0;
        for (Node* node = head; node; node = node->next) {
            if (node->val != -1) {
                cout << node->val << " ";
                chk = 1;
            }
        }
        if (chk)cout << endl;
    }

};


class SparseMatrix {
private:
    Node* head{};
    Node* tail{};
    int rows{}, columns{};
    vector<ArrayLinkedList*>_2D_Array;
public:
    SparseMatrix(int rows, int columns) :rows(rows), columns(columns) {

        _2D_Array.resize(rows);

        for (int i = 0; i < rows; i++) {
            _2D_Array[i] = new ArrayLinkedList(columns);
        }
    }


    void set_value(int value, int row, int column) {
        for (int i = 0; i < rows; i++) {
            if (i == row) {
                _2D_Array[i]->set_value(value, column);
            }
        }
    }

  int GetValue(int row, int column)
    {
      assert(row >= 0 and row < rows);
      assert(column >= 0 and column < columns);
        for (int i = 0; i < rows; i++) {
            if (row == i) {
                int val = _2D_Array[i]->Get_value(column);
                if (val == -1)return 0;
                else return val;
            }
        }
    }
    void Print() {
        for (int i = 0; i < rows; i++) {
            _2D_Array[i]->Print();

        }
    }

    void Add(const SparseMatrix& matrix) {
        assert(rows == matrix.rows and columns == matrix.columns);
        vector<ArrayLinkedList*>_2D_Temp = matrix._2D_Array;
        for (int i = 0; i < rows; i++) {
            _2D_Array[i]->Add_Array(_2D_Temp[i]);
        }
    }
    void Print_array_nonzero() {
        cout << "Print Matrix: " << rows << " x " << columns << endl;
        for (int i = 0; i < rows; i++) {
            {
                _2D_Array[i]->Print_array_nonzero();

            }
        }
    }

}; int main() {
    SparseMatrix mat(10, 10);
    mat.Print();

    cout << "**********************\n";

    mat.set_value(5, 3, 5);
    mat.set_value(7, 3, 7);
    mat.set_value(2, 3, 2);
    mat.set_value(0, 3, 2);
    mat.set_value(6, 5, 6);
    mat.set_value(4, 5, 4);
    mat.set_value(3, 7, 3);
    mat.set_value(1, 7, 1);
    mat.Print();

    cout << "**********************\n";

    mat.Print_array_nonzero();

    cout << "************************\n";

    cout << mat.GetValue(3, 5) << endl;
    cout << mat.GetValue(1, 1) << endl;
  //  cout << mat.GetValue(10, 10) << endl;
  // 
    cout << "**********************\n";

    SparseMatrix mat2(10, 10);
    mat2.Print();

    cout << "**********************\n";

    mat2.set_value(5, 1, 9);
    mat2.set_value(6, 3, 8);
    mat2.set_value(9, 9, 9);
    mat2.Print();

    cout << "**********************\n";

    mat.Add(mat2);
    mat.Print_array_nonzero();
    cout << "NO RTE\n";

}
