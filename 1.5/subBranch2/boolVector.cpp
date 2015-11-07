#include "boolVector.hpp"

//////BOOL CASE
///Iterator const
Vector<bool>::const_iterator::const_iterator(const Vector<bool> & boolData,std::size_t pointIndex)
	: currentIndex(pointIndex)
	, _boolData(boolData){}
	
Vector<bool>::const_iterator::~const_iterator(){}

bool Vector<bool>::const_iterator::operator*() const{
	bool temp = _boolData.get_Bool(currentIndex);
	return temp;
}
Vector<bool>::const_iterator::const_iterator(const const_iterator & sA)
	: currentIndex(sA.currentIndex)
	, _boolData(sA._boolData){}


/*
Vector<bool>::iterator& Vector<bool>::iterator::operator=(iterator && sA){
	const_cast<Vector<bool>&>(_boolData) = const_cast<Vector<bool>&>(sA._boolData);
	currentIndex = sA.currentIndex;
	return *this;
}
*/





Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-=(std::size_t n){
	if(currentIndex -n >=0 && currentIndex-n <= _boolData._nActiveBit){
		currentIndex = currentIndex-n;
		return *this;
	}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}

Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+=(int n){
	int tempCurId = (int) currentIndex;
	if(tempCurId + n >= 0 && tempCurId + n <= (int) _boolData._nActiveBit){
		currentIndex = ((std::size_t) (tempCurId+n));
		return *this;
	}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}

