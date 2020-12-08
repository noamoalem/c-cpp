//
// Created by Noa Moalem on 8.6.2020.
//

#include <fstream>
#include "Matrix.h"

/**
 * The constructor, initialize new matrix in size rows*cols, with zeros.
 * @param rows The matrix rows number.
 * @param cols The matrix cols number.
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    if (rows <= ZERO || cols <= ZERO)
    {
        std::cerr << ERR_MSG_IVALID_SIZE << std::endl;
        exit(FAIL);
    }
    else
    {
        matrix = new float[rows * cols];
        for (int i = 0; i < rows * cols; i++)
        {
            matrix[i] = ZERO;
        }

    }
}

/**
 * The default constructor. initialize new matrix in size 1*1, with zero.
 */
Matrix::Matrix() : Matrix(DEFAULT_SIZE, DEFAULT_SIZE)
{
}

/**
 * The copy constructor, initialize new matrix with the given matrix values.
 * @param m given matrix.
 */
Matrix::Matrix(const Matrix &m)
{
    this->rows = (m.rows);
    this->cols = (m.cols);
    this->matrix = new float[rows * cols];
    for (int i = 0; i < rows * cols; i++)
    {
        matrix[i] = m.matrix[i];
    }
}

/**
 * The destructor. delete the matrix array.
 */
Matrix::~Matrix()
{
    delete[] matrix;
}

/**
 * getter for the matrix rows number
 * @return The number of rows.
 */
int Matrix::getRows() const
{
    return rows;
}

/**
 * getter for the matrix cols number
 * @return The number of columns.
 */
int Matrix::getCols() const
{
    return cols;
}

/**
 * Transforms a matrix into a column vector.
 * @return reference for the matrix that vectorize preform on.
 */
Matrix &Matrix::vectorize()
{
    rows = cols * rows;
    cols = DEFAULT_SIZE;
    return *this;
}

/**
 * Prints matrix elements as a matrix.
 */
void Matrix::plainPrint() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i * cols + j] << ' ';
        }
        std::cout << std::endl;
    }
}

/**
 * Assignment of one matrix (rhs) to another.
 * @param rhs matrix to copy the value from.
 * @return the matrix after assignment.
 */
Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    rows = rhs.rows;
    cols = rhs.cols;
    delete[] matrix;
    matrix = new float[rows * cols];

    for (int i = 0; i < rows * cols; i++)
    {
        matrix[i] = rhs.matrix[i];
    }
    return *this;
}

/**
 * Matrix addition accumulation.
 * @param rhs the matrix to add.
 * @return the matrix after the addition of rhs.
 */
Matrix &Matrix::operator+=(const Matrix &rhs)
{
    if (rows != rhs.rows || cols != rhs.cols)
    {
        std::cerr << ERR_MSG_DIFFRENT_MATRIX_SIZE << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < rows * cols; i++)
        {
            matrix[i] += rhs.matrix[i];
        }
    }
    return *this;
}

/**
 * Return the i,j element in the matrix.
 * @param row the row of the wanted element.
 * @param col the column of the wanted element.
 * @return the i,j element in the matrix.
 */
float Matrix::operator()(const int row, const int col) const
{
    if (row >= rows || row < ZERO || col >= cols || col < ZERO)
    {
        std::cerr << ERR_MSG_INDEX_OUT_OF_RANGE << std::endl;
        exit(FAIL);
    }
    return matrix[row * cols + col];
}

/**
 * Return the i,j element in the matrix.
 * @param row the row of the wanted element.
 * @param col the column of the wanted element.
 * @return the i,j element in the matrix.
 */
float &Matrix::operator()(const int row, const int col)
{
    if (row >= rows || row < ZERO || col >= cols || col < ZERO)
    {
        std::cerr << ERR_MSG_INDEX_OUT_OF_RANGE << std::endl;
        exit(FAIL);
    }
    return matrix[row * cols + col];
}

/**
 * Return the i’th element of matrix that represent as a vector.allowed assigment
 * @param index the wanted element.
 * @return Return the i’th element of matrix.
 */
