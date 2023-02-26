// Spring 2023
// Data Structures
// Project 2

#include <fstream> // for reading fileInput
#include <iostream>
#include <string>

using namespace std;


string* parseLine(string line, int numEntries);

class tableClass {
protected:
  string **myTable; // 2D string array to store all values (strings and numbers)
  string *DTarray;  // 1D array to store the data types of each column
  int numRows, numCols; // number of rows and columns

public:
  // Constructors
  tableClass();
  tableClass(int rows, int cols);

  // Overload the [] operator to access a row in myTable
  string *operator[](int i);

  // File reading Method
  void readCSV(string filename);

  // Output Method
  void display();

  // Sort the table
  void sortTable();

  // Search record
  string *searchRecord(string str); // str will be from the first column

  // Search value from table
  void searchValue(string str);

  // Getters
  int getNumberRows(); // returns the number of rows
  int getNumberCols(); // returns the number of columns
  tableClass *
  getColumns(int colLeft,
             int colRight); // returns a tableClass with a set of columns from
                            // colLeft to colRight indices
  tableClass *getRows(int rowTop,
                      int rowBottom); // returns a tableClass with a set of rows
                                      // from rowTop to rowBottom indices
  tableClass *getRowsCols(int colLeft, int colRight, int rowTop,
                          int rowBottom); // returns a tableClass with the data
                                          // between the cols and rows given

  // Find info of a given column
  double findMin(int colNumber); // returns the min of the given column

  // Destructor
  ~tableClass();
};

// Return the number of rows
int tableClass::getNumberRows() { return numRows; }

// Return the number of cols
int tableClass::getNumberCols() { return numCols; }

// Returns the ith row
string *tableClass::operator[](int i) { return myTable[i]; }

tableClass::tableClass() {}

tableClass::tableClass(int rows, int cols) {

  // Initialize myTable rows
  myTable = new string *[rows];

  // Initialize myTable columns
  for (int i = 0; i < rows; i++) {
    myTable[i] = new string[cols];
  }

  DTarray = new string[cols];

  numRows = rows;
  numCols = cols;
}

// displays the table
void tableClass::display() {

  // Print data types

  // for (int i = 0; i < numCols; i++) {

  //   // Add a space between entries unless it's the last one
  //   cout << DTarray[i] << (i == numCols ? "" : " ");
  // }

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      // Add a space between entries unless it's the last one
      cout << myTable[i][j] << (j == numCols ? "" : " ");
    }

    // Print a newline after each row unless it's the last
    if (i != numRows) {
      cout << endl;
    }
  }
}

void tableClass::sortTable() {

  for (int i = 1; i < numRows; i++) {

    // Get the ith row, starting from the second row
    string* first = myTable[i];
    for (int j = i - 1; j >= -1; j--) {

      // Get the row above
      string* second = myTable[j];

      // If the first column of the first row is greater than the first column of the second, we've found the right spot
      if (j == -1 || first[0].compare(second[0]) > 0) {
	myTable[j + 1] = first;
	break;
      } else {
	// Move the row above down one
	myTable[j + 1] = second;
      }
    }
  }
}


// Reads the csv file and stores the rows in the myTable array
void tableClass::readCSV(string filename) {
  fstream fs;
  fs.open(filename, fstream::in | fstream::out);


  string line;
  for (int i = 0; i < numRows; i++) {

    getline(fs , line, '\n');

    myTable[i] = parseLine(line, numCols);
    
  }

  fs.close();
}

string* parseLine(string line, int numEntries) {

  // Current index of the string
  int curIdx = 0;
  
  string* entries = new string[numEntries];
  
  for (int i = 0; i < numEntries; i++) {

    string entry = "";

    // Add each character to entry until you reach a comma
    while (curIdx < line.length() && line.at(curIdx) != ',' && line.at(curIdx) != '\r') {

      entry += line.at(curIdx);
      curIdx++;
    }
    entries[i] = entry;
    curIdx++;
  }

  return entries;
}


int main() {
  int numRows, numCols;
  string fileName;
  char option;

  cin >> numRows >> numCols >> fileName;
  cout << "NumRows: " << numRows << endl;
  cout << "NumCols: " << numCols << endl;
  cout << "FileName: " << fileName << endl;

  tableClass *table = new tableClass(numRows, numCols);

  // TODO: read the file input name and call readCSV()
  
  table->readCSV(fileName);


  table->display();

  table->sortTable();


  cout << "Sorted: " << endl;
  table->display();
  // TODO: read the data types and store in DTarray of d

  // TODO: start reading the options till the end of the file

  return 0;
}
