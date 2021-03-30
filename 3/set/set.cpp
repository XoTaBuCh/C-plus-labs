#include <iostream>
//AVL tree
using namespace std;

template <typename T>
class set {
private:
    struct node { //creating node structure 
        T data;
        node* left;
        node* right;
        int height;

        node(T value) { //constuctor
            data = value;
            height = 1;
            left = right = NULL;
        } 
    };
    node* root = NULL; // root of our tree

    int Height(node* a) { // ruturns the height
        if (a != NULL) {
            return a->height;
        }
        else {
            return 0;
        }
    }

    void Fixheight(node* a) { // update height after manipulations
        int hl = Height(a->left);
        int hr = Height(a->right);
        if (hl > hr) {
            a->height = hl + 1;
        }
        else {
            a->height = hr + 1;
        }
    }

    node* Rotateleft(node* a) { // small turning on left
        node* b = a->right;
        a->right = b->left;
        b->left = a;
        Fixheight(a);
        Fixheight(b);
        return b;
    }

    node* Rotateright(node* a) { // small turning on right
        node* b = a->left;
        a->left = b->right;
        b->right = a;
        Fixheight(a);
        Fixheight(b);
        return b;
    }

    node* Balance(node* a) { // calculates height differences in nodes and balances using turns
        Fixheight(a);
        if (Height(a->left) - Height(a->right) == -2) {
            node* b = a->right;
            if (Height(b->left) - Height(b->right) > 0) {
                a->right = Rotateright(a->right);
            }
            return Rotateleft(a);
        }
        if (Height(a->left) - Height(a->right) == 2) {
            node* b = a->left;
            if (Height(b->left) - Height(b->right) < 0) {
                a->left = Rotateleft(a->left);
            }
            return Rotateright(a);
        }
        return a;
    }

    node* Insert(node* a, T value) { // inserting an element into a set via binary search for required position
        if (a == NULL) {
            a = new node(value);
            return a;
        }
        if (value < a->data) {
            a->left = Insert(a->left, value);
        }
        else if ( value > a->data) {
            a->right = Insert(a->right, value);
        }
        return Balance(a);
    }

    node* Remove_min(node* a) { // replacing the left-closest node to the removing node with balance
        if (a->right == 0)
            return a->left;
        a->right = Remove_min(a->right);
        return Balance(a);
    }

    node* Remove(node* a, T value) { // removing the required node
        if (a == NULL) {
            return 0;
        }
        if (value > a->data) {
            a->right = Remove(a->right, value);
        }
        else if (value < a->data) {
            a->left = Remove(a->left, value);
        }
        else {
            if (a->left == NULL) {
                node* b = a->right;
                delete a;
                return b;
            }
            node* b = a->left;
            if (b->right != NULL) {
                do {
                    b = b->right;
                } while (b->right != NULL);
            }
                b->left = Remove_min(a->left);
                b->right = a->right;
                return Balance(b);
        }
        Balance(a);
    }
    void Output(node* a) { // set output
        if ((a->left == NULL) && (a->right == NULL)) {
            cout << a->data << " ";
        }
        else {
            if (a->left != NULL) {
                Output(a->left);
            }
            cout << a->data << " ";
            if (a->right != NULL) {
                Output(a->right);
            }     
        }
    }
public:
    void insert(T value) { // public method that calls private-insert method, passing a pointer to the root of tree
        root = Insert(root, value);
    }

    void remove(T value) { // similarly for deliting
        root = Remove(root, value);
    }
    
    void output() { // similarly for output
        Output(root);
    }
};

int main()
{
    set<int> NIKITKA;
    NIKITKA.insert(54);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(36);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(26);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(31);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(59);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(5);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(69);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(70);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(145);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(1);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(254);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(200);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(194);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(56);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(146);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(132);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(148);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(220);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(213);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(240);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(7);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(21);
    NIKITKA.output(); cout << endl;
    NIKITKA.insert(74);
    NIKITKA.output(); cout << endl;
}