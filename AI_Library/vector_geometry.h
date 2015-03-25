#ifndef VECTOR_GEOMETRY_H
#define VECTOR_GEOMETRY_H

template<typename Numeric, int dimension>
class geo_vector{

public:
	Numeric[dimension] data;

	Numeric opertor[](int index){
		return data[index];
	}

};
#endif// #ifndef VECTOR_GEOMETRY_H