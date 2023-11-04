// Monir Fathalla and Jake Choi
// Completed: [DATE]
// Assignment 2 CMPT 125 ConnectN Game

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 25
#define MINSIZE 8
#define MINCONNECTNUM 4

// proto
int InitializeBoard(int **connectNBoard, int numRowsInBoard);
int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen);
int DisplayBoard(int **connectNBoard, int numRowsInBoard);
int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID);

int main()
{
    int numRows;
    int numToConnect;

    // get numRows from user
    while (1)
    {
        printf("Enter the number of squares along each edge of board\n");
        if (scanf("%d", &numRows) != 1)
        {
            printf("ERROR: The value of numRows is not an integer \n");
            while (getchar() != '\n')
                ;
            continue;
        }
        else if (numRows > MAXSIZE)
        {
            printf("ERROR: Board size too large (>%d)\n", MAXSIZE);
            while (getchar() != '\n')
                ;
            continue;
        }
        else if (numRows < MINSIZE)
        {
            printf("ERROR: Board size too small (<%d)\n", MINSIZE);
            while (getchar() != '\n')
                ;
            continue;
        }
        else
        {
            while (getchar() != '\n')
                ;
            break;
        }
    }
    // get numToConnect from user
    while (1)
    {
        printf("Enter the number of pieces that must form a line to win\n");
        if (scanf("%d", &numToConnect) != 1)
        {
            printf("ERROR: The value provided was not an integer \n");
            while (getchar() != '\n')
                ;
            continue;
        }
        else if (numToConnect > numRows - MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too large (>%d)\n", (numRows - MINCONNECTNUM));
            while (getchar() != '\n')
                ;
            continue;
        }
        else if (numToConnect < MINCONNECTNUM)
        {
            printf("ERROR: Number to connect is too small (<%d)\n", MINCONNECTNUM);
            while (getchar() != '\n')
                ;
            continue;
        }
        else
        {
            while (getchar() != '\n')
                ;
            break;
        }
    }

    // allocate game boards
    int **myConnectNBoard = (int **)malloc(numRows * sizeof(int *));
    for (int i = 0; i < numRows; i++)
    {
        myConnectNBoard[i] = (int *)malloc(numRows * sizeof(int));
    }

    if (!InitializeBoard(myConnectNBoard, numRows))
    {
        printf("ERROR: Could not initialize the game board ");
        return 0;
    }

    int playerID;
    playerID = 2;
    int attempts;
    attempts = 0;
    int chosenColumn;
    // red 1 black 2

    do
    {
        printf("\n\n");
        if (!DisplayBoard(myConnectNBoard, numRows))
        {
            printf("ERROR: Could not display the game board ");
        }
        if (playerID == 1)
        {
            playerID = 2;
        }
        else
        {
            playerID = 1;
        }

        if (playerID == 1)
        {
            printf("Red moves\n");
        }
        else
        {
            printf("Black moves\n");
        }

        while (1)
        {
            if (attempts == 3)
            {
                printf("Too many illegal moves\n");
                if (playerID == 1)
                {
                    printf("Red has forfeited a turn\n");
                }
                else
                {
                    printf("Black has forfeited a turn\n");
                }
                attempts = 0;
                break;
            }
            printf("Enter the column number where you want to put your piece\n");
            if (scanf("%d", &chosenColumn) != 1)
            {
                printf("ERROR: The value provided was not an integer \n");
                while (getchar() != '\n')
                    ;
                attempts++;
                continue;
            }
            // Check if the column chosen is within the valid range
            if (chosenColumn < 0 || chosenColumn > numRows - 1)
            {
                printf("ERROR: Column %d is not on the board: try again \n", chosenColumn);
                printf("ERROR: Column number should be >= 0 and <%d\n", numRows);
                while (getchar() != '\n')
                    ;
                attempts++;
                continue;
            }

            // Find the bottommost available row in the chosen column

            int row = 0;
            while (row < numRows && myConnectNBoard[row][chosenColumn] == 0)
            {
                row++;
            }

            // Check if the column is full (no available row)
            if (row < 0)
            {
                printf("ERROR: Column %d is already completely full try again\n", chosenColumn);
                while (getchar() != '\n')
                    ;
                attempts++;
                continue;
            }
            if (!MakeMove(myConnectNBoard, numRows, playerID, chosenColumn))
            {
                while (getchar() != '\n')
                    ;
                attempts++;
                continue;
            }
            else
            {
                while (getchar() != '\n')
                    ;
                attempts = 0;
                break;
            }
        }
    } while (!CheckWinner(myConnectNBoard, numRows, numToConnect, chosenColumn, playerID));

    if (playerID == 1)
    {
        printf("Red has won\n");
    }
    else
    {
        printf("Black has won\n");
    }
    DisplayBoard(myConnectNBoard, numRows);
}

int InitializeBoard(int **connectNBoard, int numRowsInBoard)
{
    // Check if pointer to the board is NULL
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot initialize the board because the pointer to the board is NULL\n");
        return 0;
    }

    if (numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE)
    {
        // check illegal rows
        printf("ERROR: illegal number of rows in board\n");
        return 0;
    }

    for (int i = 0; i < numRowsInBoard; i++)
    {
        for (int j = 0; j < numRowsInBoard; j++)
        {
            connectNBoard[i][j] = 0; // Initialize each element to 0
        }
    }

    return 1;
}

