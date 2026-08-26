//
// DD1388 - Lab 2: The matrix
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "T must be move-constructible");
    static_assert(std::is_move_assignable<T>::value, "T must be move-assignable");


public:
    // constructors and assignment operators
    /* TODO: Make the appropriate constructor(s) explicit 

    Explicit: Man måste kalla på en funktion för att den ska exikveras.
    Implicit: Då kan constructor kallas utan att man vill
    
    */
    explicit Matrix(); //DefaultConstructor
    explicit Matrix(size_t dim); //SquareDimensionConstructor
    explicit Matrix(size_t rows, size_t cols); //RowColConstructor
    Matrix(const std::initializer_list<T> & list); // InitListConstructor
    Matrix(const Matrix<T> & other);    // MatrixConstructor

    Matrix(Matrix<T> && other) noexcept; //MoveConstructor

    Matrix<T> & operator=(const Matrix<T> & other); // CopyConstructor
    Matrix<T> & operator=(Matrix<T> && other) noexcept; // MoveConstructor

    ~Matrix(); // Destructor //Förmodligen testad

    // accessors: Få tal man vill ha
    size_t rows() const; //RowFunction
    size_t cols() const; //ColonFunction

    // Åtkomstoperatorer
    T & operator()(size_t row, size_t col); // Få värde på (row, col) //ElementAccess
    const T & operator()(size_t row, size_t col) const; //ElementAccess

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const; //MultiplyOperator
    Matrix<T> operator+(const Matrix<T> & other) const; //AddOperator
    Matrix<T> operator-(const Matrix<T> & other) const; //SubtractOperator

    Matrix<T> operator*=(const Matrix<T> & other); //MultiplyAssignOperator
    Matrix<T> operator+=(const Matrix<T> & other); //AddAssignOperator
    Matrix<T> operator-=(const Matrix<T> & other); //SubtractAssignOperator

    // methods
    void reset(); //ResetFunction

    void insert_row(size_t row); //InsertRow
    void append_row(size_t row); //AppendRow
    void remove_row(size_t row); //RemoveRow
    void insert_column(size_t col); //InsertColumn
    void append_column(size_t col); //AppendColumn
    void remove_column(size_t col); //RemoveColumn

    // iterators
    typedef T* iterator;
    /*
    //for (auto i = v.begin(); i != v.end(); i++) {}
        auto: 
            INNAN auto:
            std::vector v;
            for (typename Vector::const_interator i = v.begin(); ...)

            Med auto:
                                    auto int x; Allocera x automatiskt på stacken
            auto i = v.begin(); Betyder "Utifrån v.begin(), lista ut vad i ska vara för typ" (omg!)

        */

    iterator begin(); //BegiIterator
    iterator end(); //EndIterator

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);  // Vet inte hur man testar

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m); // StreamOutputOperator

// functions
template<typename T>
Matrix<T> identity(size_t dim); //IdentityFunction


//
// Implementations
//

template<typename T>
Matrix<T>::Matrix()
    : m_rows(0), m_cols(0), m_capacity(0), m_vec(nullptr)
/*:  Initialize members here */ {
    // Done!
}

template<typename T>
Matrix<T>::Matrix(size_t dim)
    : m_rows(dim), m_cols(dim), m_capacity(dim*dim), m_vec(nullptr)
