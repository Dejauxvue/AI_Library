
#include <iostream>


#include "Jubics_crube_problem.h"
#include "AI_search_tree.h"

int main(char* argv, int argc){
	std::cout << "Hello Mars" << std::endl;

	jubics_crube::Problem_impl problem;

	AI_search_tree tree;

	tree.set_input(problem);

	std::vector<std::shared_ptr<Action>> result;

	std::cout << "depth search result: " << tree.depth_search(result)<< std::endl;


	getchar();
	return 0;
}