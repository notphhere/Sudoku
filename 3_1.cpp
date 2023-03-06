#include <iostream>
#include <fstream>
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
#define sidelength 9
using namespace std;

// char sudoku[9][9];
int sudoku[sidelength][sidelength];

void storingarrayas_char(string fname)
{
    char ch;
    ifstream file(fname);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ch = file.get();
            if (ch != 'X')
            {
                sudoku[i][j] = ch;
            }
            else
            {
                sudoku[i][j] = '_';
            }
        }
        file.get(ch); // Got junk number at the end of each line in sudoku text file, this is to absorb junk numbers
    }

    file.close();
}
void storingarrayas_int(string fname)
{
    char ch;
    ifstream file(fname);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ch = file.get();
            if (ch != 'X')
            {
                sudoku[i][j] = ch - '0';
            }
            else
            {
                sudoku[i][j] = 0;
            }
        }
        file.get(ch); // Got junk number at the end of each line in sudoku text file, this is to absorb junk numbers
    }

    file.close();
}
void displayboard()
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
        {
            cout << "-------- -------- --------" << endl;
        }
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
            {
                cout << "| ";
            }
            cout << sudoku[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-------- -------- --------" << endl;
}
bool isPresentInCol(int col, int num)
{
    for (int row = 0; row < sidelength; row++)
        if (sudoku[row][col] == num)
            return true;
    return false;
}
bool isPresentInRow(int row, int num)
{
    for (int col = 0; col < sidelength; col++)
        if (sudoku[row][col] == num)
            return true;
    return false;
}
bool isPresentInBox(int startrow, int startcol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (sudoku[row + startrow][col + startcol] == num)
                return true;
    return false;
}
bool findEmptyPlace(int &row, int &col)
{
    for (row = 0; row < sidelength; row++)
        for (col = 0; col < sidelength; col++)
            if (sudoku[row][col] == 0)
                return true;
    return false;
}
bool isValidPlace(int row, int col, int num)
{
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3, col - col % 3, num);
}
bool solveSudoku()
{
    int row, col;
    if (!findEmptyPlace(row, col))
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isValidPlace(row, col, num))
        {
            sudoku[row][col] = num;
            if (solveSudoku())
                return true;
            sudoku[row][col] = 0;
        }
    }
    return false;
}

int main()
{
    char reply;
    storingarrayas_int("P1_SUDOKU2.txt");
    cout << UNDERLINE << "Original board: " << CLOSEUNDERLINE << endl;
    displayboard();
    if (solveSudoku())
    {
        cout << "\n\n";
        do
        {
            cout << "Need answer? (y/n) ";
            cin >> reply;
        } while ((reply != 'Y') && (reply != 'N') && (reply != 'y') && (reply != 'n'));

        if (reply == 'Y' || reply == 'y')
        {
            cout << endl
                 << UNDERLINE << "Answer board: " << CLOSEUNDERLINE << endl;
            displayboard();
        }
        else
        {
            cout << endl
                 << "Good luck solving" << endl
                 << endl;
        }
    }
    else
    {
        cout << "No solution" << endl;
    }
}
