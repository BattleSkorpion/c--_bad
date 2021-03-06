/*************************************/
/* INFORMATION SECTION               */
/* DARIAN SIEMBAB                    */
/* October 24, 2021               	 */
/* Chapter 13 - Stacks 				 	 */
/* Program 2   						 	 */
/*************************************/

/*************************************/
/* PROGRAM DESCRIPTION SECTION       */
/* THIS PROGRAM WILL MAINTAIN HOTEL  */
/* RESERVATIONS IN A LINKED LIST     */
/*************************************/

/*******************/
/* INCLUDE SECTION */
/*******************/
#include <apstring.cpp>      // USED FOR apstring CLASS
#include <apvector.h>        // apvector CLASS
#include <conio.h>			  // USED FOR getch()                                                                       
#include <iocolors.h>		  // USED FOR makeWindows CLASS
#include <iostream.h>		  // BASIC INPUT & OUTPUT

/*********************/
/* STRUCTURE SECTION */
/*********************/
struct digit_node
{
	short int digit; 
	digit_node *next_ptr;
};

///// PROTOTYPES /////

void delete_stack(digit_node *head_ptr);
// PROTOTYPE - DELETES STACK

void display_stack(digit_node *head_ptr);
// PROTOTYPE - DISPLAYS THE STACK

void display_stacks(digit_node *digit1_head_ptr, digit_node *digit2_head_ptr,
		digit_node *results_head_ptr);
// PROTOTYPE - DISPLAYS STACKS VALUES BY DISPLAYING EACH STACK

digit_node* push(digit_node *head_ptr, digit_node *new_node_ptr);
// PROTOTYPE - PUSHES TO STACK

digit_node* pop(digit_node *head_ptr);
// PROTOTYPE - POPS FROM STACK

void inputAPstring (apstring &str, apstring prmpt);
// PROTOTYPE - INPUTS AND APSTRING

void inputChar (char &ans, char c1, char c2, apstring prmpt, apstring err);
// PROTOTYPE - INPUTS A CHARACTER

void inputChar (char &ans, char c1, char c2, char c3, apstring prmpt,
apstring err);
// PROTOTYPE - INPUTS A CHARACTER (3 CHARACTER OPTIONS)

void inputAnyInt (short int &num, apstring prmpt); 
// PROTOTYPE - INPUTS ANY INTEGER

void inputInt (int &num, apstring prmpt, apstring err);
// PROTOTYPE - INPUTS AN INTEGER

void printErrorMessage (apstring err);
// PROTOTYPE - PRINTS ERROR MESSAGE

void programDescription();
// PROTOTYPE - PRINTS PROGRAM DESCRIPTION

int printMenu();
// PROTOTYPE - PRINTS PROGRAM MENU

void windowHeading(int nm);
// PROTOTYPE - PRINTS WINDOW HEADING

/*****************/
/* ERROR SECTION */
/*****************/
const apstring ERROR1 = "ANSWER must be Y, y, N, or n!";
const apstring ERROR3 = "ERROR: Value must be POSITIVE!";
const apstring ERROR5 = "Error: Must input a digit!";
const apstring ERROR6 = "Error: Stack empty.";
const apstring ERROR10 = "Error: Out of MEMORY error or other error! Program will terminate!";

/******************/
/* PROMPT SECTION */
/******************/
const apstring PROMPT1 = "Input run program again (Y, y, N, n): ";
const apstring PROMPT2 = "INPUT must be from 1-4";
const apstring PROMPT3 = "Input number of digits to add together: ";
const apstring PROMPT4 = "Input value: ";

