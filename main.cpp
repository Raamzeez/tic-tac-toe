#include <iostream>

using namespace std;

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

void playerPrompt(string board[3][3], string player)
{
    string character;
    string position;
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
                    sampleRowText += " ";
                }
                else
                {
                    sampleRowText += to_string(((row * row) + column - 1));
                    //Pick up from here and figure out the mathematical formula that will relate the rows and columns to the corresponding 1-9 integers
                };
            };
        };
    }
}

int main()
{

    string board[3][3] = {{"X", "O", "X"}, {"O", "O", "X"}, {"X", "O", "O"}};
    bool gameRunning = true;
    bool playerOneTurn = true;
    bool playerTwoTurn = false;

    while (gameRunning)
    {
        drawBoard(board);
        break;
    };
}