bool Vector<bool>::const_iterator::operator==(const_iterator it){
	if (it.currentIndex == currentIndex){
		return true;
	}
	return false;
	
}

Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator++(){
	if(currentIndex+1 <= _boolData._nActiveBit){
		currentIndex++; 
		return *this;
		}
	throw std::out_of_range("bool index not in range \n");
	return *this;
}
Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator--(){
	if(currentIndex == 0){
		throw std::out_of_range("bool index not in range \n");
		return *this;}
	currentIndex--;
	return *this;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator++(int d){
	if(currentIndex==_boolData._nActiveBit){
		throw std::out_of_range("bool index not in range \n");
		return *this;
	}
	const_iterator ans = *this; 
	currentIndex++; 
	return ans;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator--(int d){
	if(currentIndex==0){
		throw std::out_of_range("bool index not in range \n");
		return *this;
	}
	const_iterator ans = *this; 
	currentIndex--; 
	return ans;
}
				
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator-(std::size_t n){
	const_iterator ans = *this;
	ans-=(n);
	return ans;
}
Vector<bool>::const_iterator Vector<bool>::const_iterator::operator+(std::size_t n){
	const_iterator ans = *this;
	ans+=(n);
	return ans;
}

std::size_t Vector<bool>::const_iterator::operator-(const_iterator from){
	return (currentIndex - from.currentIndex);
}

bool Vector<bool>::const_iterator::operator !=(const const_iterator &s2){
				if(currentIndex == s2.currentIndex){
					return false;
					}	
				return true;
				}
				
bool Vector<bool>::const_iterator::operator<(const const_iterator &s2){
	if(_boolData.get_Bool(currentIndex) < s2._boolData.get_Bool(s2.currentIndex))
		return true;
	else
		return false;
	}


/*
Vector<bool>::const_iterator& Vector<bool>::const_iterator::operator=(const_iterator const& sA){ //assigncopy
	if(this==&sA) return *this;
    _boolData = sA._boolData;
    currentIndex = sA.currentIndex;
    return *this;			
}*/








/*
///Iterator non const
Vector<bool>::iterator::iterator(Vector<bool> & boolData,std::size_t pointIndex)
	: currentIndex(pointIndex)
	, _boolData(boolData){}
*/
///Init Iterator
Vector<bool>::const_iterator Vector<bool>::begin() const{
	const_iterator tempIterator(*this,(std::size_t) 0);
	return tempIterator;
}
Vector<bool>::const_iterator Vector<bool>::end() const{
	const_iterator tempIterator(*this,_nActiveBit);
	return tempIterator;
}


Vector<bool>::iterator Vector<bool>::begin(){
	const Vector<bool> & tempConst = *this;
	iterator tempIterator(tempConst,(std::size_t) 0);
	//iterator tempIterator(*this,(std::size_t) 0);
	return tempIterator;	
}

Vector<bool>::iterator Vector<bool>::end(){
	iterator tempIterator(*this,_nActiveBit);
	return tempIterator;
}






void Vector<bool>::iterator::operator=(bool Value){
	const_cast<Vector<bool>&>(_boolData).set_Bool(currentIndex,Value);
}

Vector<bool>::iterator& Vector<bool>::iterator::operator=(iterator const& it){
	if(this==&it) return *this;
		const_cast<Vector<bool>&>(_boolData) = const_cast<Vector<bool>&>(it._boolData);
		currentIndex = it.currentIndex;
	return *this;
}


Vector<bool>::bool_unsigProxy Vector<bool>::iterator::operator*(){
	return bool_unsigProxy(const_cast<Vector<bool>&>(_boolData), currentIndex);
}













//Bool Constructor

const bool Vector<bool>::operator[](const std::size_t i) const{
	const bool temp = get_Bool(i);
	return temp;
}
Vector<bool>::bool_unsigProxy Vector<bool>::operator[](const std::size_t i){
	bool_unsigProxy tempPro(*this,i);
	return tempPro;
}



Vector<bool>::Vector()
    : _totSize(init_size)
    , _nActiveBit(0)
{
	_unsig_array = new unsigned int [init_size];
	std::cout << "default init\n";
}
Vector<bool>::Vector(const std::size_t & reqSize)
	: _totSize(reqSize/bit_p_Elt+1)
	, _nActiveBit(reqSize) {
	_unsig_array = new unsigned int[_totSize];
	std::cout << "size initilizer \n";
}

Vector<bool>::Vector(Vector && sA) noexcept
	: _unsig_array(sA._unsig_array)
	, _totSize(sA._totSize)
	, _nActiveBit(sA._nActiveBit)
{
	sA._totSize = 0;
	sA._nActiveBit = 0;
	sA._unsig_array = nullptr;	
	
}

Vector<bool>::Vector(const Vector & sA)
	: _totSize(sA._totSize)
	, _nActiveBit(sA._nActiveBit)
	{
	_unsig_array = new unsigned int[_totSize];
	for(std::size_t i = 0; i < _nActiveBit/bit_p_Elt +1 ; i++){
		_unsig_array[i] = sA._unsig_array[i];
	}
}




Vector<bool>::~Vector(){
	delete[] _unsig_array;
}

Vector<bool>::Vector(const std::size_t & reqSize, const bool & value){
	_totSize = reqSize/bit_p_Elt +1;
	_nActiveBit = reqSize;
	_unsig_array = new unsigned int[_totSize];
	std::cout << "Size initilizer with init value \n";
	//Default set all to 0
	for(std::size_t uIndex = 0; uIndex < _totSize ; uIndex ++){
			_unsig_array[uIndex] = 0;
	}
	if(value){ //Set all to "true" performimg bit op.	
		for(std::size_t boolIndex = 0; boolIndex < reqSize; boolIndex++){
			set_Bool(boolIndex,true);
		}
	}
}


//Vector<T>& Vector<bool>::operator=(Vector<T> && sA); //move assign
//Move assignment
Vector<bool>& Vector<bool>::operator=(Vector<bool> && sA){
    if(this==&sA){ return *this;}
    
	delete[] _unsig_array;
		_unsig_array = sA._unsig_array;
		_totSize = sA._totSize;
		_nActiveBit = sA._nActiveBit;
		sA._unsig_array = nullptr;
		sA._totSize = 0;
		sA._nActiveBit = 0;
    return *this;
}
Vector<bool>& Vector<bool>::operator=(Vector<bool> const& sA){//AssignCopy
	if(this==&sA) return *this;
	
	delete[] _unsig_array;
	_totSize = sA._totSize;
	_nActiveBit = sA._nActiveBit;
	_unsig_array = new unsigned int [_totSize];
	for(std::size_t i = 0; i < _nActiveBit/bit_p_Elt+1;i++){
		_unsig_array[i] = sA._unsig_array[i];
	}
	return *this;

}





//list init
Vector<bool>::Vector(const std::initializer_list<bool> & initList){
	_totSize = initList.size()/bit_p_Elt +1;
	_nActiveBit = initList.size();
	_unsig_array = new unsigned int[_totSize];
	
	std::size_t counter = 0;
    for(auto &elt : initList){
		set_Bool(counter,elt);
		counter++;
	}
}




void Vector<bool>::constFun() const{
	std::cout << "const function" << "\n";
}
void Vector<bool>::normalFun(){
	std::cout << "normal function" << "\n";
}

void Vector<bool>::set_Bool(const std::size_t & boolIndex, const bool & boolValue){
	if(boolIndex >= _nActiveBit){
        throw std::out_of_range("bool index not in range \n");}
	std::size_t uSigIndex = boolIndex / bit_p_Elt;
	std::size_t bSubIndex = boolIndex % bit_p_Elt;
	if(boolValue){
		//or - compares both, set first index to 1, then shift bsub steps. 
									//Guaratees index bSubIndex will be 1
									//if 1 is in either, that index is set to 1
		_unsig_array[uSigIndex] |= (1u << bSubIndex);
	}
	else{
		//And set to 1 only if both sides is true
								// not converts 00001 to 11110 and then and operation
		_unsig_array[uSigIndex] &= ~(1u << bSubIndex);
	}
}

bool Vector<bool>::get_Bool(const std::size_t & boolIndex) const{
	if(boolIndex >= _nActiveBit){
		throw std::out_of_range("bool index not in range \n");
	}
	std::size_t uSigIndex = boolIndex / bit_p_Elt;
	std::size_t bSubIndex = boolIndex % bit_p_Elt;
	
	const unsigned int & uSigValue = _unsig_array[uSigIndex];
	//takes out the unsig value, then shift it so the interesting 
	//bit is located at index 0, then mod 2 to determine if it is 1 or 0
	//and makes appropriate return value.
	if( (uSigValue >> bSubIndex)%2){
		return true;
	}
	return false; 
	
}

void Vector<bool>::printData() const{
	std::cout << "print raw unsigned values \n";
	for(std::size_t i = 0; i < _totSize;i++){
		std::cout << _unsig_array[i] << " ";
	}
	std::cout << std::endl;
	/*std::cout << "printing corresponding bool values\n";
	for(std::size_t i = 0; i < _nActiveBit;i++){
		std::cout << get_bool(i) <<" ";
	}
	std::cout << "\n";*/
}

void Vector<bool>::push_back(const bool & element){
    //std::cout << "pushbackar \n";
    _nActiveBit++;
    if (_nActiveBit/bit_p_Elt +1 > _totSize){
        _totSize *= size_incr_fct;
        _totSize += init_size;
        
        unsigned int * tempArray = new unsigned int[_totSize];
        for(std::size_t count = 0; count < _nActiveBit/bit_p_Elt;count++){
			tempArray[count] = _unsig_array[count];}
		if(element){tempArray[_nActiveBit/bit_p_Elt] = 1;}
		else{tempArray[_nActiveBit/bit_p_Elt] = 0;}
        delete[] _unsig_array;
        _unsig_array = tempArray;
        tempArray = nullptr;
    }
    else{
		set_Bool(_nActiveBit-1,element);
	}    
}




Vector<bool>::bool_unsigProxy::bool_unsigProxy(Vector<bool>& boolData,std::size_t target)
				: targetBoolIndex(target)
				, _boolData(boolData)
				{	}

void Vector<bool>::bool_unsigProxy::operator=(bool const& sA){
	_boolData.set_Bool(targetBoolIndex,sA);
} 

				//Get value via proxy
Vector<bool>::bool_unsigProxy::operator const bool () const{
//std::cout <<"getting value \n";
	const bool temp_value = _boolData.get_Bool(targetBoolIndex);
	return temp_value;
	
}
			

namespace std
{
    template<> 
    void swap(Vector<bool>::iterator& p1, Vector<bool>::iterator& p2){
	std::size_t sindex2 = p2.currentIndex;
	p2.currentIndex = p1.currentIndex;
	p1.currentIndex = sindex2;
	}
}

namespace std
{
	template<>
	void iter_swap(Vector<bool>::bool_unsigProxy& p1, Vector<bool>::bool_unsigProxy& p2){
	std::cout << "test \n unsigbool\n";
	//bool tempBool = *p1;
	//bool temp2Bool = *p2;
	//*p1 = temp2Bool;
	//*p2 = tempBool;
	}
}	