void main ()
{
	/********************/
   /* VARIABLE SECTION */
   /********************/
   digit_node *digits1_head_ptr = NULL;     // DIGITS STACK 1
   digit_node *digits2_head_ptr = NULL;     // DIGITS STACK 2
   digit_node *digits3_head_ptr = NULL;     // DIGITS SUM OF DIGITS STACK 1 AND 2
   digit_node *digit_ptr;            		  // NODE TO PUSH ONTO STACK
   int inputCount;
   short int temp_int;
   short int total;
	bool carry;
   char runProgram;				  				  // RUN PROGRAM OPTIONS: Y, y, N, n
   int menuOption;              				  // MENU SELECTION OPTIONS

   /********************************/
   /* FUNCTION PROGRAM DESCRIPTION */
   /********************************/
   programDescription();

   /*******************************************/
   /* MAIN LOOP TO RUN PROGRAM MORE THAN ONCE */
   /*******************************************/
   do
   {
      /************************************/
      /* INPUT NUMBER OF NUMBERS TO INPUT */
      /************************************/
      inputInt(inputCount, PROMPT3, ERROR3);

      /****************************/
      /* INPUT VALUES INTO STACKS */
      /****************************/
		for(int i = 0; i < inputCount; i++)
      {
      	digit_ptr = new digit_node;
         digit_ptr->digit = -100;
         while(digit_ptr->digit >= 10 || digit_ptr->digit <= -10)
         {
      		inputAnyInt(digit_ptr->digit, PROMPT4);
            if (digit_ptr->digit >= 10 || digit_ptr->digit <= -10)
            {
            	printErrorMessage(ERROR5);
            }
         }
         digits1_head_ptr = push(digits1_head_ptr, digit_ptr);
         digit_ptr = new digit_node;
         digit_ptr->digit = -100;
         while(digit_ptr->digit >= 10 || digit_ptr->digit <= -10)
         {
      		inputAnyInt(digit_ptr->digit, PROMPT4);
            if (digit_ptr->digit >= 10 || digit_ptr->digit <= -10)
            {
            	printErrorMessage(ERROR5);
            }
         }
         digits2_head_ptr = push(digits2_head_ptr, digit_ptr);
      }

      cout << pop(digits1_head_ptr);      // TODO: why null!
      cin.get();

		/***********************************/
		/* SUM DIGITS1 AND DIGITS2 STACKS  */
		/* (PUSH RESULTS TO DIGITS3 STACK) */
		/***********************************/
		carry = 0; 			// initialize / reset value of carry to 0
		for (int i = 0; i < inputCount; i++)
		{
			total = pop(digits1_head_ptr)->digit + pop(digits2_head_ptr)->digit + carry;

			/**********************/
			/* CARRY IF NECESSARY */
			/**********************/
			if (total >= 10)
			{
				carry = 1;
				digit_ptr = new digit_node;
				digit_ptr->digit = total % 10; 	// use "units' digit of the sum"
															// (ones' place)
				push(digits3_head_ptr, 				// push value onto results stack
					digit_ptr);							// (digits3 stack)
			} 
			else
			{
				carry = 0;
				digit_ptr = new digit_node;
				digit_ptr->digit = total; 			// total will be < 10
				push(digits3_head_ptr, 				// push value onto results stack
					digit_ptr);							// (digits3 stack)
			}
		}

      /****************/
      /* PRINT STACKS */
      /****************/
      display_stacks(digits1_head_ptr, digits2_head_ptr, digits3_head_ptr); 

		/*************************************************/
		/* FUNCTION TO INPUT ANSWER TO RUN PROGRAM AGAIN */
		/*************************************************/
		inputChar (runProgram, 'y', 'n', PROMPT1, ERROR1);

      cin.ignore (80,'\n');
   }
   while ((runProgram == 'y') || (runProgram == 'Y'));
}

/*****************************************************************************/
/*										  FUNCTION SECTION                             */
/*****************************************************************************/

void delete_stack(digit_node *head_ptr)
/************************************************************/
/* PRECONDITION:  ENTIRE STACK MUST BE DELETED              */
/* POSTCONDITION: STACK IS DELETED, MEMORY RETURNED TO HEAP */
/************************************************************/
{
 	do
  	{
   	pop(head_ptr);     // Pop items until stack is empty.
  	}
   while(head_ptr != NULL);
}

void display_stack(digit_node *head_ptr)
/*******************************************************/
/* PRECONDITION:  NEEDS TO DISPLAY STACK (AS A NUMBER) */
/* POSTCONDITION: DISPLAYS STACK								 */
/*******************************************************/
{
	digit_node *current_ptr = head_ptr;	   // SET CURRENT POINTER
														// TO HEAD OF LIST

   /*************************************************************/
   /* IF LIST IS NOT EMPTY PRINT OUT EACH NODE TO FORM A NUMBER */
   /*************************************************************/
   while(current_ptr != NULL)
   {
   	current_ptr = pop(current_ptr);
      cout << current_ptr->digit;
   }
   /***********************************************/
   /* ELSE IF LIST IS EMPTY DISPLAY ERROR MESSAGE */
   /***********************************************/
   if (current_ptr == NULL)
   {       
   	printErrorMessage(ERROR6);
   }
}

void display_stacks(digit_node *digit1_head_ptr, digit_node *digit2_head_ptr,
	  digit_node *results_head_ptr)
