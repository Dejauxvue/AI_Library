#include "Jubics_crube_problem.h"

namespace jubics_crube{

	std::vector<ActionT> State_impl::get_possible_actions(){
		std::vector<ActionT> ret;
		ret.reserve(6);

		ActionT base_action0(-1);
		for (int x = 0; x < 2; x++){
			ActionT base_action1 = base_action0 + ActionT({ x, 0, 0 });
			for (int y = 0; y < 2; y++){
				ActionT base_action2 = base_action1 + ActionT({ 0, y, 0 });
				for (int z = 0; z < 2; z++){
					ActionT final_action = base_action2 + ActionT({ 0, 0, z });
					if (!final_action.scalar_prod(cur_direction_))//only add, if action vector is orthogonal to direction
					{
						ret.push_back(final_action);
					}
				}
			}
		}
		return ret;
	}

	std::shared_ptr<Problem_state<ActionT>> State_impl::state_after_action(const ActionT& action){
		std::shared_ptr<Problem_state<ActionT>> ret(new State_impl());
		State_impl& ret_ref = *static_cast<State_impl*>(ret.get());
		ret_ref = *this;

		int next_segment_length;
		if (ret_ref.remaining_indices_of_movable_.size() == 0){
			next_segment_length = cubes_count_ - 1 - cur_cube_index_;
		}
		else
		{
			next_segment_length = ret_ref.remaining_indices_of_movable_.front() - cur_cube_index_;
			ret_ref.remaining_indices_of_movable_.pop_front();
		}


		geo_vector<int, 3>& temp_pos = ret_ref.cur_position_;
		for (int i = 0; i < next_segment_length; i++){
			temp_pos = temp_pos + action;
			for (unsigned int j = 0; j < 3; j++){//if new position exceeds the bounds
				if (temp_pos[i] < 0 || temp_pos[i] >= 5) return std::shared_ptr<Problem_state<ActionT>>();
			}
			bool& space = ret_ref.occupied_space_.at_vec(temp_pos);
			if (space)//if already occupied space is filled, the action does not provide a valid state
			{
				return std::shared_ptr<Problem_state<ActionT>>();
			}
			space = true;
		}
		ret_ref.cur_cube_index_ += next_segment_length;
		ret_ref.cur_direction_ = action;

	}

	bool State_impl::is_solved(){
		if (cubes_count_ != cur_cube_index_ || !remaining_indices_of_movable_.empty()){//if not all cubes used, the result cannot be correct
			return false;
		}

		//find first occupied space since the cube must begin there
		for (unsigned int x = 0; x < occupied_space_.get_dimensions()[0]; x++)
		for (unsigned int y = 0; y < occupied_space_.get_dimensions()[1]; y++)
		for (unsigned int z = 0; z < occupied_space_.get_dimensions()[2]; z++)
		{
			if (occupied_space_.at({ x, y, z })){
				if (x >= 3 || y >= 3 || z >= 3){//the region is too small to contain the required cube
					return false;
				}

				//check if the occupied region is a 3x3x3 cube
				for (unsigned int xk = x; xk < x + 3; xk++)
				for (unsigned int yk = y; yk < y + 3; yk++)
				for (unsigned int zk = z; zk < z + 3; zk++)
				{
					if (!occupied_space_.at({ x, y, z })){
						return false;
					}
				}
				return true;
			}

		}
	}

	std::shared_ptr<State_impl> Problem_impl::get_start_state(){
		std::shared_ptr<State_impl> ret(new State_impl());

	}
}//namespace jubics_crube