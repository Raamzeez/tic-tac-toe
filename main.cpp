#include <iostream>
#include <cmath>

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

bool validateInput(int input)
{
    if (input >= 0 && input <= 9)
    {
        return true;
    };
    cout << "Your input was invalid. Please try again." << endl;
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
    row = floor(inputNumber / 3);
    column = inputNumber - (3 * (row - 1));
    rowAndColumn.row = row;
    rowAndColumn.column = column;
    return rowAndColumn;
}

bool validateChar(string board[3][3], int firstPosNumber, int secondPosNumber, bool repeat, string expectedChar)
{
    rowColData newPosition = relateNumToPos(firstPosNumber);
    string newChar = board[newPosition.row][newPosition.column];
    if (expectedChar == newChar)
    {
        if (repeat == false)
        {
            validateChar(board, firstPosNumber, secondPosNumber, true, expectedChar);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool success(string board[3][3], rowColData updatedPosition, int updatedBoardNumber)
{
    int updatedRow = updatedPosition.row;
    int updatedColumn = updatedPosition.column;
    string currentChar = board[updatedRow - 1][updatedColumn - 1];
    int top = updatedBoardNumber - 3;
    if (validateInput(top) && validateChar(board, top, top - 3, false, currentChar))
    {
        return true;
    }
    int topRight = updatedBoardNumber - 2;
    if (validateInput(topRight) && validateChar(board, topRight, topRight - 2, false, currentChar))
    {
        return true;
    }
    int right = updatedBoardNumber + 1;
    if (validateInput(right) && validateChar(board, right, right + 1, false, currentChar))
    {
        return true;
    }
    int bottomRight = updatedBoardNumber + 4;
    if (validateInput(bottomRight) && validateChar(board, bottomRight, bottomRight + 4, false, currentChar))
    {
        return true;
    }
    int bottom = updatedBoardNumber + 3;
    if (validateInput(bottom) && validateChar(board, bottom, bottom + 3, false, currentChar))
    {
        return true;
    }
    int bottomLeft = updatedBoardNumber + 2;
    if (validateInput(bottomLeft) && validateChar(board, bottomLeft, bottomLeft + 2, false, currentChar))
    {
        return true;
    }
    int left = updatedBoardNumber - 1;
    if (validateInput(left) && validateChar(board, left, left - 1, false, currentChar))
    {
        return true;
    }
    int topLeft = updatedBoardNumber - 4;
    if (validateInput(topLeft) && validateChar(board, topLeft, topLeft + 3, false, currentChar))
    {
        return true;
    }
    return false;
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
        cout << numberPosition << endl;
        cout << typeid(numberPosition).name() << endl;
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
            cout << "The game is complete. Thanks for playing!" << endl;
            break;
        }
    };
}