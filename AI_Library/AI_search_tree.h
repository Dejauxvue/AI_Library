#pragma once
#ifndef AI_SEARCH_TREE_H
#define AI_SEARCH_TREE_H

#include <type_traits>

#include "Tree_solvable.h"

/**
@class AI_search_tree
template class for a search tree for a template problem
*/

template<typename Problem>
class AI_search_tree
{
	static_assert(std::is_base_of<Tree_solvable, Problem>::value, "AI_search_tree needs Tree_solvable as template")
public:
	AI_search_tree();

	/**
	prepares the search tree for solving the given problem
	@param problem to solve
	*/
	void set_input(const Problem& problem){
		problem_ = problem;
	};

	/**
	tries to find a solution for the problem using depth first search
	@param [out] result vector where the result will be stored, if method return true, if it returns false, the 
				vectors content is undefined
	@return true, if a solution could be found
	*/
	bool depth_search(std::vector<Problem::Action>& result);


	~AI_search_tree();

private:
	Problem problem_;
	Problem::State cur_state_;
};

#include "AI_search_tree.hpp"

#endif AI_SEARCH_TREE_H

