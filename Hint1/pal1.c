#define _CRT_SECURE_NO_WARNINGS
#include "pal.h"

int arr[6]; // int array to store each digit individually
static const int temp = &arr[0];


//--------------------------------------------------
// is_pal
//--------------------------------------------------
boolean is_pal(int a[6], int size) {  // test if the number is a palindrome
	int res = 0;

	for (int i = 0; i < size / 2; i++) {  // I use size / 2 becuase we stop coamparing when we get to the middle of the array

		if (a[i] == a[size - (i + 1)]) { //  loop through the array comparing letters from head and tail

			res = 1;  // return 1 if a palindrome is found
			//break;
			//return res;
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
char ask_for_command() {
	
	char res = ' ';
	printf("\nPress   A   D   W   X   to move"); 
	printf("\nPress b to exit\n---------------------------------\n\n");
	res = my_get_char();
	return res;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------
void process_movement(int a[6], int** p_p, int* p_nm, char c) {

	if(c == 'a' || c == 'A') {  // move left{

		if (*p_p != (a + 0))  //if we reach the last element of the array do not allow a move to the left
		{
			*p_p = (*p_p - 1);

		}
		else {
			printf("Cannot move left");
			*p_nm = *p_nm - 1; // nummoves increment when this method is called, but this failed so decrement moves by 1
		}
	}
	else if (c == 'd' || c == 'D') { // move right{

		if (*p_p != (a + 5)) {	// if we reach the last element of the array do not allow a move to the right
			*p_p = (*p_p + 1);
			printf("THE location is now OF *P_P IS %p\n", *&p_p);

		}
		else {
			printf("\nError: Cannot move right");
			*p_nm = *p_nm - 1; // nummoves increment when this method is called, but this failed so decrement moves by 1

		}
	}

	else if (c == 'w' || c == 'W') { // increase by 1{
		if (**p_p < 9) {		// ensure that 9 is the maximimum for each element
			**p_p = **p_p + 1;
		}
		else {
			printf("\n9 is max number. Try Again!!!");
			*p_nm = *p_nm - 1; // do not allow num of moves to increment

		}
	}
	else if (c == 'x' || c == 'X') { // decrease by 1 {

		if (**p_p > 0) { //// ensure that  is the minimum for each element

			**p_p = **p_p - 1;
		}
		else {
			printf("\n0 is minimum number. Try again!!!\n---------------------------------------");
			*p_nm = *p_nm - 1; // do not allow num of moves to increment

		}
	}
	else if (c == 'b' || c == 'B') { // decrease by 1 {
		
		printf("Exiting..");
		
	}
	else {   // if an invalid letter is recieded give an error..
		printf("Not a valid command. Try again !!");
		*p_nm = *p_nm - 1; // do not allow num of moves to increment
		
	}

}

//--------------------------------------------------
// print_status
//--------------------------------------------------
void print_status(int a[6], int* p, int nm) {
	
	printf("\n-------Game Status---------------");
	printf("\n    {");
	for (int x = 0; x < 6; x++) {
		printf("%d,",a[x]);

	}
	printf("}");
	
	// ------------- now make the arrow move..
	printf("\n");
	for (int n = 0; n < 6; n++) {
			if (p == (a + n)) {

			int temp = 0;
			printf("     ");
			while (temp < (0 + n)){
				printf("  ");
				temp++;
			}
		}

	}	printf("^");


	printf("\nNumber of moves: %d\n", nm);

}

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------
void user_game_palindrome(int pal_num) {

	int arr[6]; // int array to store each digit individually
	int i; // for the loop 
	char* str = (char*)malloc(6 * sizeof(char));

	sprintf(str, "%d", pal_num);// convert the int recieved to a string so I can seperate each digit 1 by 1 into array

	for (i = 0; i < 6; i++) {

		arr[i] = str[i] - '0'; // convert char to int, without the - '0' it will print the ascii representation
	}

	char letter;
	int* p = &arr;
	int** p_p = &p;

	int pnm = -1; // start number of moves at -1 because it changes to 0 when the game starts
	int* p_nm = &pnm;		// pointer to number of moves

	int size = sizeof(arr) / sizeof(arr[0]);	// get the size of the array so it can be used as paramter for certain functions
	int palin;
	palin = is_pal(arr, size);	// if returns 1 then its a palindrome. else its not

	while (palin == 0) { // while it is not  a palindrome keep the game running..
						 //res = 0;
		pnm++;	// increment number of moves
		palin = is_pal(arr, size);
		if (palin == 1) {
			printf("\n----Palindrome found you won!!----\n----------------------------------");
			print_status(arr, p, pnm);
			break; // game is won stop playing
		}
		print_status(arr, p, pnm);
		letter = ask_for_command();
		//scanf("%c"); // hoover up the newline character
		process_movement(arr, p_p, p_nm, letter);
		if (letter == 'b') {
			palin = 1;
			//printf("\nExiting..");

		}
	}

}
// final version
