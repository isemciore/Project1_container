//
// Created by ezhang on 2015-10-15.
//

#ifndef THREADSAFE_SAFEVECTPAR_HPP
#define THREADSAFE_SAFEVECTPAR_HPP
#include "Vector.hpp"
#include <mutex>
#include <thread>



template <class T>
class SafeVectPar : public Vector<T>{
public:
    using Vector<T>::Vector;
    void safe_swap(std::size_t from, std::size_t to);
    explicit SafeVectPar(); //def init
    ~SafeVectPar(); //destruct
    SafeVectPar(const SafeVectPar<T> &); //copy
    SafeVectPar(SafeVectPar<T> &&); //move
    SafeVectPar<T>& operator=(SafeVectPar<T> && sA); //move assign
    SafeVectPar<T>& operator=(SafeVectPar<T> const& sA); //Assigncopy
    explicit SafeVectPar(const std::size_t &);
    SafeVectPar(const std::size_t &,const T &);
    SafeVectPar(const std::initializer_list<T> &);


    void push_back(const T & element);
    void insert(const std::size_t &,const T &);

private:
    std::mutex** uniqueLocker = new std::mutex*[32];
    std::size_t initSize = 32;
    std::size_t  nAvailableLocks = 0;
    void generateNewLocks(std::size_t);
    void deleteAllLocks();
};


template<class T>
void SafeVectPar<T>::safe_swap(std::size_t from, std::size_t to){
    if(from == to){
        return;
    }
    if(from > to){
        std::size_t temp = to;
        to = from;
        from = temp;
    }
    while(!(*uniqueLocker[from]).try_lock());
    while(!(*uniqueLocker[to]).try_lock());
    this->unsafeSwap(from,to);
    uniqueLocker[to]->unlock();
    uniqueLocker[from]->unlock();
}
template<class T>
void SafeVectPar<T>::generateNewLocks(size_t t){
    deleteAllLocks();
    nAvailableLocks = t;
    uniqueLocker = new std::mutex*[t];
    for(std::size_t i = 0; i < t; i++){
        uniqueLocker[i] = new std::mutex;
    }

}
template<class T>
void SafeVectPar<T>::deleteAllLocks() {
    for (std::size_t i = 0; i < nAvailableLocks; i++) {
        delete uniqueLocker[i];
    }
    delete[] uniqueLocker;
    nAvailableLocks = 0;

}

template <class T>
SafeVectPar<T>::SafeVectPar() : Vector<T>(){
    generateNewLocks(initSize);
}


template <class T>
SafeVectPar<T>::~SafeVectPar() {
    //Vector<T>::~Vector();
    deleteAllLocks();
}


template <class T>
SafeVectPar<T>::SafeVectPar(const SafeVectPar<T> &par) : Vector<T>(par) {
    generateNewLocks(par.capacity());
}

template <class T>
SafeVectPar<T>::SafeVectPar(SafeVectPar<T> &&par) : Vector<T>(std::move(par))  {
    generateNewLocks(par.capacity());
}

template <class T>
SafeVectPar<T>::SafeVectPar(const size_t &t) : Vector<T>(t) {
    generateNewLocks(t);
}

template <class T>
SafeVectPar<T>::SafeVectPar(const size_t &t, const T &t1): Vector<T>(t,t1) {
    generateNewLocks(t);
}

template <class T>
SafeVectPar<T>::SafeVectPar(const std::initializer_list<T> &list) : Vector<T>(list) {
    generateNewLocks(list.size());
}


template <class T>
SafeVectPar<T>& SafeVectPar<T>::operator=(SafeVectPar<T> &&sA) {
    generateNewLocks(sA.size());
    Vector<T>::operator=(std::move(sA));
    return *this;
}

template <class T>
SafeVectPar<T>& SafeVectPar<T>::operator=(SafeVectPar<T> const &sA) {
    Vector<T>::operator=(sA);
    generateNewLocks(sA.size());
    return *this;
}


template<class T>
void SafeVectPar<T>::push_back(const T & element) {
    Vector<T>::push_back(element);
    if (Vector<T>::size() > nAvailableLocks){
        generateNewLocks(nAvailableLocks*2+1);
    }

}

template<class T>
void SafeVectPar<T>::insert(const std::size_t & size,const T & elt){
    Vector<T>::insert(size,elt);
    if ( Vector<T>::size() > nAvailableLocks){
        generateNewLocks(nAvailableLocks*2+1);
    }
}






#endif //THREADSAFE_SAFEVECTPAR_HPP

