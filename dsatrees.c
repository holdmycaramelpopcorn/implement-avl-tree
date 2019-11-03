#include<stdio.h> 
#include<stdlib.h> 
#define COUNT 10
// An AVL tree node 
struct node 
{ 
	int key; 
	struct node* left; 
	struct node* right; 
	int height; 
}; 
typedef struct node* NODE;
// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get the height of the tree 
int height(NODE N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
NODE newNode(int key) 
{ 
	NODE node = (NODE)malloc(sizeof(struct node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
NODE rightRotate(NODE y) 
{ 
	NODE x = y->left; 
	NODE T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
NODE leftRotate(NODE x) 
{ 
	NODE y = x->right; 
	NODE T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(NODE N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
NODE insert(NODE node, int key) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else // Equal keys are not allowed in BST 
		return node; 

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(NODE root) 
{ 
	if(root != NULL) 
	{ 
		printf("%d ", root->key); 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
}
void inOrder(NODE root) 
{ 
	if(root != NULL) 
	{  
		inOrder(root->left);
		printf("%d ", root->key); 
		inOrder(root->right); 
	} 
}
void postOrder(NODE root) 
{ 
	if(root != NULL) 
	{ 
		postOrder(root->left); 
		postOrder(root->right);
		printf("%d ", root->key);  
	} 
} 
void print2DUtil(NODE root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d(%d)\n", root->key,getBalance(root));
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(NODE root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
} 
NODE minValueNode(NODE node)  
{  
    NODE current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  
  
// Recursive function to delete a NODE 
// with given key from subtree with  
// given root. It returns root of the  
// modified subtree.  
NODE deleteNode(NODE root, int key)  
{   
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    { printf("\n%d has been deleted\n",key);
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            NODE temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            NODE temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this NODE 
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    } 
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    } 
    return root;  
}  
/* Driver program to test above functions*/
int main() 
{ 
NODE root = NULL; 
int item,n,choice,key;
printf("\nBeginning to build a tree now...\n");
printf("\nEnter number of initial nodes: ");
scanf("%d",&n);
for(int i=0;i<n;i++)
{
	printf("\nEnter element %d\n",(i+1));
	scanf("%d",&item);
	root=insert(root,item);
}
/*Infinite loop to execute until user wishes to terminate*/
while(1){
printf("\nMENU\n");
printf("1. Insert Node\n");
printf("2. Print Tree Structure\n");
printf("3. Delete a node\n");
printf("4. Preorder Traversal\n");
printf("5. Inorder Traversal\n");
printf("6. Post Order Traversal\n");
printf("7. Exit\n");
printf("\nEnter Choice\n");
scanf("%d",&choice);
switch(choice)
{
	case 1: printf("\nEnter node data: ");
		scanf("%d",&item);
		root=insert(root,item);
		break;
	case 2: printf("\nTree structure is:\n");
		printf("NB: Printing balance factor in brackets\n");
		print2D(root);
		break;
	case 3: printf("\nEnter key for deletion\n");
		scanf("%d",&key);
		root=deleteNode(root,key);
		break;
	case 4: printf("\nPreorder traversal: \n");
		preOrder(root);
		printf("\n");
		break;
	case 5: printf("\nInorder traversal: \n");
		inOrder(root);
		printf("\n");
		break;
	case 6: printf("\nPostorder traversal: \n");
		postOrder(root);
		printf("\n");
		break;
	default: printf("\nExiting...\n");
		 exit(0);
}
}
return 0; 
} 

