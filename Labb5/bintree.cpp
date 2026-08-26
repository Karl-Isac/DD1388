#include "bintree.h"

void insert(Node * & p, int key, double to_be_inserted) {
    if (p == nullptr) {
        p = new Node{key, to_be_inserted, nullptr, nullptr};
    }
    else if (key < p->key) {
        insert(p->left, key, to_be_inserted);
    }
    else if (key > p->key) {
        insert(p->right, key, to_be_inserted);
    }
    else {
        p->data = to_be_inserted; // Update existing key
    }
}
void remove(Node * & p, const int & key) {
    if (p == nullptr) {
        return;
    }
    if (key < p->key) {
        remove(p->left, key);
    }
    else if (key > p->key) {
        remove(p->right, key);
    }
    else {
        if (p->left == nullptr) {
            Node * temp = p;
            p = p->right;
            delete temp;
        }
        else if (p->right == nullptr) {
            Node * temp = p;
            p = p->left;
            delete temp;
        }
        else {
            if (max_height(p->right) < max_height(p->left)) { // Fippel, kanske se över :/
                Node * temp = p->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                p->key = temp->key;
                p->data = temp->data;
                remove(p->right, temp->key);
            }
            else {
                Node * temp = p->left;
                while (temp->right != nullptr) {
                    temp = temp->right;
                }
                p->key = temp->key;
                p->data = temp->data;
                remove(p->left, temp->key);
            }
        }
    }
}

const double & find(Node * p, const int & to_be_found) {
    if (p == nullptr) {
        throw runtime_error("Key not found");
    }
    if (to_be_found < p->key) {
        return find(p->left, to_be_found);
    }
    else if (to_be_found > p->key) {
        return find(p->right, to_be_found);
    }
    else {
        return p->data;
    }
}

double & edit(Node * p, const int & to_be_changed) {
    if (p == nullptr) {
        throw runtime_error("Key not found");
    }
    if (to_be_changed < p->key) {
        return edit(p->left, to_be_changed);
    }
    else if (to_be_changed > p->key) {
        return edit(p->right, to_be_changed);
    }
    else {
        return p->data;
    }
}

void delete_tree(Node * & p) {
    if (p != nullptr) {
        delete_tree(p->left);
        delete_tree(p->right);
        delete p;
        p = nullptr;
    }
}

unsigned int max_height(Node * p) {
    if (p == nullptr) {
        return 0;
    }
    unsigned int left_height = max_height(p->left);
    unsigned int right_height = max_height(p->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

unsigned int min_height(Node * p) {
    if (p == nullptr) {
        return 0;
    }
    unsigned int left_height = min_height(p->left);
    unsigned int right_height = min_height(p->right);
    return (left_height < right_height) ? left_height + 1 : right_height + 1;
}
unsigned int size(Node * p) {
    if (p == nullptr) {
        return 0;
    }
    return size(p->left) + size(p->right) + 1;
}

bool is_balanced(Node * p) {
    if (p == nullptr) {
        return true;
    }
    return size(p->left) == size(p->right) && is_balanced(p->left) && is_balanced(p->right);
}

void print_tree(Node* p, int depth) {
    if (p == nullptr)
        return;
    print_tree(p->right, depth + 1);

    cout << string(depth * 5, ' ');
    cout << "(" << p->key << ")[" << p->data << "]\n";

    print_tree(p->left, depth + 1);
}

void loop(Node * & tree, const string & cmd) {
        if (cmd == "insert") {
            int x;
            cin >> x;
            double to_be_inserted;
            cin >> to_be_inserted;
            insert(tree, x, to_be_inserted);
        }
        else if (cmd == "remove") {
            int x;
            cin >> x;
            remove(tree, x);
        }
        else if (cmd == "edit") {
            int x;
            cin >> x;
            double to_change;
            cin >> to_change;
            edit(tree, x) = to_change;
        }
        else if (cmd == "delete_tree") {
            delete_tree(tree);
        }
        else if (cmd == "max_height") {
            cout << max_height(tree) << endl;
        }
        else if (cmd == "min_height") {
            cout << min_height(tree) << endl;
        }
        else if (cmd == "size") {
            cout << size(tree) << endl;
        }
        else if (cmd == "is_balanced") {
            cout << is_balanced(tree) << endl;
        }
        else if (cmd == "print") {
            print_tree(tree);
        }
        else if (cmd == "find") {
            int x;
            cin >> x;
            try {
                const double & value = find(tree, x);
                cout << "Found: " << value << endl;
            }
            catch (const runtime_error & e) {
                cout << e.what() << endl;
            }
        }
        else if (cmd == "get_node") {
            int x;
            cin >> x;
            try {
                Node * & node = get_node(tree, x);
                string cmd_2;
                cin >> cmd_2;
                loop(node, cmd_2);
            }
            catch (const runtime_error & e) {
                cout << e.what() << endl;
            }
        }
        else {
            cout << "Unknown command: " << cmd << endl;
        }
}

Node * & get_node(Node * & p, const int & key) {
    if (p == nullptr) {
        throw runtime_error("Key not found");
    }
    if (key < p->key) {
        return get_node(p->left, key);
    }
    else if (key > p->key) {
        return get_node(p->right, key);
    }
    else {
        return p;
    }
}

int main() {
    Node * tree = nullptr;

    string cmd;

    while (cin >> cmd) {
        loop(tree, cmd);
    }
}