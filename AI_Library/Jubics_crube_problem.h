#ifndef JUBICS_CRUBE_PROBLEM_H
#define JUBICS_CRUBE_PROBLEM_H

#include "vector_geometry.h"
#include "structures.h"

#include "Tree_solvable.h"

/**
	implements all the necessary interfaces for a AI_search_tree to solve a problem where 
	small cubes lined up on a string should be combined correctly to form a bigger cube
*/

namespace jubics_crube{
	/**
	at each movable position on the string, there are four possible orientations 
	but overall there are obviously 6 (one for each of the cubes side) 
	*/
	typedef int ActionT;

	class State :Problem_state<ActionT>{
	public:
		State():occupied_space_({ 5, 5, 5 }){};

		std::vector<ActionT> get_possible_actions(){
			int next_segment_length = remaining_indices_of_movable_.size() == 0 ? cubes_count_ - 1 - cur_cube_index_ : remaining_indices_of_movable_[0] - cur_cube_index_;

		};
		~State();

	private:
		Multi_dim_array<bool> occupied_space_;
		int cubes_count_;
		int cur_cube_index_;
		std::vector<int> remaining_indices_of_movable_;
		geo_vector<int, 3> cur_position_;
	};

}//namespace jubics_crube

#endif//#ifndef JUBICS_CRUBE_PROBLEM_H