/*****************************************************/
/* PRECONDITION:  NEEDS TO DISPLAY STACKS FOR OUTPUT */
/* POSTCONDITION: DISPLAYS STACKS (AS NUMBERS)		  */
/*****************************************************/
{
	makeWindows (15, 10, 65, 23, BLACK);
   gotoxy(3, 3);
   txtcolor(WHITE);
   
	cout << "First number: " << endl;
	display_stack(digit1_head_ptr);
   cout << endl;
   cout << "Second number: " << endl;
   display_stack(digit2_head_ptr);
   cout << endl;
   cout << "Result: " << endl; 
   display_stack(results_head_ptr);
}

digit_node* push(digit_node *head_ptr, digit_node *new_node_ptr)
/**********************************************************/
/* PRECONDITION:  USER WANTS TO PUSH AN ITEM ON THE STACK */
/* POSTCONDITION: PUSHES AN ITEM ON THE STACK				 */
/**********************************************************/
{
	/****************************************/
   /* IF STACK IS EMPTY THEN MAKE NEW NODE */
   /* THE FIRST ITEM ON THE STACK 			 */
   /****************************************/
	if(head_ptr == NULL)
   {
   	new_node_ptr->next_ptr = NULL;
      head_ptr = new_node_ptr;
   }

   /*******************************/
   /* ELSE STACK IS NOT EMPTY, SO */
   /* PUSH THE NODE ON THE STACK  */
	/*******************************/
   else
   {
   	new_node_ptr->next_ptr = head_ptr;
      head_ptr = new_node_ptr;
   }
   return head_ptr;
}

//TODO: FIXXXXXXXXXXXX
digit_node* pop(digit_node *head_ptr)
/******************************************************/
/* PRECONDITION:  USER WANTS TO POP ITEM OFF OF STACK */
/* POSTCONDITION: ITEM IS POPPED OFF OF STACK 			*/
/******************************************************/
{
	digit_node *temp_ptr;

   /***********************************************************/
   /* IF STACK IS NOT EMPTY (NULL) THEN POP ITEM OFF OF STACK */
   /***********************************************************/
   if (head_ptr != NULL)
   {
   	temp_ptr = head_ptr->next_ptr; 	// SET TEMP POINTER TO NEXT NODE
      delete head_ptr;                 // DELETE FORMER TOP NODE
      head_ptr = temp_ptr;             // MOVE HEAD POINTER TO NEW TOP OF STACK
   }
   return head_ptr;
}

void inputAPstring(apstring &str, apstring prmpt)
/******************************************/
/* PRECONDITION: USER NEEDS AN APSTRING   */
/* POSTCONDITION: USER INPUTS AN APSTRING */
/******************************************/
{
	makeWindows (15, 10, 65, 17, BLUE, LIGHTGREEN, BLUE);
   gotoxy (5, 5);
   cout << prmpt;
   txtcolor (YELLOW);
   getline (cin, str);
   txtcolor (WHITE);
}

void inputChar(char &ans, char c1, char c2, apstring prmpt, apstring err)
/*******************************************************/
/* PRECONDITION: USER NEEDS A CHARACTER                */
/* POSTCONDITION: READS IN A CHARACTER AND LOOPS UNTIL */
/* 					THE CORRECT CHARACTER IS INPUTTED    */
/*******************************************************/
{
	do
   {
   	makeWindows (15, 10, 65, 23, GREEN);
   	gotoxy (10, 6);
   	txtcolor (RED);
   	cout << err;
   	txtcolor (WHITE);

      if (prmpt.length() >= 40)
   	// IF THE LENGTH OF THE PROMPT IS TOO LONG, SPLITS THE PROMPT BETWEEN TWO
   	// LINES
   	{
      	gotoxy (5, 3);
      	cout << prmpt.substr (0, 40);

      	gotoxy (5, 4);
      	cout << prmpt.substr (40, 40);
   	}
   	else
   	// ELSE, PRINTS THE PROMPT REGULARLY
   	{
      	gotoxy (5, 4);
      	cout << prmpt;
   	}

      gotoxy (5, 6);
   	txtcolor (YELLOW);
   	cin >> ans;
   	txtcolor (WHITE);

      /*******************************************/
      /* FUNCTION TO ERROR CHECK VALID CHARACTER */
      /*******************************************/
      if ((ans != toupper (c1)) && (ans != c1) &&
      	 (ans != toupper (c2)) && (ans != c2))
      {
      	printErrorMessage (err);
      }
   }
   while ((ans != toupper (c1)) && (ans != c1) &&
      	 (ans != toupper (c2)) && (ans != c2));
}

