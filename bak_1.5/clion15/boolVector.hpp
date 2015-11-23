#ifndef BOOLARRAY
#define BOOLARRAY

#include"Vector.h"

template <>
class Vector <bool>{
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
		class bool_unsigProxy{//also bitpointer
			private:
				std::size_t targetBoolIndex;
				Vector<bool>& _boolData;
			
			public:
				bool_unsigProxy(Vector<bool> & boolData,std::size_t target);
				//set value via proxy 
				void operator=(bool const& sA);
				//Get value via proxy
				operator const bool () const;
				bool_unsigProxy& operator++();
				bool_unsigProxy& operator--();
				bool_unsigProxy operator++(int d);
				bool_unsigProxy operator--(int d);
				bool_unsigProxy operator-(int);
				bool_unsigProxy operator+(int);
				bool_unsigProxy operator+=(int);
				bool_unsigProxy operator-=(int);
				bool operator<(int);
			
		};
	
		class const_iterator : 
			public std::iterator<std::random_access_iterator_tag, bool>{	
			public:	
				
				const_iterator(const Vector<bool> & boolData,std::size_t pointIndex);
				~const_iterator();/*{}*/
				bool_unsigProxy operator*() const;
				const_iterator operator+=(int n);
				const_iterator operator-=(std::size_t n);
				bool operator==(const_iterator it);
				const_iterator& operator++();
				const_iterator& operator--();
				const_iterator operator++(int d);
				const_iterator operator--(int d);
				const_iterator operator-(std::size_t);
				const_iterator operator+(std::size_t);
				std::size_t operator-(const_iterator from);
				
				bool operator<(const const_iterator &s2);
				const_iterator(const const_iterator &);
				
				bool operator !=(const const_iterator &s2);
				
				//friend void swap(const_iterator&,const_iterator&);
				
				//friend void iter_swap(const_iterator&,const_iterator&);
			protected:
				std::size_t currentIndex;
				bool_unsigProxy bitPoint;
				
			private:
			
		};
		class iterator: public const_iterator{ ///vid ansätta värde casta om const till const_cast bort referensens
			public:
				using const_iterator::const_iterator;
				void operator=(bool Value);		
				iterator& operator=(iterator const& it);
				bool_unsigProxy& operator*();
				
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
        Vector(Vector &&) noexcept; //move
        Vector(const Vector &); 
        /*
        //copy
        Vector<T>& operator=(Vector<T> const& sA); //Assigncopy
        */
        explicit Vector(const std::size_t &);
        Vector(const std::size_t &,const bool &); 
        Vector(const std::initializer_list<bool> &);
        /* 
        std::size_t size() const ;*/
        void push_back(const bool&);
		//std::back_insert_iterator<Vector<bool>> back_inserter(Vector<bool>& c);
        const bool operator[](const std::size_t i) const;
        bool_unsigProxy operator[](const std::size_t i);
         
        
};















#endif
