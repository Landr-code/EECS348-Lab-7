#include <iostream>
#include <fstream>      //for file input
using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
    int data[SIZE][SIZE]; // 2D array for matrix data (using int for simplicity)

public:
    // 1. Read values from stdin into a matrix
    void readFromStdin() {
        ifstream file("matrix-data.txt");

        if (!file.is_open()) {                               // Check if the file opened successfully
            cout << "Uh oh! Error opening file!" << endl;
            return;
        }
        for (int i = 0; i < SIZE; i++) {                    //read values from file into matrix
            for (int j = 0; j < SIZE; j++) {
                file >> data[i][j];
            }
        }

        file.close();                                      //Close that file after reading
    }

    // 2. Display a matrix
    void display() const {
        for (int i = 0; i < SIZE; i++) {                    //loop through the matrix and print values in a grid format
            for (int j = 0; j < SIZE; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;                                   //move to the next row
        }
    }

    // 3. Add two matrices (operator overloading for +)
    Matrix operator+(const Matrix& other) const {
        Matrix result;                                      //store the result of addition

        for (int i = 0; i < SIZE; i++) {                    //add the corresponding elements of both matrices
            for (int j = 0; j < SIZE; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;                                      //return the new matrix
    }

    // 4. Multiply two matrices (operator overloading for *)
    Matrix operator*(const Matrix& other) const {
        Matrix result;

        for (int i = 0; i < SIZE; i++) {                    //initialize result matrix to 0
            for (int j = 0; j < SIZE; j++) {
                result.data[i][j] = 0;
            }
        }

        for (int i = 0; i < SIZE; i++) {                    //perform matrix mutliplication
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;

    // 5. Compute the sum of matrix diagonal elements
    int sumOfDiagonals() const {
        int sum = 0;

        for (int i = 0; i < SIZE; i++) {                     //add main diagonal from top-left to bottom-right
            sum += data[i][i];
        }

        for (int i = 0; i < SIZE; i++) {                    //add secondary diagonal from top-right to bottom-left
            sum += data[i][SIZE - 1 - i];
        }

        return sum;
    }

    // 6. Swap matrix rows
    void swapRows(int row1, int row2) {                     //Check if the indices are valid
        if (row1 < 0 || row1 >= SIZE || row2 < 0 || row2 >= SIZE) {
            cout << "Invalid row indices!" << endl;
            return;
        }

        for (int j = 0; j < SIZE; j++) {                    //Swap them rows element by element
            int temp = data[row1][j];
            data[row1][j] = data[row2][j];
            data[row2][j] = temp;
        }
    }
};

int main() {
    // Example usage:
    Matrix mat1;
    cout << "Enter values for Matrix 1:" << endl;
    mat1.readFromStdin();
    cout << "Matrix 1:" << endl;
    mat1.display();

    Matrix mat2;
    cout << "Enter values for Matrix 2:" << endl;
    mat2.readFromStdin();
    cout << "Matrix 2:" << endl;
    mat2.display();

    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.display();

    Matrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.display();

    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping rows:" << endl;
    mat1.display();

    return 0;
}