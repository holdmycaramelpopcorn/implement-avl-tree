# implement-avl-tree
This is a short code in C to implement the AVL tree and perform some operations on it.

Just run the C file. There is no make file here.

## How to build

``` 
gcc dsatrees.c -o avl
```

## How to run

```
./avl
```
## Description
It is observed that BST's worst-case performance is closest to linear search algorithms, that is Ο(n). In real-time data, we cannot predict data patterns and their frequencies. So, a need arises to balance out the existing BST.
Named after their inventor Adelson, Velski & Landis, AVL trees are height balancing binary search tree. AVL tree checks the height of the left and right subtrees and assures that the difference is not more than 1. This difference is called the Balance Factor.
BalanceFactor = height(left-subtree) − height(right-subtree)

If the difference in the height of left and right subtrees is more than 1, the tree is balanced using some rotation techniques.
AVL Rotations
To balance itself, an AVL tree may perform the following four kinds of rotations −
Left rotation
Right rotation
Left-Right rotation
Right-Left rotation
Each of these rotations have been implemented in the code, along with a driver function and standard traversal techniques. There is also a function to print the structure of a rearranged AVL tree (and each node’s balance factor) using adequate spacing.