float &Matrix::operator[](const int index)
{
    if (index < ZERO || index >= rows * cols)
    {
        std::cerr << ERR_MSG_INDEX_OUT_OF_RANGE << std::endl;
        exit(FAIL);
    }
    return matrix[index];
}

/**
 * Return the i’th element of matrix that represent as a vector.
 * @param index the wanted element.
 * @return Return the i’th element of matrix.
 */
float Matrix::operator[](const int index) const
{
    if (index < ZERO || index >= rows * cols)
    {
        std::cerr << ERR_MSG_INDEX_OUT_OF_RANGE << std::endl;
        exit(FAIL);
    }
    return matrix[index];
}

/**
 * Prints the number the matrix represent.
 * @param s given output stream.
 * @param rhs The matrix to print.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &s, const Matrix &rhs)
{
    for (int i = 0; i < rhs.rows; i++)
    {
        for (int j = 0; j < rhs.cols; j++)
        {
            if (rhs.matrix[i * rhs.cols + j] <= 0.1f)
            {
                s << "  ";
            }
            else
            {
                s << "**";
            }
        }
        s << std::endl;
    }
    return s;
}

/**
 * Matrix addition. (lhs + rhs)
 * @param lhs
 * @param rhs
 * @return the result of the addition.
 */
Matrix Matrix::operator+(const Matrix &rhs) const
{
    if (rows != rhs.getRows() || cols != rhs.getCols())
    {
        std::cerr << ERR_MSG_DIFFRENT_MATRIX_SIZE << std::endl;
        exit(FAIL);
    }
    else
    {
        Matrix toRet = Matrix(*this);
        for (int i = 0; i < toRet.getRows() * toRet.getCols(); i++)
        {
            toRet[i] += rhs.matrix[i];
        }
        return toRet;
    }
}

/**
 * multiplication of two matrix.
 * @param rhs the second matrix.
 * @return the result of the multiplication.
 */
Matrix Matrix::operator*(const Matrix &rhs) const
{
    if (cols != rhs.getRows())
    {
        std::cerr << ERR_MSG_DIFFRENT_MATRIX_SIZE << std::endl;
        exit(FAIL);
    }
    else
    {
        Matrix toRet(rows, rhs.cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < rhs.cols; ++j)
            {
                for (int k = 0; k < cols; ++k)
                {
                    toRet.matrix[i * toRet.cols + j] +=
                            matrix[i * cols + k] * rhs.matrix[k * rhs.cols + j];
                }
            }
        }
        return toRet;
    }

}

/**
 * Scalar multiplication on the right.
 * @param c Scalar.
 * @return The matrix by reference.
 */
Matrix Matrix::operator*(const float c) const
{
    Matrix toRet = Matrix(*this);
    for (int i = 0; i < toRet.getRows() * toRet.getCols(); i++)
    {
        toRet.matrix[i] = (toRet.matrix[i] * (c));
    }
    return toRet;
}

/**
 * Scalar multiplication on the left.
 * @param c Scalar.
 * @return The matrix by reference.
 */
Matrix operator*(const float c, const Matrix &rhs)
{
    Matrix toRet = Matrix(rhs);
    for (int i = 0; i < toRet.getRows() * toRet.getCols(); i++)
    {
        toRet.matrix[i] = ((c) * toRet.matrix[i]);
    }
    return toRet;
}

/**
 * Fills matrix elements.
 * @param s given input stream.
 * @param rhs The matrix to fill.
 * @return The input stream.
 */
std::istream &operator>>(std::istream &is, const Matrix &rhs)
{
    if (!is.good())
    {
        std::cerr << ERR_MSG_FILE << std::endl;
        exit(FAIL);
    }
    long int matSize = (long int) (rhs.getCols() * rhs.getRows());

    float readOnNum;
    int i = 0;
    while (is.read((char *) (&readOnNum), sizeof(float)))
    {
        if (i >= matSize)
        {
            std::cerr << ERR_MSG_FILE << std::endl;
            exit(FAIL);
        }
        rhs.matrix[i] = readOnNum;
        i++;
    }

    if(is.peek() != EOF || i != matSize)
    {
        std::cerr << ERR_MSG_FILE << std::endl;
        exit(FAIL);
    }
    return is;
}











