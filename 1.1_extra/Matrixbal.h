#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"
#include <iostream>
#include <stdexcept>
/*
template <class T>
class Vector : public Vector< T > {
public:
    explicit Vector <T> (std::size_t size  = 0, T data = T()) zz: std::Vector<T>(size, data) {}
    const T& operator[](unsigned int i) const throw(std::out_of_range) {
        return this->at( i );
    }
    T& operator[](unsigned int i) throw(std::out_of_range) {
        return this->at( i );
    }    
};
*/
//	using namespace std;

class Matrix
{
 public:
    typedef unsigned int index;
    
    class matrix_row : private Vector< int >
    {
    public:
        matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator [];
    private:
        friend std::istream& operator>>( std::istream&, Matrix& ); //istream får tillgång till vector privata delar
    };
    
    //Matrix( );
    explicit Matrix(const std::size_t &,const  std::size_t &);
    //Matrix( const Matrix& );
    //Matrix(int size);
    ~Matrix( );
    Matrix& operator= ( const Matrix& ); //copy
    /*
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    std::size_t rows() const; //"get size"
    std::size_t cols() const;
    */
    //friend ostream& operator<<(ostream& os, const Date& dt);
    friend std::ostream& operator<<(std::ostream& os, const Matrix&);
    friend std::istream& operator>>(std::istream& is, const Matrix&);
 protected:
 private:
    Vector<matrix_row *> *     	m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    
    void add_row( );            // Non mandatory help function
    friend std::istream& operator>> ( std::istream&, Matrix& );
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, Matrix& );

Matrix::Matrix(const std::size_t & n_rows, const std::size_t & n_cols){
	m_rows = n_rows;
	m_cols = n_cols;
	m_vectors = new Vector<matrix_row*>(m_rows);
	for(std::size_t i = 0; i < m_rows;i++){
		matrix_row * tmp = new matrix_row(m_cols);
		(*m_vectors)[i] = tmp;//VARFÖR??? varför med parantes..?
	}
}


Matrix& Matrix::operator= ( const Matrix& src){//assignment copy
	m_rows = src.m_rows;
	m_cols = src.m_cols;
	m_vectors = new Vector<matrix_row*>(m_rows);
	for(std::size_t i = 0; i <m_rows; i++){
		(*m_vectors)[i] = (*src.m_vectors)[i];
	}
	return this*;
}


Matrix::~Matrix(){
	for(std::size_t i = 0; i < m_cols;i++){
		delete (*m_vectors)[i];
	}
	delete m_vectors;
}


//Matrix operator* ( int, const Matrix& ); <--???

#endif // MATRIX_H
