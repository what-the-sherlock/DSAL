/* EXP 3 : Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree 

-i. Insert new node, 
ii. Find number of nodes in longest path from root, 
iii. Minimum data value found in the tree, 
iv. Change a tree so that the roles of the left and right pointers are swapped at every node, 
v. Search a value.*/


#include <iostream>
using namespace std;

class node
{
    int data;
    node *lc;
    node *rc;

public:
    node *root;
    node()
    {
        root = lc = rc = NULL;
    }

    void create()
    {
        node *temp, *curr;
        int ans;
        do
        {
            temp = new node;
            cout << "enter the value which u want to insert=";
            cin >> temp->data;

            if (root == NULL)
            {

                root = temp;
            }
            else
            {
                curr = root;

                while (1)
                {
                    if (temp->data < curr->data)
                    {
                        if (curr->lc == NULL)
                        {
                            curr->lc = temp;
                            break;
                        }
                        else
                        {
                            curr = curr->lc;
                        }
                    }
                    if (temp->data > curr->data)
                    {
                        if (curr->rc == NULL)
                        {
                            curr->rc = temp;
                            break;
                        }
                        else
                        {
                            curr = curr->rc;
                        }
                    }
                }
            }
            cout << "enter your choice 1 for continue=";
            cin >> ans;
        } while (ans == 1);
    }

    void display()
    {
        rec_preorder(root);
    }

    void rec_preorder(node *root)
    {
        node *t = root;
        if (t != NULL)
        {
            cout << t->data << "->";
            rec_preorder(t->lc);
            rec_preorder(t->rc);
        }
    }
    void rec_inorder(node *root)
    {
        node *t = root;
        if (t != NULL)
        {
            rec_inorder(t->lc);
            cout << t->data << "->";
            rec_inorder(t->rc);
        }
    }
    void rec_posttorder(node *root)
    {
        node *t = root;
        if (t != NULL)
        {
            rec_posttorder(t->lc);
            rec_posttorder(t->rc);
            cout << t->data << "->";
        }
    }
    void displayin()
    {
        rec_inorder(root);
    }
    void displaypost()
    {
        rec_posttorder(root);
    }

    /*void search()
    {
        int key;
        cout << "enter the value of key element";
        cin >> key;
        node *curr;
        curr = new node;

        curr = root;

        while (curr != NULL)
        {

            if (curr->data == key)
            {
                cout << "element found in bst";
            }
            else if (curr->data < key)
            {
                curr = curr->rc;
            }
            else
            {
                curr = curr->lc;
            }
        }
        cout << "element not found";
    }*/
    node *search(node *root, int key)
    {

        if (root == NULL || root->data == key)
        {
            return root;
        }
        if (root->data > key)
        {
            search(root->lc, key);
        }
        else
            search(root->rc, key);
    }
    void minnode(node *root)
    {
        if (root == NULL)
        {
            cout << "empty tree";
        }
        else
        {
            node *t = root;
            while (t->lc != NULL)
            {
                t = t->lc;
            }
            cout << "minmum node=" << t->data;
        }
    }
    void maxnode(node *root)
    {
        if (root == NULL)
        {
            cout << "empty tree";
        }
        else
        {
            node *t = root;
            while (t->rc != NULL)
            {
                t = t->rc;
            }
            cout << "maximum node=" << t->data;
        }
    }
    int maxDepth(node *root)
    {
        if (root == NULL)
            return -1;
        else
        {
            node *t = root;
            /* compute the depth of each subtree */
            int lDepth = maxDepth(t->lc);
            int rDepth = maxDepth(t->rc);

            /* use the larger one */
            if (lDepth > rDepth)
                return (lDepth+1 );
            else
                return (rDepth+1 );
        }
    }
    
};

int main()
{
    node obj;
    int n, a;
    /*
    cout << "enter the total no of nodes present in tree";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        obj.create();
    }*/
    obj.create();

    obj.display();
    cout << endl;
    // obj.displayin();
    cout << endl;
    // obj.displaypost();
    cout << endl;
    cout << "key=";
    cin >> a;
    if (obj.search(obj.root, a) == NULL)
    {
        cout << "not found";
    }
    else
    {
        cout << "found";
    }
    cout << endl;
    obj.minnode(obj.root);
    cout << endl;
    obj.maxnode(obj.root);
    cout << endl;
    cout << obj.maxDepth(obj.root);
    return 0;
}