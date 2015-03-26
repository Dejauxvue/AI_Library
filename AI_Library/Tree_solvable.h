#ifndef TREE_SOLVABLE_H
#define TREE_SOLVABLE_H

#include <memory>
#include <vector>

	/**
	@class Problem_state
	@brief	interface for the State of Tree_solvable the template parameter specifies the type of the Action
			based on which a state transition is performed
	*/
	template<typename ActionT>
	class Problem_state{

		typedef ActionT Action;

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
		virtual std::vector<Action> get_possible_actions() = 0;


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
	template<typename ActionT, typename StateT>
	class Tree_solvable
	{
		typedef StateT State;
		typedef ActionT Action;

		static_assert(std::is_base_of<Problem_state<Action>, State>::value, "State of the Tree_solvable must match the specified Action");
	public:
		virtual std::shared_ptr<StateT> get_start_state();
	};

#endif//#ifndef TREE_SOLVABLE_H