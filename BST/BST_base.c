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

void insert_node(nd *root, int data) {
	nd ptr, ptr1, temp = malloc(sizeof(BST));
	temp->data.data = data;
	temp->left = NULL;
	temp->right = NULL;
	
	if (*root == NULL) {
		*root = temp;
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

bool delete_one(nd *root, nd *ptr, nd *ptr1) {
	if (*root == *ptr) {
		if ((*ptr)->left == NULL) {
			*root = (*ptr)->right;
		} else {
			*root = (*ptr)->left;
		}
	} else {
		if ((*ptr)->data.data < (*ptr)->data.data) {
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

	*ptr1 = (*ptr1)->right;
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
}

int main() {

}
