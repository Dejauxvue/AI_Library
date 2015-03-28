#include <stack>
#include <iostream>

#include "AI_search_tree.h"

bool AI_search_tree::depth_search(std::list<std::shared_ptr<Action>>& result){
	result = std::list<std::shared_ptr<Action>>();
	std::stack<std::shared_ptr<Problem_state>> state_stack;
	std::stack<std::list<std::shared_ptr<Action>>> possibilities_stack;
	state_stack.push(problem_->get_start_state());
	possibilities_stack.push(state_stack.top()->get_possible_actions());

	while (!state_stack.empty()){
		std::cout << "state_stack.size(): " << state_stack.size() << std::endl;
		std::cout << "possibilities_stack.size(): " << possibilities_stack.size() << std::endl;
		if (state_stack.top()->is_solved()){
			return true;
		}
		if (possibilities_stack.top().empty()){
			possibilities_stack.pop();
			state_stack.pop();
			if (!result.empty()){
				result.erase(--result.end());
			}
			continue;
		}
		std::shared_ptr<Action> current_action = possibilities_stack.top().front();
		std::shared_ptr<Problem_state> next_state = state_stack.top()->state_after_action(*current_action);
		possibilities_stack.top().erase(possibilities_stack.top().begin());
		if (next_state){
			state_stack.push(next_state);
			possibilities_stack.push(next_state->get_possible_actions());
		}
		else{
			continue;
		}
		result.push_back(possibilities_stack.top().front());
		
	}
	return false;
}