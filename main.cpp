#include <iostream>

using namespace std;

class playerResponse
{
public:
    string character;
    int position;
};

class rowColData
{
public:
    int row;
    int column;
};

bool success(string board[3][3], rowColData updatedPosition, int updatedBoardNumber)
{
    int updatedRow = updatedPosition.row;
    int updatedColumn = updatedPosition.column;
    string currentChar = board[updatedRow - 1][updatedColumn - 1];
    // int top = updatedBoardNumber - 3;
    // if (top >= 0 && top <= 9)
    // {
    // };
    // int topRight = updatedBoardNumber - 2;
    // if (topRight >= 0 && topRight <= 9)
    // {
    // };
    // int right = updatedBoardNumber + 1;
    // if (right >= 0 && right <= 9)
    // {
    // };
    // int bottomLeft = updatedBoardNumber + 4;
    // if (bottomLeft >= 0 && bottomLeft <= 9)
    // {
    // };
    // int bottom = updatedBoardNumber + 3;
    // if (bottom >= 0 && bottom <= 9)
    // {
    // };
    return false;
}

void drawBoard(string board[3][3])
{
    string boardText = "\n";
    for (int row = 0; row < 3; row++)
    {
        string rowText = "";
        for (int column = 0; column < 3; column++)
        {
            rowText += "| " + board[row][column] + " ";
        };
        rowText += "\n ----------\n";
        boardText += rowText;
    };
    cout << boardText << endl;
};

int relatePosToNum(int row, int column)
{
    return (3 * (row - 1) + column);
};

rowColData relateNumToPos(int inputNumber)
{
    int row = 0;
    int column = 0;
    rowColData rowAndColumn;
    if (inputNumber == 1)
    {
        row = 1;
        column = 1;
    };
    if (inputNumber == 2)
    {
        row = 1;
        column = 2;
    }
    if (inputNumber == 3)
    {
        row = 1;
        column = 3;
    }
    if (inputNumber == 4)
    {
        row = 2;
        column = 1;
    }
    if (inputNumber == 5)
    {
        row = 2;
        column = 2;
    }
    if (inputNumber == 6)
    {
        row = 2;
        column = 3;
    }
    if (inputNumber == 7)
    {
        row = 3;
        column = 1;
    }
    if (inputNumber == 8)
    {
        row = 3;
        column = 2;
    }
    if (inputNumber == 9)
    {
        row = 3;
        column = 3;
    }
    rowAndColumn.row = row;
    rowAndColumn.column = column;
    return rowAndColumn;
    //Note: This must be improved by removing all the if statements and coming up with a simple equation. Unfortunately, I do not know the mathematical formula right now, so this will have to do for the sake of the game functioning.
}

playerResponse playerPrompt(string board[3][3], int player)
{
    string character;
    int numberPosition;
    bool waitingForChar = true;
    bool waitingForPosition = true;
    while (waitingForChar)
    {
        cout << "Type either the character X or O (capitalized)" << endl;
        cin >> character;
        if (character == "X" || character == "O")
        {
            break;
        };
        cout << "You typed an incorrect character. Try again." << endl;
        continue;
    };
    while (waitingForPosition)
    {
        cout << "Choose the number corresponding to the position that you want to place on the board" << character << endl;
        string sampleBoardText = "\n";
        for (int row = 0; row < 3; row++)
        {
            string sampleRowText = "";
            for (int column = 0; column < 3; column++)
            {
                if (board[row][column] == "X" || board[row][column] == "O")
                {
                    sampleRowText += "| - ";
                }
                else
                {
                    const string numberText = to_string(relatePosToNum(row + 1, column + 1));
                    sampleRowText += "| " + numberText + " ";
                };
            };
            sampleRowText += "\n ----------\n";
            sampleBoardText += sampleRowText;
        };
        cout << sampleBoardText << endl;
        cin >> numberPosition;
        int row = relateNumToPos(numberPosition).row;
        int column = relateNumToPos(numberPosition).column;
        if (board[row][column] == "X" || board[row][column] == "O")
        {
            cout << "That spot is occupied. Please try again. " << endl;
            continue;
        };
        if (numberPosition >= 0 && numberPosition <= 9)
        {
            waitingForPosition = false;
            break;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }
    }
    playerResponse data;
    data.character = character;
    data.position = numberPosition;
    return data;
};

int main()
{

    string board[3][3] = {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};
    bool gameRunning = true;
    bool playerOneTurn = true;
    bool playerTwoTurn = false;

    while (gameRunning)
    {
        drawBoard(board);
        playerResponse response = playerPrompt(board, 1);
        rowColData rowAndColumn = relateNumToPos(response.position);
        const int boardRow = rowAndColumn.row;
        const int boardColumn = rowAndColumn.column;
        board[boardRow - 1][boardColumn - 1] = response.character;
        if (!success(board, rowAndColumn, response.position))
        {
            continue;
        }
        else
        {
            cout << "Congratulations! You won the game!" << endl;
            break;
        }
    };
}