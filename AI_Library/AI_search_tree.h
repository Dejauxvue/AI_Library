#ifndef AI_SEARCH_TREE_H
#define AI_SEARCH_TREE_H

#include <type_traits>

#include "Tree_solvable.h"

/**
@class AI_search_tree
*/

class AI_search_tree
{
public:
	AI_search_tree(){};


	/**
	tries to find a solution for the problem using depth first search
	@param [out] result vector where the result will be stored, if method return true, if it returns false, the
	vectors content is undefined
	@return true, if a solution could be found
	*/
	bool depth_search(std::vector<std::shared_ptr<Action>>& result);

	/**
	prepares the search tree for solving the given problem
	@param problem to solve
	*/
	void set_input(Tree_solvable& problem){
		problem_ = std::shared_ptr<Tree_solvable>(&problem);
	};

	


	~AI_search_tree(){};

private:
	std::shared_ptr<Tree_solvable> problem_;
	std::shared_ptr<Problem_state> cur_state_;
};

#endif AI_SEARCH_TREE_H

