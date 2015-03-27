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
	class Action_impl : public geo_vector<int, 3>, public Action{
	public:
		Action_impl(int all) :geo_vector<int, 3>(all){};
		//using geo_vector<int, 3>::geo_vector;//not supported in vc12 ...
	};

	class State_impl :public Problem_state{
		friend class Problem_impl;
	public:
		State_impl(const State_impl& copy);

		State_impl():occupied_space_({ 5, 5, 5 }){};

		std::vector<std::shared_ptr<Action>> get_possible_actions();

		std::shared_ptr<Problem_state> state_after_action(const Action& action);

		bool is_solved();

		const State_impl& operator=(const State_impl& copy);

	private:
		Multi_dim_array<int, 3> occupied_space_;//bool for type  would be more reasonable but std::vector stores
												//bool as single bytes and therefore cannot return a reference
												//to a bool
		int cubes_count_;
		int cur_cube_index_;
		std::list<int> remaining_indices_of_movable_;	
		geo_vector<int, 3> cur_position_;
		geo_vector<int, 3> cur_direction_;
	};//class State

	class Problem_impl :public Tree_solvable{
	public:
		std::shared_ptr<Problem_state> get_start_state();
	};
}//namespace jubics_crube

#endif//#ifndef JUBICS_CRUBE_PROBLEM_H