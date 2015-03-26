#ifndef JUBICS_CRUBE_PROBLEM_H
#define JUBICS_CRUBE_PROBLEM_H

#include <list>

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
	typedef geo_vector<int,3> ActionT;

	class State_impl :Problem_state<ActionT>{
	public:
		State_impl():occupied_space_({ 5, 5, 5 }){};

		std::vector<ActionT> get_possible_actions();

		std::shared_ptr<Problem_state<ActionT>> state_after_action(const ActionT& action);

		bool is_solved();

	private:
		Multi_dim_array<bool> occupied_space_;
		int cubes_count_;
		int cur_cube_index_;
		std::list<int> remaining_indices_of_movable_;	
		geo_vector<int, 3> cur_position_;
		geo_vector<int, 3> cur_direction_;
	};//class State

	class Problem_impl :Tree_solvable<ActionT, State_impl>{
	public:
		std::shared_ptr<State_impl> get_start_state();
	};
}//namespace jubics_crube

#endif//#ifndef JUBICS_CRUBE_PROBLEM_H