void inputChar(char &ans, char c1, char c2, char c3, apstring prmpt,
apstring err)
/*******************************************************/
/* PRECONDITION: USER NEEDS A CHARACTER                */
/* POSTCONDITION: READS IN A CHARACTER AND LOOPS UNTIL */
/* 					THE CORRECT CHARACTER IS INPUTTED    */
/*******************************************************/
// THIS INPUT CHAR FUNCTION ACCEPTS 3 CHARACTER OPTIONS INSTEAD OF 2
{
	do
   {
   	makeWindows (15, 10, 65, 23, GREEN);
   	gotoxy (10, 6);
   	txtcolor (RED);
   	cout << err;
   	txtcolor (WHITE);

      if (prmpt.length() >= 40)
   	// IF THE LENGTH OF THE PROMPT IS TOO LONG, SPLITS THE PROMPT BETWEEN TWO
   	// LINES
   	{
      	gotoxy (5, 3);
      	cout << prmpt.substr (0, 40);

      	gotoxy (5, 4);
      	cout << prmpt.substr (40, 40);
   	}
   	else
   	// ELSE, PRINTS THE PROMPT REGULARLY
   	{
      	gotoxy (5, 4);
      	cout << prmpt;
   	}

      gotoxy (5, 6);
   	txtcolor (YELLOW);
   	cin >> ans;
   	txtcolor (WHITE);

      /*******************************************/
      /* FUNCTION TO ERROR CHECK VALID CHARACTER */
      /*******************************************/
      if ((ans != toupper (c1)) && (ans != c1) &&
      	 (ans != toupper (c2)) && (ans != c2) &&
          (ans != toupper (c3)) && (ans != c3))
      {
      	printErrorMessage (err);
      }
   }
   while ((ans != toupper (c1)) && (ans != c1) &&
      	 (ans != toupper (c2)) && (ans != c2) &&
          (ans != toupper (c3)) && (ans != c3));
}

void inputInt (int &num, apstring prmpt, apstring err)
/*************************************************************/
/* PRECONDITION: PROGRAM NEEDS A (POSITIVE) INT VALUE   	    */
/* POSTCONDITION: PROMPTS USER FOR AN INTEGER VALUE TO INPUT */
/* 					LOOPS UNTIL CORRECT VALUE IS INPUTTED      */
/*************************************************************/
{
	bool failed;

	do
   {
   	failed = false;
   	makeWindows (15, 10, 65, 23, GREEN);
   	gotoxy (8, 10);
   	txtcolor (RED);
   	cout << err;
   	txtcolor (WHITE);

      if (prmpt.length() >= 40)
      // IF THE LENGTH OF THE PROMPT IS TOO LONG, SPLITS THE PROMPT BETWEEN TWO
      // LINES
      {
      	gotoxy (5, 3);
         cout << prmpt.substr (0, 40);

         gotoxy (5, 5);
         cout << prmpt.substr (40, 40);

         gotoxy (5, 7);
      }
      else
      // ELSE, PRINTS THE PROMPT REGULARLY
      {
   		gotoxy (5, 4);
   		cout << prmpt;
      }
      txtcolor (YELLOW);
      cin >> num;
   	txtcolor (WHITE);

      /*****************************************/
      /* FUNCTION TO ERROR CHECK VALID INTEGER */
      /*****************************************/
      if (num <= false || cin.fail())
      {
         failed = true;

      	cin.clear();		// CLEARS ERROR FLAG ON CIN SO FUTURE
         						// I/O OPERATIONS WILL WORK CORRECTLY

			cin.sync();			// DISCARDS ALL UNREAD CHARACTERS FROM INPUT BUFFER
         						// BASICALLY ANOTHER WAY TO DO CIN.IGNORE

      	printErrorMessage (err);
      }
   }
    while (num <= false || failed == true);
}

