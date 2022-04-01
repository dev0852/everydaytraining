#include <bits/stdc++.h>
using namespace std;
//this class implements a red black tree
class rbtree{
    private:
        //this class represents a node in the tree
        class node{
            public:
                int data;
                bool color;
                node *left, *right, *parent;
                node(int data){
                    this->data = data;
                    this->color = true;
                    this->left = NULL;
                    this->right = NULL;
                    this->parent = NULL;
                }
        };
        node *root;
        //this function rotates the tree to the left
        void rotate_left(node *x){
            node *y = x->right;
            x->right = y->left;
            if(y->left != NULL){
                y->left->parent = x;
            }
            y->parent = x->parent;
            if(x->parent == NULL){
                root = y;
            }
            else if(x == x->parent->left){
                x->parent->left = y;
            }
            else{
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }
        //this function rotates the tree to the right
        void rotate_right(node *x){
            node *y = x->left;
            x->left = y->right;
            if(y->right != NULL){
                y->right->parent = x;
            }
            y->parent = x->parent;
            if(x->parent == NULL){
                root = y;
            }
            else if(x == x->parent->left){
                x->parent->left = y;
            }
            else{
                x->parent->right = y;
            }
            y->right = x;
            x->parent = y;
        }
        //this function fixes the tree after insertion
        void fix_insert(node *z){
            node *y = NULL;
            while(z->parent != NULL && z->parent->color == true){
                if(z->parent == z->parent->parent->left){
                    y = z->parent->parent->right;
                    if(y != NULL && y->color == true){
                        z->parent->color = false;
                        y->color = false;
                        z->parent->parent->color = true;
                        z = z->parent->parent;
                    }
                    else{
                        if(z == z->parent->right){
                            z = z->parent;
                            rotate_left(z);
                        }
                        z->parent->color = false;
                        z->parent->parent->color = true;
                        rotate_right(z->parent->parent);
                    }
                }
                else{
                    y = z->parent->parent->left;
                    if(y != NULL && y->color == true){
                        z->parent->color = false;
                        y->color = false;
                        z->parent->parent->color = true;
                        z = z->parent->parent;
                    }
                    else{
                        if(z == z->parent->left){
                            z = z->parent;
                            rotate_right(z);
                        }
                        z->parent->color = false;
                        z->parent->parent->color = true;
                        rotate_left(z->parent->parent);
                    }
                }
            }
            root->color = false;
        }
        //this function inserts a node in the tree
        void insert(node *z){
            node *y = NULL;
            node *x = root;
            while(x != NULL){
                y = x;
                if(z->data < x->data){
                    x = x->left;
                }
                else{
                    x = x->right;
                }
            }
            z->parent = y;
            if(y == NULL){
                root = z;
            }
            else if(z->data < y->data){
                y->left = z;
            }
            else{
                y->right = z;
            }
            fix_insert(z);
        }
        //this function deletes a node from the tree
        void delete_node(node *z){
            node *y = z;
            node *x = NULL;
            bool y_original_color = y->color;
            if(z->left == NULL){
                x = z->right;
                transplant(z, z->right);
            }
            else if(z->right == NULL){
                x = z->left;
                transplant(z, z->left);
            }
            else{
                y = tree_minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if(y->parent == z){
                    x->parent = y;
                }
                else{
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            if(y_original_color == false){
                fix_delete(x);
            }
        }
        //this function fixes the tree after deletion
        void fix_delete(node *x){
            node *w = NULL;
            while(x != root && x->color == false){
                if(x == x->parent->left){
                    w = x->parent->right;
                    if(w->color == true){
                        w->color = false;
                        x->parent->color = true;
                        rotate_left(x->parent);
                        w = x->parent->right;
                    }
                    if(w->left->color == false && w->right->color == false){
                        w->color = true;
                        x = x->parent;
                    }
                    else{
                        if(w->right->color == false){
                            w->left->color = false;
                            w->color = true;
                            rotate_right(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        w->right->color = false;
                        rotate_left(x->parent);
                        x = root;
                    }
                }
                else{
                    w = x->parent->left;
                    if(w->color == true){
                        w->color = false;
                        x->parent->color = true;
                        rotate_right(x->parent);
                        w = x->parent->left;
                    }
                    if(w->right->color == false && w->left->color == false){
                        w->color = true;
                        x = x->parent;
                    }
                    else{
                        if(w->left->color == false){
                            w->right->color = false;
                            w->color = true;
                            rotate_left(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        w->left->color = false;
                        rotate_right(x->parent);
                        x = root;
                    }
                }
            }
            x->color = false;
        }
        //this function deletes a node from the tree
        void transplant(node *u, node *v){
            if(u->parent == NULL){
                root = v;
            }
            else if(u == u->parent->left){
                u->parent->left = v;
            }
            else{
                u->parent->right = v;
            }
            if(v != NULL){
                v->parent = u->parent;
            }
        }
        //this function finds the minimum node in the tree
        node *tree_minimum(node *x){
            while(x->left != NULL){
                x = x->left;
            }
            return x;
        }
        //this function finds the maximum node in the tree
        node *tree_maximum(node *x){
            while(x->right != NULL){
                x = x->right;
            }
            return x;
        }
        //this function finds the successor of a node in the tree
        node *tree_successor(node *x){
            if(x->right != NULL){
                return tree_minimum(x->right);
            }
            node *y = x->parent;
            while(y != NULL && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }
        //this function finds the predecessor of a node in the tree
        node *tree_predecessor(node *x){
            if(x->left != NULL){
                return tree_maximum(x->left);
            }
            node *y = x->parent;
            while(y != NULL && x == y->left){
                x = y;
                y = y->parent;
            }
            return y;
        }
        //this function rotates the tree to the left
        void rotate_left(node *x){
            node *y = x->right;
            x->right = y->left;
            if(y->left != NULL){
                y->left->parent = x;
            }
            y->parent = x->parent;
            if(x->parent == NULL){
                root = y;
            }
            else if(x == x->parent->left){
                x->parent->left = y;
            }
            else{
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }
        //this function rotates the tree to the right
        void rotate_right(node *x){
            node *y = x->left;
            x->left = y->right;
            if(y->right != NULL){
                y->right->parent = x;
            }
            y->parent = x->parent;
            if(x->parent == NULL){
                root = y;
            }
            else if(x == x->parent->right){
                x->parent->right = y;
            }
            else{
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }
        //this function prints the tree in order
        void print_tree_in_order(node *x){
            if(x != NULL){
                print_tree_in_order(x->left);
                cout << x->data << " ";
                print_tree_in_order(x->right);
            }
        }
        //this function prints the tree in preorder
        void print_tree_pre_order(node *x){
            if(x != NULL){
                cout << x->data<< " ";
                print_tree_pre_order(x->left);
                print_tree_pre_order(x->right);
            }
        }
        //this function prints the tree in postorder
        void print_tree_post_order(node *x){
            if(x != NULL){
                print_tree_post_order(x->left);
                print_tree_post_order(x->right);
                cout << x->data << " ";
            }
        }
        //this function prints the tree in levelorder
        void print_tree_level_order(node *x){
            queue<node *> q;
            q.push(x);
            while(!q.empty()){
                node *y = q.front();
                q.pop();
                cout << y->data<< " ";
                if(y->left != NULL){
                    q.push(y->left);
                }
                if(y->right != NULL){
                    q.push(y->right);
                }
            }
        }
};
int main()
{
    int n;
    cout << "Enter the number of elements in the tree: ";
    cin >> n;
    int a[n];
    cout << "Enter the elements of the tree: ";
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    rb_tree t;
    for(int i = 0; i < n; i++){
        t.insert(a[i]);
    }
    cout << "The tree in order is: ";
    t.print_tree_in_order(t.root);
    cout << endl;
    cout << "The tree in preorder is: ";
    t.print_tree_pre_order(t.root);
    cout << endl;
    cout << "The tree in postorder is: ";
    t.print_tree_post_order(t.root);
    cout << endl;
    cout << "The tree in levelorder is: ";
    t.print_tree_level_order(t.root);
    cout << endl;
    cout << "Enter the element to be deleted: ";
    int x;
    cin >> x;
    t.delete_node(x);
    cout << "The tree in order is: ";
    t.print_tree_in_order(t.root);
    cout << endl;
    cout << "The tree in preorder is: ";
    t.print_tree_pre_order(t.root);
    cout << endl;
    cout << "The tree in postorder is: ";
    t.print_tree_post_order(t.root);
    cout << endl;
    cout << "The tree in levelorder is: ";
    t.print_tree_level_order(t.root);
    cout << endl;
    return 0;
}

        
