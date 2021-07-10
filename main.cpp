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

int relateNumToPos(int row, int column)
{
    return (3 * (row - 1) + column);
};

rowColData relatePosToNum(int inputNumber)
{
    const int row = 0;
    const int column = 0;
    rowColData rowAndColumn;
    rowAndColumn.row = row;
    rowAndColumn.column = column;
    return rowAndColumn;
    // 1 --> 1 | 1
    // 2 --> 1 | 2
    // 3 --> 1 | 3
    // 4 --> 2 | 1
    // 5 --> 2 | 2
    // 6 --> 2 | 3
    // 7 --> 3 | 1
    // 8 --> 3 | 2
    // 9 --> 3 | 3
}

playerResponse playerPrompt(string board[3][3], int player)
{
    string character;
    int position;
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
                    sampleRowText += " - ";
                }
                else
                {
                    sampleRowText += to_string(relateNumToPos(row, column));
                };
            };
            sampleRowText += "\n ----------\n";
            sampleBoardText += sampleRowText;
        };
        cout << sampleBoardText << endl;
        cin >> position;
        if (position >= 0 && position <= 9)
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
    data.position = position;
    return data;
};

int main()
{

    string board[3][3] = {{" ", " ", " "}, {"O", "O", "X"}, {"X", "O", "O"}};
    bool gameRunning = true;
    bool playerOneTurn = true;
    bool playerTwoTurn = false;

    while (gameRunning)
    {
        drawBoard(board);
        playerResponse response = playerPrompt(board, 1);
        int boardPosition = response.position;
    };
}