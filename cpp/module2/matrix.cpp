#include <iostream>

template <typename T>
class matrix
{
    T *data;
    size_t rows, columns;

public:
    matrix(size_t r, size_t c)
    {
        data = new T[r * c]();
        rows = r;
        columns = c;
    }

    ~matrix()
    {
        delete[] data;
    }

    matrix(const matrix &m)
    {
        this->rows = m.rows;
        this->columns = m.columns;
        data = new T[rows * columns];
        for (size_t i = 0; i < rows * columns; i++)
        {
            data[i] = m.data[i];
        }
    }

    matrix(matrix &&move) noexcept
    {
        this->data = move.data;
        this->columns = move.columns;
        this->rows = move.rows;
        move.rows = 0;
        move.columns = 0;
        move.data = nullptr;
    }

    matrix &operator=(const matrix &m)
    {
        if (this == &m)
            return *this;
        delete[] data;
        this->rows = m.rows;
        this->columns = m.columns;
        data = new T[rows * columns];
        for (size_t i = 0; i < rows * columns; i++)
            data[i] = m.data[i];
        return *this;
    }

    matrix &operator=(matrix &&move) noexcept
    {
        if (this == &move)
            return *this;
        delete[] data;
        this->data = move.data;
        this->columns = move.columns;
        this->rows = move.rows;
        move.rows = 0;
        move.columns = 0;
        move.data = nullptr;
        return *this;
    }

    T &at(size_t r, size_t c) const
    {
        return data[(r * columns) + c];
    }

    matrix operator*(const matrix &m)
    {
        matrix product(rows, m.columns);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < m.columns; j++)
            {
                for (size_t k = 0; k < columns; k++)
                {
                    product.at(i, j) += this->at(i, k) * m.at(k, j);
                }
            }
        }
        return product;
    }

    size_t Rows()
    {
        return rows;
    }

    size_t Columns()
    {
        return columns;
    }

    void display()
    {
        for (size_t i = 0; i < rows; i++)
        {
            std::cout << "| ";
            for (size_t j = 0; j < columns; j++)
            {
                std::cout << this->at(i, j) << " ";
            }
            std::cout << "|\n";
        }
    }
};

int main()
{
    matrix<double> m1(2, 2);
    std::cout << "Enter all the numbers of the m1 matrix in row order: \n";
    for (size_t i = 0; i < m1.Rows(); i++)
        for (size_t j = 0; j < m1.Columns(); j++)
            std::cin >> m1.at(i, j);

    matrix<double> m2(2, 2);
    std::cout << "Enter all the numbers of the m2 matrix in row order: \n";
    for (size_t i = 0; i < m2.Rows(); i++)
        for (size_t j = 0; j < m2.Columns(); j++)
            std::cin >> m2.at(i, j);

    matrix<double> m3 = m1 * m2;
    std::cout << "m1: \n";
    m1.display();
    std::cout << "m2: \n";
    m2.display();
    std::cout << "m1*m2: \n";
    m3.display();

    return 0;
}