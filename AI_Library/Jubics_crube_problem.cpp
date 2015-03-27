#include "Jubics_crube_problem.h"

namespace jubics_crube{

	std::vector<std::shared_ptr<Action>> State_impl::get_possible_actions(){
		std::vector<std::shared_ptr<Action>> ret;
		ret.reserve(6);

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 2; j++){//all 6 possible directions
				Action_impl final_action(0);
				final_action[i] = 2 * j - 1;
				if (!final_action.scalar_prod(cur_direction_))//only add, if action vector is orthogonal to direction
				{
					ret.push_back(std::shared_ptr<Action>(&final_action));
				}
			}
					
		}
		return ret;
	}

	std::shared_ptr<Problem_state> State_impl::state_after_action(const Action& action){
		const Action_impl& ref_action = dynamic_cast<const Action_impl&>(action);
		std::shared_ptr<Problem_state> ret(new State_impl());
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
			temp_pos = temp_pos + ref_action;
			for (unsigned int j = 0; j < 3; j++){//if new position exceeds the bounds
				if (temp_pos[i] < 0 || temp_pos[i] >= 5) return std::shared_ptr<Problem_state>();
			}
			int& space = ret_ref.occupied_space_.at_vec(temp_pos);
			if (space)//if already occupied space is filled, the action does not provide a valid state
			{
				return std::shared_ptr<Problem_state>();
			}
			space = true;
		}
		ret_ref.cur_cube_index_ += next_segment_length;
		ret_ref.cur_direction_ = ref_action;

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

	std::shared_ptr<Problem_state> Problem_impl::get_start_state(){
		std::shared_ptr<State_impl> ret(new State_impl());
		ret->cur_cube_index_ = -1;
		ret->cubes_count_ = 9;
		ret->cur_position_ = geo_vector<int, 3>({ 2, 2, 1 });
		ret->cur_direction_ = geo_vector<int, 3>({ 0, 0, 1 });
		for (unsigned int x = 0; x < ret->occupied_space_.get_dimensions()[0]; x++)
		for (unsigned int y = 0; y < ret->occupied_space_.get_dimensions()[1]; y++)
		for (unsigned int z = 0; z < ret->occupied_space_.get_dimensions()[2]; z++){
			ret->occupied_space_.at({ x, y, z }) = false;
		}
		ret->remaining_indices_of_movable_ = std::list<int>({ 2, 4, 6, 7, 8, 9, 10, 11, 13, 15, 17, 18, 20, 22, 24, 25 });
		return ret;
	}

	const State_impl& State_impl::operator=(const State_impl& copy){

		occupied_space_ = copy.occupied_space_;
		cubes_count_ = copy.cubes_count_;
		cur_cube_index_ = copy.cur_cube_index_;
		remaining_indices_of_movable_ = copy.remaining_indices_of_movable_;
		cur_position_ = copy.cur_position_;
		cur_direction_ = copy.cur_direction_;
		return copy;
	}
}//namespace jubics_crube