#define _CRT_SECURE_NO_WARNINGS // need this to use sprint


//--------------------------------------------------
// INCLUDE SECTION
//--------------------------------------------------
#include "pal.h"

//--------------------------------------------------
// is_pal
//--------------------------------------------------
boolean is_pal(int* a, int size_num) {
	boolean res = 0;

	for (int i = 0; i < size_num / 2; i++) {  // I use size /2 becuase we stop coamparing when we get to the middle of the array

		if (a[i] == a[size_num - (i + 1)]) { //  loop through the array comparing letters from head and tail
			res = 1;  // return 1 if a palindrome is found
		}
		else {
			res = 0;	// return 0 if a palindrome is not found
			break;
		}

	}
	return res;
}

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------
char ask_for_command(char c[], int size) {
	char res = ' ';

	printf("Controls:  ");

	for (int i = 0; i < size; i++) {
		printf("%c     ", c[i]);			// print out the character commands
	}
	//printf("\nPress b to exit\n---------------------------------\n");
	res = my_get_char();

	return res;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------
void process_movement(int* a, int size_num, int** p_p, int* p_nm, char c) {
	
	switch (c) {
	case 'a':
		if (*p_p != (a + 0)) {		// do not allow to point outside the array 
			*p_p = (*p_p - 1);
			*p_nm = *p_nm + 1;
		}
		break;
	case 'd':
		if (*p_p != (a + size_num -1)) { // do not allow  to point outside the array
			*p_p = (*p_p + 1);
			*p_nm = *p_nm + 1;
		}
		break;
	case 'w':
		if (**p_p < 9) {		// ensure that 9 is the maximimum for each element
			**p_p = **p_p + 1;
			*p_nm = *p_nm + 1;
		}
		else {
			printf("\n9 is max number. Try Again!!!");
		}
		break;
	case 'x':
		if (**p_p > 0) { //// ensure that  is the minimum for each element
			**p_p = **p_p - 1;
			*p_nm = *p_nm + 1;
		}
		else {
			printf("\n0 is minimum number. Try again!!!\n---------------------------------------");
		}
		break;
	case 'h':		// move the pointer to the last element
		if(*p_p != &a[0]) {
			*p_p = &a[0];
			*p_nm = *p_nm + 1;
		}
		break;

	case 'k':		// move the pointer the last element
		if (*p_p != &a[size_num - 1]) {
			*p_p = &a[size_num - 1];
			*p_nm = *p_nm + 1;

		}
		break;
	case 'u':
		if (**p_p != 9) { // turn the current digit to a 9 (unless it is already 9)
			**p_p = 9;
			*p_nm = *p_nm + 1;
		}
		break;
	case 'm':
		if (**p_p != 0) {	 // turn the current digit to a 0 (unless it is already 0)
			**p_p = 0;
			*p_nm = *p_nm + 1;
		}
		break;
	default:
		printf("Invalid command try again\n"); // an invalid command was recieved give error
	}
}

//--------------------------------------------------
// print_status
//--------------------------------------------------
void print_status(int* a, int size_num, int* p, int num_mov) {

	printf("\n-----------------\tGame Status\t--------------------");
	printf("\n     \t\t    {");
	for (int x = 0; x < size_num; x++) {
		//printf("%d,", *(p + x));
		printf("%d,", a[x]);

	}
	printf("}");
	printf("\n");

	for (int n = 0; n < size_num; n++) {
		if (p == (a + n)) {

			int temp = 0;

			printf("            \t     ");
			while (temp < (0 + n)) {
				printf("  ");
				temp++;
			}
		}

	}	printf("^");


	printf("\nNumber of moves: %d\n", num_mov);
	//printf("------------------");
}

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------
void user_game_palindrome(int pal_num, int num_size, char commands[], int command_size) {

	int* arr = (int*)malloc(num_size * sizeof(int));

	char* str = (char*)malloc(num_size * sizeof(char));

	sprintf(str, "%d", pal_num);// convert the int recieved to a string so I can seperate each digit 1 by 1 into array

	for (int i = 0; i < num_size; i++) {
		
		arr[i] = str[i] - '0'; // convert char to int, without the - '0' it will print the ascii representation

	}
	int* p = arr;	// pointer to array
	int** p_p = &p; // pointer to pointer 
	int pnm = 0; // number of moves
	int* p_pnm = &pnm;

	int palin;
	palin = is_pal(arr, num_size);	// returns 1 if palindrome. returns 0 if not

	while (palin == 0) { // while it is not  a palindrome keep the game running..
		palin = is_pal(arr, num_size);
		if (palin == 1) {
			printf("\n|------------\t\tCongratulations you won!!\t\t-----------|");
			print_status(arr, num_size, p, pnm);
			break; // game is won stop playing
		}
		print_status(arr, num_size, p, pnm);
		char letter;
		letter = ask_for_command(commands, command_size);
		process_movement(arr, num_size, p_p, p_pnm, letter); // must feed in arr not p

	}
		printf("\n|-------------\t\tThis number is a palindrome!!!\t\t-----------|");
}

// final version