/*:  Initialize members here */ {
    // Done?
    this->m_vec = new T[m_capacity]();
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols), m_capacity(rows*cols), m_vec(nullptr)
/*:  Initialize members here */ {
    // Done?
    this->m_vec = new T[m_capacity]();
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
/*:  Initialize members here */ {
    // Done?
    size_t dim = std::sqrt(list.size());
    if (dim * dim != list.size()) throw std::out_of_range("List must have a square number of elements");
    this->m_rows = dim;
    this->m_cols = dim;
    this->m_capacity = list.size();
    this->m_vec = new T[m_capacity]();
    //std::copy(list.begin(), list.end(), this->m_vec);
    size_t i = 0;
    for (const auto& elem : list)
        this->m_vec[i++] = elem;
}

template<typename T> // Också copy O_O
Matrix<T>::Matrix(const Matrix<T> & other)
    : m_rows(other.m_rows), m_cols(other.m_cols), m_capacity(other.m_capacity), m_vec(nullptr) {
        this->m_vec = new T[other.m_capacity];
        for (size_t i = 0; i < other.m_capacity; i++)
            this->m_vec[i] = other.m_vec[i];

        //std::copy(other.m_vec, other.m_vec + other.m_capacity, this->m_vec);
        // FUCK STD::COPY!!! DUM DUM DUM >:(
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept
    : m_rows(other.m_rows), m_cols(other.m_cols), m_capacity(other.m_capacity), m_vec(other.m_vec) {
    other.m_vec = nullptr; // Nullify so original object doesn’t delete it
    other.m_rows = other.m_cols = other.m_capacity = 0;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    // Implementation goes here
    if (this == &other) return *this;

    delete[] this->m_vec;//delete[] m_vec;

    this->m_rows = other.m_rows;
    this->m_cols = other.m_cols;
    this->m_capacity = other.m_capacity;
    this->m_vec = new T[other.m_capacity]();

    for (size_t i = 0; i < other.m_capacity; i++)
            this->m_vec[i] = other.m_vec[i];
    //std::copy(other.m_vec, other.m_vec + other.m_capacity, this->m_vec);
    //std::copy(other.begin(), other.end(), this->m_vec);

    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    if (this != &other) { // Prevent self-move
        delete[] this->m_vec;//delete[] m_vec; // Free old memory

        // Move ownership of data
        this->m_rows = other.m_rows;
        this->m_cols = other.m_cols;
        this->m_capacity = other.m_capacity;
        this->m_vec = other.m_vec;

        // Nullify source to prevent double free
        other.m_vec = nullptr;
        other.m_rows = other.m_cols = other.m_capacity = 0;
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    // Implementation goes here
    delete[] this->m_vec;//delete[] m_vec;
    /* Minnesläcka? delete alla new() ! */
}

template<typename T>
size_t Matrix<T>::rows() const {
    // Implementation goes here
    return this->m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {
    // Implementation goes here
    return this->m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    // Implementation goes here
    if (!this->m_vec || row >= this->m_rows || col >= this->m_cols) {
        throw std::out_of_range("Attempted to access an empty matrix.");
    }
    return this->m_vec[row * this->m_cols + col];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    // Implementation goes here
    if (!this->m_vec || row >= this->rows() || col >= this->cols()) {
        throw std::out_of_range("Attempted to access an empty matrix.");
    }
    return this->m_vec[row * this->m_cols + col];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    // Implementation goes here
    if (this->m_cols != other.m_rows) {
        throw std::out_of_range("Matrix dimensions do not allow multiplication");
    }

    Matrix<T> ret(this->m_rows, other.m_cols);
    
    for (size_t r = 0; r < this->m_rows; r++) {
        for (size_t c = 0; c < other.m_cols; c++) {
            T sum = 0;
            for (size_t t = 0; t < this->m_cols; t++) {
                sum += (*this)(r, t) * other(t, c);
            }
            ret(r, c) = sum;
        }
        
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    // Implementation goes here
    if (this->m_capacity != other.m_capacity || this->m_cols != other.m_cols) {
        throw std::out_of_range("Matrix dimensions do not allow addition");
    }
    Matrix<T> res(this->rows(), this->cols());
    for (size_t i = 0; i < this->m_capacity; i++) {
        res.m_vec[i] = (*this).m_vec[i] + other.m_vec[i];
    }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    // Implementation goes here
    if (this->m_capacity != other.m_capacity || this->m_cols != other.m_cols) {
        throw std::out_of_range("Matrix dimensions do not allow subtraction");
    }
    Matrix<T> res(this->rows(), this->cols());
    for (size_t i = 0; i < this->m_capacity; i++) {
        res.m_vec[i] = (*this).m_vec[i] - other.m_vec[i];
    }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T> & other) {
    // Implementation goes here
    *this = (*this) * other;
    return *this;
    
}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T> & other) {
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols) {
        throw std::out_of_range("Matrix dimensions do not match for addition");
    }
    for (size_t i = 0; i < this->m_capacity; i++) {
        this->m_vec[i] += other.m_vec[i];
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T> & other) {
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols) {
        throw std::out_of_range("Matrix dimensions do not match for subtraction");
    }
    for (size_t i = 0; i < this->m_capacity; i++) {
        this->m_vec[i] -= other.m_vec[i];
    }
    return *this;
}

template<typename T>
void Matrix<T>::reset() {
    // Implementation goes here
    this->m_capacity = 0;
    this->m_rows = 0;
    this->m_cols = 0;
    delete[] this->m_vec;
    this->m_vec = nullptr;
}

template<typename T>
void Matrix<T>::insert_row(size_t row) { // Just den rad, försjut resten
    if (row >= this->m_rows)
        throw std::out_of_range("Out of bounds");
    this->m_capacity += this->m_cols;
    this->m_rows++;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity; i++) {
        if (i / this->m_cols == row) {
            replacement[i] = T(); // Kanske onödig
            offset++;
        } else {
            replacement[i] = this->m_vec[i - offset];
        }
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
void Matrix<T>::append_row(size_t row) { // Efter sagd rad, försjut resten
    if (row >= this->m_rows)
        throw std::out_of_range("Out of bounds");
    this->m_capacity += this->m_cols;
    this->m_rows++;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity; i++) {
        if ((i / this->m_cols) - 1 == row) {
            replacement[i] = T(); // Kanske onödig
            offset++;
        } else {
            replacement[i] = this->m_vec[i - offset];
        }
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    if (row >= this->m_rows)
        throw std::out_of_range("Out of bounds");
    this->m_capacity -= this->m_cols;
    this->m_rows--;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity + this->m_cols; i++) {
        if (i / this->m_cols != row) {
            replacement[i - offset] = this->m_vec[i];
        } else offset++;
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    if (col >= this->m_cols)
        throw std::out_of_range("Out of bounds");
    this->m_capacity += this->m_rows;
    this->m_cols++;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity; i++) {
        if (i % this->m_cols == col) {
            replacement[i] = T(); // Kanske också onödig
            offset++;
        } else {
            replacement[i] = this->m_vec[i - offset];
        }
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    if (col >= this->m_cols)
        throw std::out_of_range("Out of bounds");
    this->m_capacity += this->m_rows;
    this->m_cols++;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity; i++) {
        if ((i % this->m_cols) - 1 == col) {
            replacement[i] = T(); // Kanske också onödig
            offset++;
        } else {
            replacement[i] = this->m_vec[i - offset];
        }
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    if (col >= this->m_cols)
        throw std::out_of_range("Out of bounds");
    this->m_capacity -= this->m_rows;
    this->m_cols--;
    T* replacement = new T[this->m_capacity]();
    size_t offset = 0;
    for (size_t i = 0; i < this->m_capacity + this->m_rows; i++) {
        if (i % (this->m_cols + 1) != col) {
            replacement[i - offset] = this->m_vec[i];
        } else {
            offset++;
        }
    }
    delete[] this->m_vec;
    this->m_vec = replacement;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return m_vec;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    return m_vec + m_capacity;
}

template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m) {
    std::vector<std::vector<T>> tempMatrix;
    T value;
    size_t row = 0;
    // Read elements
    while (is >> value) {
        // Lägg till rader ibland
        if (tempMatrix.size() <= row) {
            tempMatrix.push_back(std::vector<T>());
        }
        tempMatrix[row].push_back(value);
        if (is.peek() == '\n') {
            row++;
        }
    }
    while (m.rows() < tempMatrix.size()) m.insert_row(0);
    while (m.rows() > tempMatrix.size()) m.remove_row(0);


    size_t maxCols = 0;
    for (const auto& row : tempMatrix) maxCols = std::max(maxCols, row.size());
    while (m.cols() < maxCols) m.insert_column(0);
    while (m.cols() > maxCols) m.remove_column(0);
    
    for (size_t r = 0; r < tempMatrix.size(); ++r) {
        for (size_t c = 0; c < tempMatrix[r].size(); ++c) {
            m(r, c) = tempMatrix[r][c];
        }
    }
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    // Implementation goes here
    // Ta matris och skriva ut (Pretty-print), human readble
    for (size_t r = 0; r < m.rows(); r++) {
        for (size_t c = 0; c < m.cols(); c++) {
            if (r == (m.rows() - 1) && c == (m.cols() - 1)) {
                os << m(r, c);
            } else if (c == m.cols() - 1) {
                os << m(r, m.cols() - 1) << "\n";
            } else {
                os << m(r, c) << " ";
            }
        }
    }
    return os;
}

template<typename T>
Matrix<T> identity(size_t dim) {
    Matrix<T> m(dim);
    for (size_t i = 0; i < m.rows(); i++) {
        m(i, i) = static_cast<T>(1);
    }
    return m;
}

#endif //MATRIX_H

/*
// 
Matrix a;
Matrix b = a;
Matrix c(a);

Matrix d;
d = a;


Matrix a;
Matrix b = std::move(a);
Matrix c(std::move(a));

Matrix d;
d = std::move(a);

// Undifined behavior
Matrix a;
Matrix b = std::move(a);

a(0, 0) = 1;

//OK
Matrix a;
Matrix b = std::move(a);

a = {0, 1, 2, 3};
a(0, 0) = 1;
*/