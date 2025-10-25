/*
Description: This code is an inventory simulation that
is implemented using a hashtable which is using
truncation for hashing keys, and double hash for handling
collision. It stores a list of inventory stock, and has a
record of all sold and bought items.

Code by: Franzyl Bjorn L. Macalua
Data Started: Oct 17, 2025
Date Finished: Oct 20, 2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
// #include <conio.h>

#define NUM 3
#define B_CAP 10
#define K 31
#define INCR 7
#define FLUSH while(getchar() != '\n')

typedef struct {
	char item_number[NUM];
	char item_name[30];
	int qty;
	float price;
	char state;
} ITEMS;

typedef struct {
	char sales_number[NUM];
	char item_number[NUM];
	int s_qty;
	char state;
} SALE;

typedef struct {
	char goods_number[NUM];
	char item_number[NUM];
	int g_qty;
	char state;
} GOODS;

typedef struct node_i *nd_i;
struct node_i {
	ITEMS data;
	nd_i next;
} ITEM_NODE;

typedef struct node_s *nd_s;
struct node_s {
	SALE data;
	nd_s next;
} SALE_NODE;

typedef struct node_g *nd_g;
struct node_g {
	GOODS data;
	nd_g next;
} GOODS_NODE;

typedef struct {
	nd_i next;
} I_Next;

typedef struct {
	nd_s next;
} S_Next;

typedef struct {
	nd_g next;
} G_Next;

void init_hmaps(I_Next hash_inv[], S_Next hash_sale[], G_Next hash_goods[]);
ITEMS input(void);
bool input_sale(SALE *data, I_Next hash_inv[], int *index);
bool input_goods(GOODS *data, I_Next hash_inv[], int *index);
int key_cast(char num[]);
int hash_trunc(int key);
int double_hash(int index, int value);
void add_inventory(I_Next hash_inv[], ITEMS data);
int edit_choice(void);
void edit_item(I_Next hash_inv[], char search_key[]);
bool search_inventory(I_Next hash_inv[], char search_key[], int *search_index);
void sales(I_Next hash_sale[], I_Next hash_inv[]);
void goods(I_Next hash_goods[], I_Next hash_inv[]);
void Display_All(I_Next hash_inv[]);
void Display_Sale(I_Next hash_sale[]);
void Display_Goods(I_Next hash_goods[]);
void menu(void);

void init_hmaps(I_Next hash_inv[], S_Next hash_sale[], G_Next hash_goods[]) {
	for (int i = 0; i < B_CAP; i++) {
		hash_inv[i].next = NULL;
		hash_sale[i].next = NULL;
		hash_goods[i].next = NULL;	
	}
}

ITEMS input(void) {
	ITEMS data;

	printf("Enter Item Number:");
	gets(data.item_number);
	printf("Enter Item Name:");
	gets(data.item_name);

	bool isValid = false;
	while (!isValid) {
		printf("Enter Quantity:");
		scanf("%d", &data.qty);
		FLUSH;

		if (data.qty < 0) {
			printf("Quantity cannot be negative\n");
		}
		else {
			isValid = true;
		}
	}

	isValid = false;
	while (!isValid) {
		printf("Enter Price:");
		scanf("%f", &data.price);
		FLUSH;

		if (data.price < 0) {
			printf("Price cannot be negative\n");
		}
		else {
			isValid = true;
		}
	}
	data.state = 'o';

	return data;
}

int key_cast(char num[]){
	int key = 0;
	int L = strlen(num);

	for (int i = 0; i < L; i++) {
		key += num[L - i - 1] * pow(K, i);
	}

	return key;
}

int hash_trunc(int key) {
	int index = key % 10;
	return index;
}

// no need
int double_hash(int index, int value) {
	int increment = 1 + (value % INCR);
	return (index + increment) % B_CAP;
}

void add_inventory(I_Next hash_inv[], ITEMS data) {
	// bool stored = false;
	nd_i temp = malloc(sizeof(ITEM_NODE));
	temp->data = data;
	temp->next = NULL;

	int index = hash_trunc(key_cast(data.item_number));

	if (hash_inv[index].next == NULL)
		temp->next = hash_inv[index].next;
	hash_inv[index].next = temp;

	printf("Inventory Added\n");

}

int edit_choice(void) {
	bool isValid = false;
	int choice;

	while (!isValid) {
		printf("Enter Choice:");
		printf("1] Edit Item Name, 2] Item Price\n");
		scanf("%d", &choice);
		FLUSH;

		if (choice == 1 || choice == 2) {
			isValid = true;
		} else {
			printf("Invalid Choice\n");
		}
	}

	return choice;
}

void edit_item(I_Next hash_inv[], char search_key[]) {
	bool found = false;
	int index = hash_trunc(key_cast(search_key));
	nd_i ptr = hash_inv[index].next;

	while (ptr != NULL) {
		if (strcmp(ptr->data.item_number, search_key)) {
			int choice = edit_choice();

			if (choice == 1) {
				printf("Enter Item Name:");
				char new_name[20];
				gets(new_name);
				strcpy(ptr->data.item_name, new_name);
			} else if (choice == 2) {
				printf("Enter Price:");
				scanf("%f", &ptr->data.price);
				FLUSH;
			}

			found = true;
			break;
		} else {
			ptr = ptr->next;
		}
	}

	if (found) {
		printf("Successfully Edited\n");
	} else {
		printf("Item not found\n");
	}
}

void view_item(I_Next hash_inv[], char search_key[]) {
	bool found = false;
	int index = hash_trunc(key_cast(search_key));
	nd_i ptr = hash_inv[index].next;

	while (ptr != NULL) {
		if (strcmp(search_key, ptr->data.item_number)) {
			printf("\n%-15s %-15s %-8s %-10s\n","ITEM #", "ITEM NAME", "QTY", "PRICE");
			printf("%-15s %-15s %-8d %-10.2f\n", ptr->data.item_number, ptr->data.item_name, ptr->data.qty, ptr->data.price);
			found = true;
			break;
		} else {
			ptr = ptr->next;
		}
	}

	if (!found) {
		printf("Item not found\n");
	}
}

bool search_inventory(I_Next hash_inv[], char search_key[], int *search_index) {
	bool found = false;
	int index = hash_trunc(key_cast(search_key));
	int index2 = -1;

	while(index2 != index) {
		if (index2 == -1) {
			index2 = index;
		}
		if (hash_inv[index2].state == 'o' && strcmp(search_key, hash_inv[index2].item_number) == 0) {
			found = true;
			*search_index = index2;
			break;
		} else {
			index2 = double_hash(index2, key_cast(search_key));
		}
	}

	return found;
}

bool input_sale(SALE *data, ITEMS hash_inv[], int *index) {
	SALE record;

	printf("Enter Sales #:");
	gets(record.sales_number);

	printf("Enter Item Number:");
	gets(record.item_number);

	if (search_inventory(hash_inv, record.item_number, index)) {
		bool isValid = false;
		while (!isValid) {
			printf("Enter quantity:");
			scanf("%d", &record.s_qty);
			FLUSH;

			if (record.s_qty > hash_inv[*index].qty) {
				printf("Quantity on hand is insufficient\n");
			}
			else if (record.s_qty < 0) {
				printf("Quantity cannot be negative\n");
			}
			else if (record.s_qty >= 0) {
				hash_inv[*index].qty -= record.s_qty;
				isValid = true;
			}
			else {
				printf("Invalid Amount\n");
			}
		}
		record.state = 'o';
		*data = record;
	} else {
		printf("Item not found / doesn't exist\n");
		return false;
	}

	return true;
}

void sales(SALE hash_sale[], ITEMS hash_inv[]) {
	int search_index;
	SALE record;
	bool isValid = input_sale(&record, hash_inv, &search_index);

	if (isValid) {
		bool stored = false;
		int index , index2 = -1;

		index = hash_trunc(key_cast(record.sales_number));

		while(index2 != index) {
			if (index2 == -1) {
				index2 = index;
			}
			if((hash_sale[index2].state == 'e') ||(hash_sale[index2].state == 'd')){
				hash_sale[index2] = record;
				// hash_inv[search_index].qty -= record.s_qty;
				stored = true;
				break;
			} else {
				index2 = double_hash(index2, key_cast(record.sales_number));
			}
		}

		if (stored) {
			printf("Sale Added\n");
		} else {
			printf("Storage is full");
		}
	} else {
		printf("Error Adding Sale\n");
	}
}

bool input_goods(GOODS *data, ITEMS hash_inv[], int *index) {
	GOODS record;

	printf("Enter Goods #:");
	gets(record.goods_number);

	printf("Enter Item Number:");
	gets(record.item_number);

	if (search_inventory(hash_inv, record.item_number, index)) {
		bool isValid = false;
		while (!isValid) {
			printf("Enter quantity:");
			scanf("%d", &record.g_qty);
			FLUSH;

			if (record.g_qty < 0) {
				printf("Quantity cannot be negative\n");
			}
			else if (record.g_qty >= 0) {
				hash_inv[*index].qty += record.g_qty;
				isValid = true;
			}
			else {
				printf("Invalid Amount\n");
			}
		}
		record.state = 'e';
		*data = record;
	} else {
		printf("Item not found / doesn't exist\n");
		return false;
	}

	return true;
}

void goods(GOODS hash_goods[], ITEMS hash_inv[]) {
	int search_index;
	GOODS record;
	bool isValid = input_goods(&record, hash_inv, &search_index);

	bool stored = false;
	int index , index2 = -1;

	index = hash_trunc(key_cast(record.goods_number));
	if (isValid) {
		while(index2 != index) {
			if (index2 == -1) {
				index2 = index;
			}
			if((hash_goods[index2].state == 'e') ||(hash_goods[index2].state == 'd')){
				hash_goods[index2] = record;
				// hash_inv[search_index].qty += record.g_qty;
				stored = true;
				break;
			} else {
				index2 = double_hash(index2, key_cast(record.goods_number));
			}
		}

		if (stored) {
			printf("Goods Receipt Added\n");
		} else {
			printf("Storage is full");
		}
	}
	else {
		printf("Error Adding Receipt!\n");
	}
}

void Display_All(ITEMS hash_inv[]) {
	printf("\n%-5s %-15s %-15s %-8s %-10s %-6s\n",
		   "i", "ITEM #", "ITEM NAME", "QTY", "PRICE", "STATE");
	printf("-------------------------------------------------------------\n");

	for (int i = 0; i < B_CAP; i++) {
		printf("%-5d %-15s %-15s %-8d %-10.2f %-6c\n",
			   i+1,
			   hash_inv[i].item_number,
			   hash_inv[i].item_name,
			   hash_inv[i].qty,
			   hash_inv[i].price,
			   hash_inv[i].state);
	}
}

void Display_Sale(SALE hash_sale[]) {
	printf("\n%-5s %-15s %-15s %-10s %-6s\n",
			"i", "SALES #", "ITEM #", "SOLD QTY", "STATE");
	printf("-----------------------------------------------------\n");

	for (int i = 0; i < B_CAP; i++) {
		printf("%-5d %-15s %-15s %-10d %-6c\n",
			   i+1,
			   hash_sale[i].sales_number,
			   hash_sale[i].item_number,
			   hash_sale[i].s_qty,
			   hash_sale[i].state);
	}
}

void Display_Goods(GOODS hash_goods[]) {
	printf("\n%-5s %-15s %-15s %-10s %-6s\n",
			"i", "SALES #", "ITEM #", "REC. QTY", "STATE");
	printf("-----------------------------------------------------\n");

	for (int i = 0; i < B_CAP; i++) {
		printf("%-5d %-15s %-15s %-10d %-6c\n",
			   i+1,
			   hash_goods[i].goods_number,
			   hash_goods[i].item_number,
			   hash_goods[i].g_qty,
			   hash_goods[i].state);
	}
}

void menu() {
	printf("Macalua Enterprise\n");
	printf("1] Add New Item\n");
	printf("2] Edit Item Information\n");
	printf("3] View Specific Item\n");
	printf("4] Sales\n");
	printf("5] Goods Receipt\n");
	printf("6] Display Sales\n");
	printf("7] Display Goods Receipt\n");
	printf("8] Display All Items\n");
	printf("9] Exit\n");
}

int main() {
	I_Next hmap_inventory[B_CAP];
	S_NEXT hmap_sales[B_CAP];
	G_NEXT hmap_goods[B_CAP];

	init_hmaps(hmap_inventory, hmap_sales, hmap_goods);

	bool isRepeating = true;

	while (isRepeating) {
		int choice;
		menu();
		printf("Input:\n");
		scanf("%d", &choice);
		FLUSH;
		switch (choice) {
			case 1: {
				ITEMS data = input();
				add_inventory(hmap_inventory, data);
			}
				break;
			case 2: {
				char search_string[30];
				printf("Enter Item Number:\n");
				gets(search_string);
				edit_item(hmap_inventory, search_string);
			}
				break;
			case 3:{
				char search_string[30];
				printf("Enter Item Number:\n");
				gets(search_string);
				view_item(hmap_inventory, search_string);
			}
				break;
			case 4:
				sales(hmap_sales, hmap_inventory);
				break;
			case 5:
				goods(hmap_goods, hmap_inventory);
				break;
			case 6:
				Display_Sale(hmap_sales);
				break;
			case 7:
				Display_Goods(hmap_goods);
				break;
			case 8:
				Display_All(hmap_inventory);
				break;
			case 9:
				exit(0);
		}
		printf("\nPress Any Button to continue\n");
		getchar();
	}
}