// DisplayBoard
int DisplayBoard(int **connectNBoard, int numRowsInBoard)
{
    // Check if the pointer to the board is NULL
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot display the game board because the pointer to the board is NULL\n");
        return 0;
    }

    // Check if the number of rows is within the legal range
    if (numRowsInBoard > MAXSIZE || numRowsInBoard < MINSIZE)
    {
        printf("ERROR: illegal number of rows in board\n");
        return 0;
    }

    // Print the column numbers at the top of the board
    printf("   ");
    for (int j = 0; j < numRowsInBoard; j++)
    {
        printf("%3d", j);
    }
    printf("\n");

    // Iterate over each row in the board
    for (int i = 0; i < numRowsInBoard; i++)
    {
        // Print the row number at the left edge of the board
        printf("%2d ", i);

        // Iterate over each column in the row
        for (int j = 0; j < numRowsInBoard; j++)
        {
            // Check the value in the current cell of the board
            if (connectNBoard[i][j] == 2)
            {
                printf("%3c", 'B'); // Print 'B' for black game piece
            }
            else if (connectNBoard[i][j] == 1)
            {
                printf("%3c", 'R'); // Print 'R' for red game piece
            }
            else
            {
                printf("%3c", 'o'); // Print 'o' for empty square
            }
        }
        printf("\n"); // Move to the next line for the next row
    }

    return 1;
}

// MakeMove function
int MakeMove(int **connectNBoard, int numRowsInBoard, int playerID, int columnChosen)
{
    // Check if the board pointer is NULL
    if (connectNBoard == NULL)
    {
        printf("ERROR: cannot make a move because the pointer to the board is NULL\n");
        return 0;
    }

    // Check if the column chosen is within the valid range
    if (columnChosen < 0 || columnChosen > numRowsInBoard)
    {
        printf("Illegal move: Column chosen is out of range\n");
        return 0;
    }

    // Find the bottommost available row in the chosen column
    int row = numRowsInBoard - 1;
    while (row >= 0 && connectNBoard[row][columnChosen] != 0)
    {
        row--;
    }

    // Check if the column is full (no available row)
    if (row < 0)
    {
        printf("Illegal move: Column is already full\n");
        return 0;
    }

    // Place the player's game piece in the chosen column and row
    connectNBoard[row][columnChosen] = playerID;

    // Print the move information based on the player's ID
    if (playerID == 1)
    {
        printf("Red has moved\n");
    }
    else
    {
        printf("Black has moved\n");
    }
    // printf("%d",playerID);

    return 1;
}

int CheckWinner(int **connectNBoard, int numRowsInBoard, int numConnect, int columnChosen, int playerID)
{
    int afterCount = 0;
    int beforeCount = 0;
    int i;

    // Check if the board pointer is NULL
    if (connectNBoard == NULL)
    {
        return 0;
    }

    // Check if the column chosen is within the valid range
    if (columnChosen < 0 || columnChosen >= numRowsInBoard)
    {
        return 0;
    }

    // Check if the pointer to the board is NULL
    if (*connectNBoard == NULL)
    {
        return 0;
    }

    // Find the row where the newest game piece has been placed
    // TOP DOWN
    int row = 0;
    while (row < numRowsInBoard && connectNBoard[row][columnChosen] == 0)
    {
        row++;
    }

    // If the row is not found, the move is not legal
    if (row < 0)
    {
        return 0;
    }

    // Check the row to the right of the columnChosen
    for (i = columnChosen + 1; i < numRowsInBoard; i++)
    {
        if (connectNBoard[row][i] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }

    // Check the row to the left of the columnChosen
    for (i = columnChosen - 1; i >= 0; i--)
    {
        if (connectNBoard[row][i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    // Check if the player has won horizontally
    if (afterCount + beforeCount + 1 >= numConnect)
    {
        return 1;
    }

    // re initialize afterCount and beforeCount to 0
    afterCount = 0;
    beforeCount = 0;

    // Check the column below the newest piece
    for (i = row + 1; i < numRowsInBoard; i++)
    {
        if (connectNBoard[i][columnChosen] == playerID)
        {
            afterCount++;
        }
        else
        {
            // printf("AFTER%d\n",afterCount);
            break;
        }
    }

    // Check if the player has won vertically
    if (afterCount + beforeCount + 1 >= numConnect)
    {
        return 1;
    }

    // re initialize afterCount and beforeCount to 0
    afterCount = 0;
    beforeCount = 0;

    // Check the diagonal row from upper left to lower right
    for (i = 1; row + i < numRowsInBoard && columnChosen + i < numRowsInBoard; i++)
    {
        if (connectNBoard[row + i][columnChosen + i] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }

    // Check the diagonal row from upper left to lower right part 2
    for (i = 1; row - i >= 0 && columnChosen - i >= 0; i++)
    {
        if (connectNBoard[row - i][columnChosen - i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    // Check if the player has won diagonally (upper left to lower right)
    if (afterCount + beforeCount + 1 >= numConnect)
    {
        return 1;
    }

    // re initialize afterCount and beforeCount to 0
    afterCount = 0;
    beforeCount = 0;

    // Check the diagonal row from upper right to lower left
    for (i = 1; row + i < numRowsInBoard && columnChosen - i >= 0; i++)
    {
        if (connectNBoard[row + i][columnChosen - i] == playerID)
        {
            afterCount++;
        }
        else
        {
            break;
        }
    }

    // Check the diagonal row from upper right to lower left part 2
    for (i = 1; row - i >= 0 && columnChosen + i < numRowsInBoard; i++)
    {
        if (connectNBoard[row - i][columnChosen + i] == playerID)
        {
            beforeCount++;
        }
        else
        {
            break;
        }
    }

    // Check if the player has won diagonally (upper right to lower left)
    if (afterCount + beforeCount + 1 >= numConnect)
    {
        return 1;
    }

    // No winning condition found
    return 0;
}