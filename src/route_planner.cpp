#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model){
/* The object '&model' of class RouteModel is a reference object, a reference object can be initialized only once in the entire program. In case a reference object is present
   as an attribute in the constructor, then it needs to be initialized using initializer lists. Otherwise the reference object is already holding a garbage address and 
   it is immutable and cannot be modified to another address here inside the constructor definition 
   In the intializer list above an object(m_Model) of class RouteModel is created and assigned to the reference object &model
   */
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node   = &m_Model.FindClosestNode(end_x, end_y);
}


/* Description : This function calculates the Heuristic distance for the A* search */

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
	return node->distance(*end_node);
}


/* Description : This function finds and adds neighbouring nodes to the current search node
                 Output from this function is a set of probable paths that can be taken to reach the destination */
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
	current_node->FindNeighbors();
	for(auto neighbor : current_node->neighbors){
    	neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = RoutePlanner::CalculateHValue(neighbor);
    	open_list.push_back(neighbor);
      	neighbor->visited = true;
      	neighbor->parent = current_node;
    }
}

/* 
 * Description : this function compares two nodes for the sum(f_value) of g value(g_value) and heuristic value(h_value) :
 * Returns : True : when the node1 has a higher f_value,
 *		  False : when the node1 has the lower f_value
*/
bool Compare(const RouteModel::Node  *a, const RouteModel::Node *b) {
	float f1 = a->g_value + a->h_value; // f1 = g1 + h1
	float f2 = b->g_value + b->h_value; // f2 = g2 + h2
  	return f1 > f2; 
}

/* Description : This function selects the neighbour node for the current search node based on the lowest F value.
 * The lowest F Value signifies the minimum cost required to reach to that node, thus the fastest possible path.
 */
RouteModel::Node *RoutePlanner::NextNode() {
	std::sort(open_list.begin(),open_list.end(),Compare);
	RouteModel::Node *current_node = open_list.back();
  	open_list.pop_back();
  	return current_node;
}

/* Description : This function constructs the final path from the start position(Start Node) to the destination position(End Node).
 * The path thus constructed is the fastest possible path from a point A to point B.
 */

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while(current_node->parent != nullptr){
      path_found.push_back(*current_node);
      distance += current_node->distance(*(current_node->parent));
      current_node = current_node->parent;
    }
  	
  	path_found.push_back(*current_node);
  	   
    /* Reverse the entities to give the path found from the start_node to the end_node */
    std::reverse(path_found.begin(),path_found.end()); 
  
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


/* Description : Implementation of the A* Search Algorithm   : https://towardsdatascience.com/a-star-a-search-algorithm-eb495fb156bb
 */
void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = start_node;
  	open_list.push_back(current_node);
	current_node->visited=true;
	RoutePlanner::AddNeighbors(current_node); /* Initialize the Search */
 
	while(!open_list.empty()){
    	current_node = RoutePlanner::NextNode();
    	if(current_node == end_node){
    		m_Model.path = RoutePlanner::ConstructFinalPath(current_node);
    		break;
    	}
    	else
    	RoutePlanner::AddNeighbors(current_node);
  	}
  	if(current_node != end_node){
    	m_Model.path = {};
    }
}
