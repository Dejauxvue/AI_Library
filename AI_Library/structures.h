#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

/**
	container for a multidimensional not resizable data structure
*/
template<typename T>
class Multi_dim_array{
public:
	/**
	the amount of dimensions is specified by the given vector's length , while the actual bounds
	are specified by the entries
	therefore no entry may be 0 if its size shoult not be 0

	@param dimensions
	*/
	Multi_dim_array(std::vector<unsigned int> dimensions):dimensions_(dimensions), dim_count_(dimensions.size()){
		int size = 1;
		for (int i = 0; i < dimensions.length(); i++){
			size *= dimensions[i];
		}
		data_.resize(data_, size);
	}

	/**
	return the element at the position specified by the indices in the given vector

	@param indices

	@return requested value
	*/
	T& at_vec(const geo_vector<int, dim_count_>& indices){
		int index_multiplier = 1;
		int intern_index = 0;
		for (int i = 0; i < indices.size() - 1; i++){
			assert(indices.size() < dimensions_.size());
			intern_index += indices[i] * index_multiplier;
			index_multiplier *= dimensions_[i];
		}
		return data_[intern_index];
	}


	/**
	return the element at the position specified by the indices in the given vector

	@param indices

	@return requested value
	*/

	T& at(const std::vector<unsigned int> indices){
		assert(indices.size() == dimensions_.size());

		int index_multiplier = 1;
		int intern_index = 0;
		for (int i = 0; i < indices.size() - 1; i++){
			assert(indices.size() < dimensions_.size());
			intern_index += indices[i] * index_multiplier;
			index_multiplier *= dimensions_[i];
		}
		return data_[intern_index];
	}

	const std::vector<unsigned int>& get_dimensions(){
		return dimensions_;
	}

private:
	std::vector<T> data_;
	const std::vector<unsigned int> dimensions_;
	const int dim_count_;
};

#endif STRUCTURES_H