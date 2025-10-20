# Option 1
Literally just adding each index, works for letters and numbers based on their ASCII code.

```c
int option1(char num[]) {
	int length = strlen(num);
	int key = 0;

    // traverse through the length and compound +=
	for (int i = 0; i < length; i++) {
		key += num[i];
	}

	return key;
}
```

# Option 2
Taking the last or first 3 letters, or whatever amount of numbers. You add it all but multiply each to 27^i. Start with the First letter + Second multipled by 27 + Third multiplied by 27^2.

```c
int option2_firstletter(char num[]) {
	int key = 0;
	key = num[0] + (27 * num[1]) + ((int)pow(27, 2) * num[2]);
	return key;
}
```

To take the last 3 digits, or whatever amount. Extract the length, first letter is length - 3 then length - 2, then lastly length - 1. As C is 0-index based.
```c
int option2_lastletter(char num[]) {
	int key = 0;
	int L = strlen(num);
	key = num[L - 3] + (27 * num[L - 2]) + ((int)pow(27, 2) * num[L-1]);
	return key;
}
```

# Option 3
idk how to explain this. Just memorize it chat

```c

```
