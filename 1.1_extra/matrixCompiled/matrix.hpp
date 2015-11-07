#ifndef INCLUDE_GUARD_4GETFUL_MATRIX_HPP
#define INCLUDE_GUARD_4GETFUL_MATRIX_HPP

#include <cstddef>
#include <istream>
#include <iostream>

// 991201 morfeus: optimized version, noexcept is faster
// 991231 moose:   removed noexcept from constructors, new can throw

class Matrix {
  protected:
    class MatrixRow {
      public:
        typedef std::size_t  size_type;
        typedef std::size_t index_type;
        typedef int         value_type;

      public:
        explicit MatrixRow (size_type size);

        MatrixRow (MatrixRow const& src);

        value_type      & operator[] (index_type idx) noexcept;
        value_type const& operator[] (index_type idx) const noexcept;

        MatrixRow& operator= (MatrixRow const&) = delete;

        ~MatrixRow () noexcept;

      protected:
        value_type * _data;
        size_type    _size;
    };

  public:

    typedef std::size_t  size_type;
    typedef std::size_t index_type;

  public:

    Matrix ();                        // empty matrix
    Matrix (size_type rows, size_type cols);
    Matrix (Matrix const& src);

    ~Matrix () noexcept;

    Matrix& operator= (Matrix const& rhs) noexcept;

    Matrix operator+ (Matrix const& rhs) const noexcept;
    Matrix operator- (Matrix const& rhs) const noexcept;
    Matrix operator* (Matrix const& rhs) const noexcept;

    Matrix operator* (int) noexcept;  // scalar multiplication
    Matrix operator+ (int) noexcept;  
    Matrix operator- () noexcept;

    MatrixRow&       operator[] (index_type idx) noexcept;
    MatrixRow const& operator[] (index_type idx) const noexcept;

    size_type rows () const noexcept;
    size_type cols () const noexcept;

  protected:
    MatrixRow ** _data;
    size_type    _rows;
    size_type    _cols;

    friend std::istream& operator>> (std::istream& stream, Matrix&       dst) noexcept;
    friend std::ostream& operator<< (std::ostream& stream, Matrix const& src) noexcept;
};

std::istream& operator>> (std::istream&, Matrix&       dst) noexcept;
std::ostream& operator<< (std::ostream&, Matrix const& src) noexcept;

#endif /* 4GETFUL_MATRIX_HPP */
