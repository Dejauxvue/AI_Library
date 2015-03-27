#ifndef TREE_SOLVABLE_H
#define TREE_SOLVABLE_H

#include <memory>
#include <vector>

/**
@class Action
@brief base class for all actions that can be performed in a problem
*/
class Action{
public:
	virtual void blub(){};//virtual function to force polymorphical behaviour
};

/**
@class Problem_state
@brief	interface for the State of Tree_solvable the template parameter specifies the type of the Action
based on which a state transition is performed
*/
class Problem_state{

public:
	/**
	@brief this method is used to check wether the goal is reached and the problem is solved
	returns true if and only if the current state is a state where the problem is solved
	*/
	virtual bool is_solved() = 0;

	/**
	@brief this method is used to find all available options and accordingly should return
	all the possible Actions that can be performed from the current state
	*/
	virtual std::vector<std::shared_ptr<Action>> get_possible_actions() = 0;


	/**
	@brief will be called in the process of finding a solution and should return a pointer to the state,
	the problem will be in after applying the specified Action

	@param action Action to apply to the current state

	@return pointer to the following state
	*/
	virtual std::shared_ptr<Problem_state>  state_after_action(const Action& action) = 0;
};



/**
@class Tree_solvable
@brief interface for a problem that can be solved using an AI_search_tree
the template paramter ist the type of the Action sequence that should be computed
*/
class Tree_solvable
{
public:
	virtual std::shared_ptr<Problem_state> get_start_state() = 0;
};

#endif//#ifndef TREE_SOLVABLE_H