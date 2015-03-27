#ifndef VECTOR_GEOMETRY_H
#define VECTOR_GEOMETRY_H

#include<assert.h>

template<class Numeric, int dimension>
class geo_vector{

public:
	geo_vector<Numeric, dimension>(){};

	geo_vector(std::initializer_list<Numeric> list){
		assert(list.size() == dimension);
		int i = 0;
		for (std::initializer_list<Numeric>::iterator iter = list.begin(); iter != list.end(); iter++){
			data_[i++] = *iter;
		}
	};

	geo_vector<Numeric, dimension>(const Numeric& all){
		for (int i = 0; i < dimension; i++){
			data_[i] = all;
		}
	};

	const Numeric& operator [](int index) const{
		return data_[index];
	};

	Numeric& operator [](int index) {
		return data_[index];
	};

	/**
	computes the scalar product of this and another vector
	for more information: http://en.wikipedia.org/wiki/Dot_product
	@param other
	@return scalar product
	*/
	Numeric scalar_prod(const geo_vector & other){
		Numeric ret = 0;
		for (int i = 0; i < dimension; i++){
			ret += data_[i] * other[i];
		}
		return ret;
	}

	/**
	adds the vectors component-wise
	*/
	geo_vector<Numeric, dimension> operator+(const geo_vector<Numeric, dimension>& other){
		geo_vector<Numeric, dimension> ret;
		for (int i = 0; i < dimension; i++){
			ret[i] = data_[i] + other[i];
		}
		return ret;
	};
	

	

private:
	Numeric data_[dimension];
};
#endif// #ifndef VECTOR_GEOMETRY_H