#include <iostream>
#include <cmath>

using namespace std;

class playersSetup
{
public:
    string playerOneSymbol;
    string playerTwoSymbol;
};

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

int numOfCharacters(string board[3][3])
{
    int numOfCharacters = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (board[row][column] == "X" || board[row][column] == "O")
            {
                numOfCharacters++;
            }
        }
    }
    return numOfCharacters;
}

bool validateInput(int input)
{
    if (input >= 0 && input <= 9)
    {
        return true;
    }
    else
    {
        return false;
    }
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
    rowColData newPosition = relateNumToPos(repeat ? secondPosNumber : firstPosNumber);
    string newChar = board[newPosition.row - 1][newPosition.column - 1];
    if (expectedChar == "X" || expectedChar == "O" && newChar == "X" || newChar == "O")
    {
        if (expectedChar == newChar)
        {
            if (repeat == false)
            {
                return validateChar(board, firstPosNumber, secondPosNumber, true, newChar);
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
    else
    {
        return false;
    }
}

bool success(string board[3][3], rowColData updatedPosition, int updatedBoardNumber)
{
    //Run when there are only 3 characters on the board
    int updatedRow = updatedPosition.row;
    int updatedColumn = updatedPosition.column;
    string currentChar = board[updatedRow - 1][updatedColumn - 1];
    int top = updatedBoardNumber - 3;
    if (validateChar(board, top, top - 3, false, currentChar))
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
};

playersSetup gameSetup()
{
    bool waitingForFirstSymbol = true;
    string playerOneSymbol;
    string playerTwoSymbol;

    while (waitingForFirstSymbol)
    {
        cout << "What symbol will player 1 use? (X or O)" << endl;
        cin >> playerOneSymbol;
        if (playerOneSymbol == "X" || playerOneSymbol == "O")
        {
            waitingForFirstSymbol = false;
        }
        else
        {
            cout << "You type an incorrect symbol. Please try again." << endl;
            continue;
        }
    }
    playerTwoSymbol = playerOneSymbol == "X" ? playerTwoSymbol = "O" : playerTwoSymbol = "X";
    cout << "Player 2 will use " << playerTwoSymbol << endl;
    playersSetup info;
    info.playerOneSymbol = playerOneSymbol;
    info.playerTwoSymbol = playerTwoSymbol;
    return info;
}

playerResponse playerPrompt(string board[3][3], int player, string playerOneSymbol, string playerTwoSymbol)
{
    string character = (player == 1 ? playerOneSymbol : playerTwoSymbol);
    int numberPosition;
    bool waitingForFirstSymbol = true;
    bool waitingForChar = true;
    bool waitingForPosition = true;

    while (waitingForPosition)
    {
        cout << (player == 1 ? "PLAYER 1 TURN: " : "PLAYER 2 TURN: ") << endl;
        cout << "Type the number of the position you want to place the " << character << endl;
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
        if (board[row - 1][column - 1] == "X" || board[row - 1][column - 1] == "O")
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

    playersSetup gameInfo = gameSetup();

    while (gameRunning)
    {
        drawBoard(board);
        playerResponse response = playerPrompt(board, playerOneTurn ? 1 : 2, gameInfo.playerOneSymbol, gameInfo.playerTwoSymbol);
        rowColData rowAndColumn = relateNumToPos(response.position);
        const int boardRow = rowAndColumn.row;
        const int boardColumn = rowAndColumn.column;
        board[boardRow - 1][boardColumn - 1] = response.character;
        if (numOfCharacters(board) >= 3)
        {
            for (int row = 0; row < 3; row++)
            {
                for (int column = 0; column < 3; column++)
                {
                    rowColData rowAndColumn;
                    rowAndColumn.row = row;
                    rowAndColumn.column = column;
                    if (success(board, rowAndColumn, response.position))
                    {
                        drawBoard(board);
                        cout << "PLAYER " << (playerOneTurn ? "1" : "2") << " WON THE GAME! Thanks for playing!" << endl;
                        return 0;
                    }
                }
            }
        }
        playerOneTurn = !playerOneTurn;
        continue;
    };
}