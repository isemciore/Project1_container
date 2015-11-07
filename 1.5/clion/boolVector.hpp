#ifndef BOOLARRAY
#define BOOLARRAY

#include "Vector.h"
template <>
class Vector<bool>{
	private:
		unsigned int * _unsig_array;
		std::size_t _totSize;
        std::size_t _nActiveBit;
        const static std::size_t init_size = 1; //init size
        const static int size_incr_fct = 2;   //Multi inc size
        const static std::size_t bit_p_Elt = 32;//bits per unsig
        void set_Bool(const std::size_t &, const bool &);
		bool get_Bool(const std::size_t &) const;
        
	public:
		typedef bool value_type;
		typedef long ptrdiff_t;
		//typedef bool& reference;
		//typedef bool* pointer;

		class bool_unsigProxy{//also bitpointer
			public:
				std::size_t targetBoolIndex;
			private:
				Vector<bool>& _boolData; //when modifiy const cast away
			
			public:
				friend void swap(Vector<bool>::bool_unsigProxy& buP1, Vector<bool>::bool_unsigProxy& buP2);
				bool_unsigProxy(Vector<bool> & boolData,std::size_t target);
				//set value via proxy
				void operator=(bool const& sA);
				~bool_unsigProxy();
				std::size_t getTargetIndex();
				//Get value via proxy
				bool_unsigProxy(const bool_unsigProxy &);
				operator const bool () const;
				bool_unsigProxy& operator++();
				bool_unsigProxy& operator--();
				bool_unsigProxy operator++(int d);
				bool_unsigProxy operator--(int d);
				bool_unsigProxy operator-(int);
				bool_unsigProxy operator+(int);
				bool_unsigProxy& operator+=(int);
				bool_unsigProxy& operator-=(int);
				bool operator<(const bool_unsigProxy &) const;
				bool operator==(bool_unsigProxy);
				//ptrdiff_t operator-(bool_unsigProxy&);
				bool_unsigProxy& operator=(const bool_unsigProxy&);
				bool_unsigProxy& operator=(bool_unsigProxy && source);

		};
	
		class const_iterator : 
			public std::iterator<std::random_access_iterator_tag, bool>{	
			public:	
				
				const_iterator(const Vector<bool> & boolData,std::size_t pointIndex);
				~const_iterator();/*{}*/
				bool_unsigProxy operator*() const;
				const_iterator& operator+=(int n);
				const_iterator& operator-=(int n);
				//bool operator==(const_iterator it);
				const_iterator& operator++();
				const_iterator& operator--();
				const_iterator operator++(int d);
				const_iterator operator--(int d);
				const_iterator operator-(int);
				const_iterator operator+(int);
				ptrdiff_t operator-(const_iterator from);
				//std::size_t getTargetIndex() const;

			 	const_iterator(bool_unsigProxy bitPoint, std::size_t pointIndex);
				bool operator<(const const_iterator &s2) const;
				const_iterator(const const_iterator &);
				bool operator !=(const const_iterator &s2);
				bool operator ==(const const_iterator &s2);
				//friend void swap(const_iterator&,const_iterator&);
				void getIndex();//DEBUG PURPOSE
				//friend void iter_swap(const_iterator&,const_iterator&);

			protected:
				bool_unsigProxy bitPoint;
				
			private:
			
		};
		class iterator: public const_iterator{
			public:
				void operator=(bool Value);
				bool_unsigProxy& operator*();
				iterator& operator=(const iterator&);
				//friend void swap(Vector<bool>::iterator&, Vector<bool>::iterator&);
				iterator operator+(int i);//ska väl inte behöva overloada allt?
				iterator& operator++();//annars något = iterator +1; något blir const iterator
				iterator operator++(int);
				iterator& operator--();
				iterator operator--(int d);
				iterator operator-(int);
				ptrdiff_t operator-(iterator from);
				using const_iterator::const_iterator;
			private:

		};

		const_iterator begin() const;
		const_iterator end() const;
		iterator begin();
		iterator end();
		void printData() const;
		explicit Vector(); //def init
        ~Vector(); //destruct
        Vector<bool>& operator=(Vector<bool> && sA); //move assign
        Vector<bool>& operator=(Vector<bool> const& sA);
        Vector(Vector<bool> &&) noexcept; //move
        Vector(const Vector<bool> &); //copy
        explicit Vector<bool>(const std::size_t &);
        Vector(const std::size_t &,const bool &);
        Vector(const std::initializer_list<bool> &);

        std::size_t size() const;
        void push_back(const bool&);
		const bool operator[](const std::size_t i) const;
        bool_unsigProxy operator[](const std::size_t i);
         
        
};














#endif
