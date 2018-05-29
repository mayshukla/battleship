#include <iostream>
#include <cstdlib> // for rand()
#include <ctime> // to seed random number generator

class Board
{

  public:
    int * * grid; // since grid is 2D, must be pointers to pointers
    int cols, rows;
    int shipx, shipy;

    // Constructor
    Board (int c, int r)
    {
      cols = c;
      rows = r;

      // dynamically allocate memory for grid
      grid = new int * [cols]; // note: new returns pointer so here we only use one *
      for (int n = 0; n < cols; n++) // n represents the COLUMN index
      {
        grid[n] = new int [rows];
      }

      // intitialize grid to zeros
      // this might be optional
      for (int x = 0; x < cols; ++x)
      {
        for (int y = 0; y < rows; ++y)
        {
          grid[x][y] = 0;
        }
      }

      // randomly place a ship somewhere
      srand (time(NULL)); // seed
      shipx = std::rand() % cols;
      shipy = std::rand() % rows;
      // grid [shipx] [shipy] = 2; // unneccessary

    } // end constructor

    // method to display status of board
    void print_board ()
    {
      // print column labels
      std::cout << "   ";
      for (int x = 0; x < cols; ++x)
      {
        if (x<9) { std::cout << " " << x+1; } // when x=9, the label is actually 10
        else { std::cout << x+1; }
      }
      std::cout << std::endl;
      std::cout << "   ";
      for (int x = 0; x < cols; ++x)
      {
        std::cout << "--";
      }
      std::cout << std::endl;

      for (int y = 0; y < rows; ++y)
      {
        // print row labels
        if (y<9) { std::cout << " " << y+1 << "| "; } // when y=9, the label is actually 10
        else { std::cout << y+1 << "| "; }

        for (int x = 0; x < cols; ++x)
        {
          std::cout << grid[x][y] << " ";
        }
        std::cout << std::endl;
      }
    }

};

int main ()
{
  int rows, cols; // will be used to initialize board
  int guess_col, guess_row; // to store user's guesses

  // prompt user for board dimensions
  std::cout << "Enter columns of board: ";
  std::cin >> cols;
  std::cout << std::endl;

  std::cout << "Enter rows of board: ";
  std::cin >> rows;
  std::cout << std::endl;

  // initialize and display board
  Board board(cols, rows);
  std::cout << board.cols << "x" << board.rows << " board:" << std::endl;

  // display location of ship for debugging purposes, remove before release
  std::cout << std::endl;
  std::cout << "Ship at " << board.shipx + 1 << ", " << board.shipy + 1 << std::endl;
  std::cout << std::endl;

  do {
    // display board
    board.print_board();

    // prompt user for turn
    std::cout << "Guess a column: ";
    std::cin >> guess_col;
    guess_col = guess_col - 1; // convert to zero-index

    std::cout << "Guess a row: ";
    std::cin >> guess_row;
    guess_row = guess_row - 1; // convert to zero-index

    if (guess_col == board.shipx && guess_row == board.shipy) // should I check the grid or just each coordinate?
    {
      std::cout << "You win!" << std::endl;
      break;
    }
    else
    {
      board.grid[guess_col][guess_row] = 1; // mark which spots the user has tried
      std::cout << "Try again." << std::endl << std::endl;
    }
  } while (guess_col != board.shipx || guess_row != board.shipy);



  return 0;
}