void inputAnyInt (short int &num, apstring prmpt)
/*************************************************************/
/* PRECONDITION: PROGRAM NEEDS A (POSITIVE) INT VALUE   	    */
/* POSTCONDITION: PROMPTS USER FOR AN INTEGER VALUE TO INPUT */
/* 					LOOPS UNTIL CORRECT VALUE IS INPUTTED      */
/*************************************************************/
{
	bool failed;

	do
   {
   	failed = false;
   	makeWindows (15, 10, 65, 23, GREEN);
   	gotoxy (8, 10);
   	txtcolor (WHITE);

      if (prmpt.length() >= 40)
      // IF THE LENGTH OF THE PROMPT IS TOO LONG, SPLITS THE PROMPT BETWEEN TWO
      // LINES
      {
      	gotoxy (5, 3);
         cout << prmpt.substr (0, 40);

         gotoxy (5, 5);
         cout << prmpt.substr (40, 40);

         gotoxy (5, 7);
      }
      else
      // ELSE, PRINTS THE PROMPT REGULARLY
      {
   		gotoxy (5, 4);
   		cout << prmpt;
      }
      txtcolor (YELLOW);
      cin >> num;
   	txtcolor (WHITE);

      /*****************************************/
      /* FUNCTION TO ERROR CHECK VALID INTEGER */
      /*****************************************/
      if (cin.fail())
      {
         failed = true;

      	cin.clear();		// CLEARS ERROR FLAG ON CIN SO FUTURE
         						// I/O OPERATIONS WILL WORK CORRECTLY

			cin.sync();			// DISCARDS ALL UNREAD CHARACTERS FROM INPUT BUFFER
         						// BASICALLY ANOTHER WAY TO DO CIN.IGNORE

      	printErrorMessage("Input error! (A non-numerical value may have been inputted)");
      }
   }
   while (num <= false || failed == true);
}

void printErrorMessage (apstring err)
/******************************************************/
/* PRECONDITION: USER NEEDS A CORRECT VALUE           */
/* POSTCONDITION: PRINTS OUT ERROR MESSAGE IF INVALID */
/******************************************************/
{
	/*****************/
	/* ERROR MESSAGE */
	/*****************/
   makeWindows (15, 10, 65, 17, RED);
   gotoxy (22, 2);
   cout << "ERROR";

   gotoxy (2, 4);
   txtcolor (YELLOW);
   if (err.length() >= 50)
   // SPLITS THE ERROR BETWEEN TWO LINES IF THE ERROR IS OVER 50 LENGTH
   {
   	cout << err.substr (0, 50);
   	gotoxy (2, 5);
   	cout << err.substr (50, 50);
   }
   else                                                                       
   // ELSE PRINTS THE ERROR REGULARLY
   {
   	cout << err;
   }

   txtcolor (WHITE);
   gotoxy (12, 7);
   cout << "press ENTER to continue...";
   getch();
}

int printMenu()
/*******************************************************/
/* PRECONDITION: 	USER NEEDS MENU OPTIONS              */
/* POSTCONDITION: DISPLAYS THE PROGRAM MENU 				 */
/*******************************************************/
{
	int ans = 0;
	int x = 2;
	int y = 2;
	while (ans == 0)
	{
      makeWindows (15, 10, 65, 23, GREEN);
      gotoxy(x, y);
      txtcolor(WHITE);
      cout << "Menu: ";
      gotoxy(x, y + 1);
      cout << "Create new reservation: 1";
      gotoxy(x, y + 2);
      cout << "Delete a reservation: 2";
      gotoxy(x, y + 3);
      cout << "Display reservation details: 3";
      gotoxy(x, y + 4);
      cout << "Display all customer details: 4";     // ALPHABETICAL ORDER
      gotoxy(x, y + 5);
      cout << "Exit: 5";
      gotoxy(x, y + 7);
      cin >> ans;

      /*****************************************************/
      /* IF STATEMENT TO CHECK FOR UNAVAILABLE MENU OPTION */
      /*****************************************************/
      if (ans < 1 || ans > 5)
      {
   		printErrorMessage(PROMPT2);
         ans = 0;
   	}
   }
   return ans;
}

void programDescription()
/******************************************************/
/* PRECONDITION: USER WAITING FOR PROGRAM DESCRIPTION */
/* POSTCONDITION: PRINTS OUT PROGRAM DESCRIPTION      */
/******************************************************/
{
	makeWindows (15, 10, 65, 17, BLUE, LIGHTGREEN, BLUE);
   gotoxy (22, 1);
   cout << "Program 5";
   gotoxy (10, 3);
   cout << "THIS PROGRAM WILL MAINTAIN HOTEL";
   gotoxy (10, 4);
   cout << "RESERVATIONS IN A LINKED LIST";
   getch ();
}

void windowHeading(int nm)
/*******************************************/
/* PRECONDITION: WINDOW NEEDS A HEADING    */
/* POSTCONDITION: PRINTS HEADING IN WINDOW */
/*******************************************/
{
	gotoxy (15, 1);
}
