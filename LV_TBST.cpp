#include <iostream>
using namespace std;
struct Node {
struct Node *left, *right;
int data;
int lthread;
int rthread;
};
class TBST
{  public:
    struct Node* root = NULL;
   int key;
  struct Node* insert(struct Node* root, int ikey);  
  struct Node* inSucc(struct Node* ptr);
  struct Node* inorderSuccessor(struct Node* ptr);
  void inorder(struct Node* root);
  struct Node* inPred(struct Node* ptr);
  struct Node* caseA(struct Node* root, struct Node* par,
struct Node* ptr);
struct Node* caseB(struct Node* root, struct Node* par,
struct Node* ptr);
struct Node* caseC(struct Node* root, struct Node* par,
struct Node* ptr);
struct Node* delThreadedBST(struct Node* root, int dkey);
};
struct Node* TBST::insert(struct Node* root, int ikey)
{
  Node* ptr = root;
  Node* par = NULL;
while (ptr != NULL) {
par = ptr; 
if (ikey<ptr->data) {
if (ptr->lthread == 1)
ptr = ptr->left;
else
break;
          }
else {
if (ptr->rthread == 1)
ptr = ptr->right;
else
break;
              }
         }
    Node* tmp = new Node;
tmp->data = ikey;
tmp->lthread = 0;
tmp->rthread = 0;
if (par == NULL) {
root = tmp;
tmp->left = NULL;
tmp->right = NULL;
    }
else if (ikey< (par->data)) {
tmp->left = par->left;
tmp->right = par;
par->lthread = 1;
par->left = tmp;
        }
else {
tmp->left = par;
tmp->right = par->right;
par->rthread = 1;
par->right = tmp;
     }
return root;
 }
struct Node* TBST::inSucc(struct Node* ptr)
{
if (ptr->rthread == 0)
return ptr->right;

ptr = ptr->right;
while (ptr->lthread == 1)
ptr = ptr->left;

return ptr;
}
struct Node* TBST::inorderSuccessor(struct Node* ptr)
{
if (ptr->rthread == 0)
return ptr->right;
ptr = ptr->right;
while (ptr->lthread == 1)
ptr = ptr->left;
return ptr;
}
void TBST:: inorder(struct Node* root)
{
if (root == NULL)
cout<<"Tree is empty";
struct Node* ptr = root;
while (ptr->lthread == 1)
ptr = ptr->left;
while (ptr != NULL) {
cout<<ptr->data;
ptr = inorderSuccessor(ptr);
       }
}
struct Node* TBST::inPred(struct Node* ptr)
{
if (ptr->lthread == 0)
return ptr->left;

ptr = ptr->left;
while (ptr->rthread == 1)
ptr = ptr->right;
return ptr;
}
struct Node* TBST::caseA(struct Node* root, struct Node* par,
struct Node* ptr)
{
if (par == NULL)
root = NULL;
else if (ptr == par->left) {
par->lthread = 0;
par->left = ptr->left;
          }
else
          {
par->rthread = 0;
par->right = ptr->right;
        }
free(ptr);
return root;
}
struct Node* TBST::caseB(struct Node* root, struct Node* par,
struct Node* ptr)
{
struct Node* child;
if (ptr->lthread == 1)
child = ptr->left;
else
child = ptr->right;
if (par == NULL)
root = child;

else if (ptr == par->left)
par->left = child;
else
par->right = child;

    // Find successor and predecessor
    Node* s = inSucc(ptr);
    Node* p = inPred(ptr);

    // If ptr has left subtree.
if (ptr->lthread == 1)
p->right = s;

    // If ptr has right subtree.
else {
if (ptr->rthread == 1)
s->left = p;
    }

free(ptr);
return root;
}

// Here 'par' is pointer to parent Node and 'ptr' is
// pointer to current Node.
struct Node* TBST::caseC(struct Node* root, struct Node* par,
struct Node* ptr)
{
    // Find inorder successor and its parent.
struct Node* parsucc = ptr;
struct Node* succ = ptr->right;

    // Find leftmost child of successor
while (succ->lthread==1) {
parsucc = succ;
succ = succ->left;
    }

ptr->data = succ->data;

if (succ->lthread == 0 &&succ->rthread == 0)
root = caseA(root, parsucc, succ);
else
root = caseB(root, parsucc, succ);

return root;
}

// Deletes a key from threaded BST with given root and
// returns new root of BST.
struct Node* TBST::delThreadedBST(struct Node* root, int dkey)
{
    // Initialize parent as NULL and ptrent
    // Node as root.
struct Node *par = NULL, *ptr = root;

    // Set 0 if key is found
int found = 0;

    // Search key in BST : find Node and its
    // parent.
while (ptr != NULL) {
if (dkey == ptr->data) {
found = 1;
break;
        }
par = ptr;
if (dkey<ptr->data) {
if (ptr->lthread == 1)
ptr = ptr->left;
else
break;
        }
else {
if (ptr->rthread == 1)
ptr = ptr->right;
else
break;
        }
    }

if (found == 0)
cout<<"dkey not present in tree\n";

    // Two Children
else if (ptr->lthread == 1 &&ptr->rthread == 1)
root = caseC(root, par, ptr);

    // Only Left Child
else if (ptr->lthread == 1)
root = caseB(root, par, ptr);

    // Only Right Child
else if (ptr->rthread == 1)
root = caseB(root, par, ptr);

    // No child
else
root = caseA(root, par, ptr);

return root;
}

// Driver Program
int main()
{
    TBST t;
    struct Node* root = NULL;
   int key;
while(1)
   {
int ch;
cout<<"\n enter the choice";
cout<<"\n 1.insert data";
cout<<"\n 2.delete a data";
cout<<"\n 3.display all data";
cout<<"\n 4.exit";
cin>>ch;
switch(ch)
   {
case 1:
cout<<"enter data to be inserted";
cin>>key;
root = t.insert(root, key);
break;
case 2:
cout<<"enter data to be deleted";
cin>>key;
root = t.delThreadedBST(root, key);
break;
case 3:  
t.inorder(root);
break;
case 4:  exit(0);

default:
cout<<"\n invalid entry";
    }             
    }
return 0;
}  