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

		if (a[i] == a[size_num - (i + 1)]) { //  loop through the array comparing letters starting from head and tail
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

	//printf("Controls:  ");

	for (int i = 0; i < size; i++) {
		//printf("%c     ", c[i]);			// print out the character commands
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
		if (*p_p != (a + size_num - 1)) { // do not allow  to point outside the array
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
		if (**p_p > 0) { //// ensure that  0 is the minimum for each element
			**p_p = **p_p - 1;
			*p_nm = *p_nm + 1;
		}
		else {
			printf("\n0 is minimum number. Try again!!!\n---------------------------------------");
		}
		break;
	default:
		printf("Invalid command try again\n"); // an invalid command was recieved, give an error message
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
}

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------
void user_game_palindrome(int pal_num, int num_size, char commands[], int command_size, char* solution, int solution_size) {
	int* arr = (int*)malloc(num_size * sizeof(int));

	//char str[sizeof(arr)];
	char* str = (char*)malloc(num_size * sizeof(char));

	sprintf(str, "%d", pal_num);	// convert the int recieved to a string so I can seperate each digit 1 by 1 into array

	for (int i = 0; i < num_size; i++) {

		arr[i] = str[i] - '0';	// convert char to int, without the - '0' it will print the ascii representation
	}

	int* p = arr;	// pointer to array
	int** p_p = &p; // pointer to pointer 
	int pnm = 0; // number of moves
	int* p_pnm = &pnm;

	printf("Lets get started..\n");
	
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

		for (int i = 0; i < solution_size; i++) {
			printf("\nPress the %c key", solution[i]); // tell the user which key to press

				letter = ask_for_command(commands, command_size);
				if (letter == solution[i]) {			// if they press the correct key
					process_movement(arr, num_size, p_p, p_pnm, letter); // must feed in arr not p
					print_status(arr, num_size, p, pnm);

				}
				else {
					printf("\n-------------- Wrong letter Ted ------------------\n");	// wrong letter was pressed
					i--;		// WRONG LETTER RECIEVED SO DO NOT ALLOW i TO INCREMENT
				}
		}	
	}
	printf("\n|-------------\t\tThis number is a palindrome!!!\t\t-----------|");

}

//--------------------------------------------------
// get_solving_array
//--------------------------------------------------
char* get_solving_array(int* arr, int size_num, int* p, int* total_movs) {

	char* res = (char*)malloc(*total_movs +1* sizeof(char));
	
	int cnt = 0;
	int temp = 0;
	for (int i = 0; i < size_num / 2; i++) {
		if (arr[i] != arr[size_num - (i + 1)]) {		 // if the 2 numbers do not match

			temp = 0;

			if (arr[i] > arr[size_num - (i + 1)]) {		 // if the number on the left half of the arrray is greater than the number its being compared with in the right half
				temp = arr[i] - arr[size_num - (i + 1)]; // calcualte number of moves needed to increment a number
				
				for (int x = cnt; x < (cnt + temp); x++) {
					res[x] = 'x';
					res[cnt + temp] = 'd';	
				}
				cnt++; // I USE CNT KEEP TRACK OF WHERE I AM
			}
			
			else {											// NUMBER ON THE LEFT IS LESS THAN NUMBER ON RIGHT SIDE								 
				
				temp = arr[size_num - (i + 1)] - arr[i];  // calculate how many moves this element needs to move				
				for (int m = cnt; m < (cnt + temp); m++) { 
					res[m] = 'w';
					res[cnt + temp] = 'd';
				}
				cnt++;
			}
		}
		else {
			res[cnt + temp] = 'd';
		}

		cnt += temp;
	}

	printf("Minimum number of moves this will take is %d\n", *total_movs);
	printf("\n");
	printf("This game can be completed efficiently by doing the following commands in order:\n");
	printf("\n");

	for (int n = 0; n < *total_movs; n++) {
		printf("%c, ", res[n]);
	}
	printf("\n----------------------------------------------------------------------------------");
	printf("\n");

	return res;
}

//--------------------------------------------------
// machine_game_palindrome
//--------------------------------------------------
void machine_game_palindrome(int pal_num, int num_size, char* commands, int commands_size) {

	int* arr = (int*)malloc(num_size * sizeof(int));

	char str[sizeof(arr)];

	sprintf(str, "%d", pal_num);	// convert the int recieved to a string so I can seperate each digit 1 by 1 into array

	for (int i = 0; i < num_size; i++) {

		arr[i] = str[i] - '0';	// convert char to int, without the - '0' it will print the ascii representation
	}

	int temp = 0;	// temp will be used to calulate number moves each element will need to match the opposite number
	int totalMoves = 0; // this is the total, minimum amount of moves it will take to win the game
	int additionalMove = 0; // id numbers are the same this will just increment by 1, which will be one 'd' movement
	
	// ----------- test[ 0, 0, 0, 0] will represent  w x d a.. so each int element will increment when its corresponding letter is needed 
			//      w  x  d  a
	int  test[4] = {0, 0, 0, 0};
	// -------------------------------------------------------------------------------------------------------

	int palin = is_pal(arr, num_size);		// first check if the number given is already an palindrome
	if (palin == 1) {
		printf("This puzzle requires 0 moves. It is already a palindrome\n");

	}
	else {													 // else it is not a palindrome
		for (int i = 0; i < num_size / 2; i++) {			 // stop the loop when we reach the midpoint of the array
			temp = 0;										 // reset temp because we are now testing new  a element of the array over and over
			if (arr[i] != arr[num_size - (i + 1)]) {		 // if the 2 numbers do not match

				if (arr[i] > arr[num_size - (i + 1)]) {		 // if the number on the left half of the arrray is greater than the number its being compared with in the right half
					temp = arr[i] - arr[num_size - (i + 1)]; // calcualte number of moves needed to increment a number
					test[1] += temp; // set x move count
					
				}
				else {										 // else the number in the right half is bigger
					temp = arr[num_size - (i + 1)] - arr[i]; // calcualte number of moves needed to decrement a number
					test[0] += temp; // set letter w move count
				}
				
				totalMoves += temp; 
				totalMoves++;								 // add one move to iterate to the right
				test[2]++; // set d move count
			}
			else {											 // two numbers are already the same so dont need to increment/decrement
				additionalMove++;							 // increment an additional counter which count as 1 move to the right
				//test[i] = additionalMove;
			}
			
		} // end of for loop
		
		// if some numbers are the same and we do not need to go any further to the right then dont count the extra moves
		for (int i = 0; i < num_size / 2; i++) {
	
				if (arr[i] == arr[num_size - (i + 1)]) {		 // if the 2 numbers do not match
				totalMoves--;
			}
		}
	
		totalMoves += -1; // for loop was moving one extra step to the middle number, which does not count as a move. therefore decrement by one
		totalMoves += additionalMove; 
		int* tm = &totalMoves; // pointer to totalMoves

		int* t = test;

		test[2]--; // NEED TO DECREMENT D MOVEMENT BY 1 CAUSE OF LAST MOVE TO THE RIGHT IS NOT NEEDED
		
		// t is a pointer to test[]
		char* res =  get_solving_array(arr, num_size, t, tm); // get the array storing which characters to press
		user_game_palindrome(pal_num, num_size, commands, commands_size, res, totalMoves);

	}
}
// final version


