
/*
    EECS 348 - Software Engineering
    Lab 10 - C++ Programming

    Author: Kaleb Blakemore
    KU ID: 3228599

    Description:
    This program reads two matrices from a file and performs
    addition, multiplication, diagonal calculations, row swaps,
    column swaps, and element updates.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

// Matrix class definition
class Matrix {
private:
    int size;
    int** data;

    // Allocate memory for the matrix
    void allocateMemory() {
        data = new int*[size];

        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
        }
    }

public:
    // Constructor
    Matrix(int n = 0) {
        size = n;
        data = nullptr;

        if (size > 0) {
            allocateMemory();

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    data[i][j] = 0;
                }
            }
        }
    }

    // Copy constructor (creates a deep copy)
    Matrix(const Matrix& other) {
        size = other.size;
        data = nullptr;

        if (size > 0) {
            allocateMemory();

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
    }

    // Destructor (releases allocated memory)
    ~Matrix() {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    // Assignment operator (deep copy)
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < size; i++) {
                delete[] data[i];
            }

            delete[] data;

            size = other.size;
            data = nullptr;

            if (size > 0) {
                allocateMemory();

                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        data[i][j] = other.data[i][j];
                    }
                }
            }
        }

        return *this;
    }

    // Read matrix values from the input file
    bool readFromFile(ifstream& input) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!(input >> data[i][j])) {
                    return false;
                }
            }
        }

        return true;
    }

    // Display matrix with aligned columns
    void display() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(4) << data[i][j];
            }

            cout << endl;
        }
    }

    // Overload + operator for matrix addition
    Matrix operator+(const Matrix& other) const {
        if (size != other.size) {
            throw invalid_argument("Matrix sizes do not match.");
        }

        Matrix result(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Overload * operator for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (size != other.size) {
            throw invalid_argument("Matrix sizes do not match.");
        }

        Matrix result(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Calculate main diagonal sum
    int mainDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += data[i][i];
        }

        return sum;
    }

    // Calculate secondary diagonal sum
    int secondaryDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += data[i][size - 1 - i];
        }

        return sum;
    }

    // Swap two rows
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= size ||
            row2 < 0 || row2 >= size) {
            cout << "Invalid row indices." << endl;
            return;
        }

        for (int j = 0; j < size; j++) {
            int temp = data[row1][j];
            data[row1][j] = data[row2][j];
            data[row2][j] = temp;
        }
    }

    // Swap two columns
    void swapColumns(int col1, int col2) {
        if (col1 < 0 || col1 >= size ||
            col2 < 0 || col2 >= size) {
            cout << "Invalid column indices." << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            int temp = data[i][col1];
            data[i][col1] = data[i][col2];
            data[i][col2] = temp;
        }
    }

    // Update a matrix element
    void updateElement(int row, int col, int value) {
        if (row < 0 || row >= size ||
            col < 0 || col >= size) {
            cout << "Invalid matrix indices." << endl;
            return;
        }

        data[row][col] = value;
    }
};

// Practice 5: Swap rows (Matrix passed by value)
Matrix swapMatrixRows(Matrix matrix, int row1 = 0, int row2 = 1) {
    matrix.swapRows(row1, row2);
    return matrix;
}

// Practice 6: Swap columns
Matrix swapMatrixColumns(Matrix matrix, int col1 = 0, int col2 = 1) {
    matrix.swapColumns(col1, col2);
    return matrix;
}

// Practice 7: Update matrix element
Matrix updateMatrix(Matrix matrix, int row = 0,
                    int col = 0, int value = 100) {
    matrix.updateElement(row, col, value);
    return matrix;
}

// Main program
int main() {
    string filename;

    cout << "Enter input filename: ";
    cin >> filename;

    // Open input file
    ifstream input(filename);

    if (!input.is_open()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    // Read matrix dimensions
    int n;

    if (!(input >> n) || n <= 0) {
        cout << "Invalid matrix size." << endl;
        return 1;
    }

    // Create and initialize matrices
    Matrix A(n);
    Matrix B(n);

    if (!A.readFromFile(input) || !B.readFromFile(input)) {
        cout << "Error reading matrix data." << endl;
        return 1;
    }

    input.close();

    // Practice 1: Display matrices
    cout << "\nMatrix A:" << endl;
    A.display();

    cout << "\nMatrix B:" << endl;
    B.display();

    // Practice 2: Matrix addition
    cout << "\nA + B:" << endl;
    Matrix sum = A + B;
    sum.display();

    // Practice 3: Matrix multiplication
    cout << "\nA * B:" << endl;
    Matrix product = A * B;
    product.display();

    // Practice 4: Diagonal sums
    cout << "\nDiagonal sums for Matrix A:" << endl;

    cout << "Main diagonal sum: "
         << A.mainDiagonalSum() << endl;

    cout << "Secondary diagonal sum: "
         << A.secondaryDiagonalSum() << endl;

    // Practice 5: Swap rows 0 and 2
    cout << "\nProblem 5 - Rows 0 and 2 swapped:" << endl;

    Matrix rowResult = swapMatrixRows(A, 0, 2);
    rowResult.display();

    // Practice 6: Swap columns 0 and 2
    cout << "\nProblem 6 - Columns 0 and 2 swapped:" << endl;

    Matrix columnResult = swapMatrixColumns(A, 0, 2);
    columnResult.display();

    // Practice 7: Update row 1, column 2 to 99
    cout << "\nProblem 7 - Updated matrix:" << endl;

    Matrix updatedResult = updateMatrix(A, 1, 2, 99);
    updatedResult.display();

    return 0;
}
