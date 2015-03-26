#ifndef VECTOR_GEOMETRY_H
#define VECTOR_GEOMETRY_H

template<typename Numeric, int dimension>
class geo_vector{

public:
	geo_vector(){};

	geo_vector(std::initializer_list<Numeric> list){
		assert(list.size() = dimension, 
			"list for initialization of geo_vector must have same size as vector's dimension");
		int i = 0;
		for (std::initializer_list<Numeric>::iterator iter = list.begin(); iter != list.end(); iter++){
			data_[i++] = *iter;
		}
	};

	geo_vector(const Numeric& all){
		for (int i = 0; i < dimensions; i++){
			data_[i] = all;
		}
	};

	/**
	computes the scalar product of this and another vector
	for more information: http://en.wikipedia.org/wiki/Dot_product
	@param other
	@return scalar product
	*/
	Numeric scalar_prod(const geo_vector<Numeric, dimension> & other){
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
	

	Numeric& operator[](int index){
		return data_[index];
	};

private:
	Numeric data_[dimension];
};
#endif// #ifndef VECTOR_GEOMETRY_H