//Nathaniel Leslie-Rivas, Ryan Vera, Luc Cote
//CS 135.1102
//Purpose: Create Connect four with team
//4.29.2020
#include <stdio.h>
#include <string.h>
#define scores "scores.txt"


int getMenuChoice ();

int
main ()
{
  FILE *fp;
  int userMenu;

  do
    {
      userMenu = getMenuChoice ();
      switch (userMenu)
	{
	case 1:
	  break;
	case 2:
	  break;
	case 0:
	  return 0;
	  break;
	default:
	  printf ("invalid choice\n");
	  break;
	}

    }
  while (userMenu != 0);




  return 0;
}

/*void displayBoard(char board[], int maxRow, int maxCol)
	{
		


	}/*

int getMenuChoice (){
  int userOption;
  printf ("***CONNECT 4***\n");
  printf ("1. Play Game\n");
  printf ("2. Show Scores\n");
  printf ("0. EXIT\n");
  printf ("Enter your choice: ");
  scanf ("%d", &userOption);
  return userOption;
}

