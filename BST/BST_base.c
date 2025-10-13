#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int data;
} INFO;

typedef struct node *nd;
struct node {
	INFO data;
	nd left;
	nd right;
} BST;

void insert_node(nd *root, int data);
bool search(nd root, int key, INFO *info);
bool delete_nochild(nd *root, nd *ptr, nd *ptr1);
bool delete_one(nd *root, nd *ptr, nd *ptr1);
void delete_Two(nd *ptr, nd *ptr1);
void view_Tree(nd ptr);

void insert_node(nd *root, int data) {
	nd ptr, ptr1, temp = malloc(sizeof(BST));
	temp->data.data = data;
	temp->left = NULL;
	temp->right = NULL;
	
	if (*root == NULL) {
		*root = temp;
		return;
	} else {
		ptr = *root;
	}

	while (ptr !=  NULL) {
		ptr1 = ptr;
		if (data <= ptr->data.data) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}

	if (data <= ptr1->data.data) {
		ptr1->left = temp;
	} else {
		ptr1->right = temp;
	}
}

bool search(nd root, int key, INFO *info) {
	bool found = false;
	nd ptr = root;
	while (ptr != NULL) {
		if (key == ptr->data.data) {
			found = true;
			*info = ptr->data;
			break;
		}

		else if (key < ptr->data.data) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}
	return found;
}

bool delete_nochild(nd *root, nd *ptr, nd *ptr1) {
	if (*ptr1 == NULL) {
		*root = NULL;
	} else {
		if ((*ptr)->data.data < (*ptr1)->data.data) {
			(*ptr1)->left = NULL;
		} else {
			(*ptr1)->right = NULL;
		}
	}
	free(*ptr);
	return true;
}

bool delete_one(nd *root, nd *ptr, nd *ptr1) {
	if (*root == *ptr) {
		if ((*ptr)->left == NULL) {
			*root = (*ptr)->right;
		} else {
			*root = (*ptr)->left;
		}
	} else {
		if ((*ptr)->data.data < (*ptr1)->data.data) {
			if ((*ptr)->right == NULL) {
				(*ptr1)->left = (*ptr)->left;
			} else {
				(*ptr1)->left = (*ptr)->right;
			}
		}
		else {
			if ((*ptr)->right == NULL) {
				(*ptr1)->right = (*ptr)->left;
			} else {
				(*ptr1)->right = (*ptr)->right;
			}
		}
	}
	free(*ptr);

	return true;
}

void delete_Two(nd *ptr, nd *ptr1) {
	nd ptr2 = NULL;

	*ptr1 = (*ptr)->right;
	while ((*ptr1)->left != NULL) {
		ptr2 = *ptr1;
		(*ptr1) = (*ptr1)->left;
	}
	(*ptr)->data = (*ptr1)->data;

	if (ptr2 == NULL) {
		if((*ptr1)->right != NULL) {
			(*ptr)->right = (*ptr1)->right;
		} else {
			(*ptr)->right = NULL;
		}
	}
	else {
		if ((*ptr1)->right != NULL) {
			ptr2->left = (*ptr1)->right;
		} else {
			ptr2->left = NULL;
		}
	}
	free(*ptr1);
}

void view_Tree(nd ptr) {
	if (ptr == NULL) return;

	if(ptr->left != NULL) {
		view_Tree(ptr->left);
	}
	printf("%d ", ptr->data.data);
	if(ptr->right != NULL) {
		view_Tree(ptr->right);
	}
}

int main() {
	nd root = NULL;
	INFO info;

	// Insert some nodes
	insert_node(&root, 50);
	insert_node(&root, 30);
	insert_node(&root, 70);
	insert_node(&root, 20);
	insert_node(&root, 40);
	insert_node(&root, 60);
	insert_node(&root, 80);

	printf("BST (inorder): ");
	view_Tree(root);
	printf("\n");

	// Search test
	int key = 40;
	if (search(root, key, &info))
		printf("Found %d in tree!\n", key);
	else
		printf("%d not found.\n", key);

	// Delete test cases (manually calling correct delete functions)
	// 1️⃣ Leaf delete (no children)
	nd ptr = root, parent = NULL;
	while (ptr != NULL && ptr->data.data != 20) {
		parent = ptr;
		if (20 < ptr->data.data)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	if (ptr != NULL)
		delete_nochild(&root, &ptr, &parent);

	printf("After deleting 20 (leaf): ");
	view_Tree(root);
	printf("\n");

	// 2️⃣ Node with one child
	ptr = root; parent = NULL;
	while (ptr != NULL && ptr->data.data != 30) {
		parent = ptr;
		if (30 < ptr->data.data)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	if (ptr != NULL)
		delete_one(&root, &ptr, &parent);

	printf("After deleting 30 (one child): ");
	view_Tree(root);
	printf("\n");

	// 3️⃣ Node with two children
	ptr = root; parent = NULL;
	while (ptr != NULL && ptr->data.data != 50) {
		parent = ptr;
		if (50 < ptr->data.data)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	if (ptr != NULL)
		delete_Two(&ptr, &parent);

	printf("After deleting 50 (two children): ");
	view_Tree(root);
	printf("\n");

	return 0;
}
