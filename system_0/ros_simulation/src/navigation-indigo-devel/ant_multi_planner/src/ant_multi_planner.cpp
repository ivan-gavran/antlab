#include <pluginlib/class_list_macros.h>
#include <multi_robot_move/multi_planner_base.h>
#include <ant_multi_planner/ant_multi_planner.h>
#include <ant_multi_planner/primitive.h>
#include <ant_multi_planner/readinputs.h>
#include <ant_multi_planner/writeconstraints.h>
#include <ant_multi_planner/extractoutput.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <csignal>


using namespace std;

PLUGINLIB_EXPORT_CLASS(ant_multi_planner::AntMultiPlanner, multi_planner_base::MultiPlanner)

namespace ant_multi_planner {
	AntMultiPlanner::AntMultiPlanner() : initialized_(false)
	{
		ros::NodeHandle private_nh("~");
		ROS_ERROR("AntMultiPlanner constructor");


		string default_value = "240";
		string primitives_filename_default_value= "primitive_movements_manhattan.txt";
		private_nh.param("ant_multi_planner/path_cost_tolerance", multiPathCostTolerance, 5.0);
		private_nh.param("ant_multi_planner/planning_patience", z3TimeoutInSeconds, default_value);
		private_nh.param("ant_multi_planner/final_optimization", final_smt_cost_optimization, false);
		private_nh.param("ant_multi_planner/primitives", primitives_filename, primitives_filename_default_value);
		double testParam;
		private_nh.setParam("ant_multi_planner/testParam", 1.0);
		// put this to ros params
		static_files_folder = "src/multiple_robots_stage/static_files_folder/";
		system_config_files_folder = "../config/";
		initialize();
	}
	
	void AntMultiPlanner::initialize()
	{
		if(!initialized_){
			  cout<<multiPathCostTolerance<<endl;
			  cout<<z3TimeoutInSeconds<<endl;
			  cout<<final_smt_cost_optimization<<endl;
			  cout<<primitives_filename<<endl;
		      initialized_ = true;
		      boost::property_tree::ptree root;
		      boost::property_tree::read_json((system_config_files_folder+"cnf.json").c_str(), root);

		      //how many times should implan map be coarser than the original
		      map_scale =root.get<double>("map_scale", 200);
		      map_width = root.get<double>("map_width", 200);
		      map_resolution = root.get<double>("resolution",200);
		      std::cout<<map_scale<<" "<<map_width<<endl;
		      std::cout<<static_files_folder+primitives_filename<<endl;
		      readPrimitives(primitives, static_files_folder+primitives_filename);
		      ostringstream os;
		      for (int i = 0; i < primitives.size();++i){
		    	  os<<primitives[i].get_pos_f().x;
		    	  cout<<os.str()<<endl;
		      }

		      readDimension(dimension, static_files_folder+"dimension.txt");
		      readPositions(obstacles, static_files_folder+"obstacle.txt");
		      readPositionsWithCost(alwaysEventuallyFreeObstacles, static_files_folder+"dynamic_obstacles_always_eventually.txt");
		      for( vector<position_with_cost>::iterator vi = alwaysEventuallyFreeObstacles.begin(); vi!= alwaysEventuallyFreeObstacles.end(); ++vi )
		      {
		    	  cout<<"reading position----------------------"<<endl;
		    	  position_with_cost pos = *vi;
		    	  cout<<"location ("<<pos[0]<<", "<<pos[1]<<") has cost of "<<pos[2]<<endl;
//		    	  pos_2d pos2d_format;
//		    	  pos2d_format.x  = pos[0];
//		    	  pos2d_format.y = pos[1];
//		    	  position p = metersToImplanUnits(pos2d_format);
//		    	  pos[0] = p.x;
//		    	  pos[1] = p.y;
//		    	  position_with_cost pos2 = *vi;
//		    	  cout<<"location ("<<pos2[0]<<", "<<pos2[1]<<") has cost of "<<pos2[2]<<endl;
//
//		      }
		      }


		     
		    }
		    else
		      ROS_WARN("This planner has already been initialized... doing nothing");
	}
	position AntMultiPlanner::metersToImplanUnits(pos_2d pos){
		  ROS_WARN("transformation");
		  position p;
		  ostringstream os, os1;
		  double IMPLAN_UNIT_SIZE = map_resolution * map_scale;
		  double IMPLAN_MAP_WIDTH = map_width;
		  os <<"received position ("<< pos.x<<", "<<pos.y<<") in meters";
		  cout<<os.str()<<endl;

		  p.x = round(pos.x / IMPLAN_UNIT_SIZE);
		  os << p.x;
		  cout<<os.str()<<endl;
		  p.y = round(IMPLAN_MAP_WIDTH - pos.y / IMPLAN_UNIT_SIZE);
		  os1<<"transformed it in ("<<p.x<<", "<<p.y<<") in implan units";
		  cout<<os1.str()<<endl;
		  ROS_WARN("transformation finished");
		  return p;
	  }




	  pos_2d AntMultiPlanner::implanUnitsToMeters(position pos){
		  pos_2d p;
		  ostringstream os, os1;
		  double IMPLAN_UNIT_SIZE = map_resolution * map_scale;
		  double IMPLAN_MAP_WIDTH = map_width;
		  p.x = pos.x * IMPLAN_UNIT_SIZE;
		  p.y = (IMPLAN_MAP_WIDTH - pos.y) * IMPLAN_UNIT_SIZE;
		  os <<"received position ("<< pos.x<<", "<<pos.y<<") in implan units";
		  os1<<"transformed it in ("<<p.x<<", "<<p.y<<") in meters";
		  cout<<os.str()<<endl;
		  cout<<os1.str()<<endl;
		  return p;

	  }

  int AntMultiPlanner::findTheGreatestManhattanDistance(pos_vec_t initpos, pos_vec_t finalpos)
	{
		int theGreatest = 0;
		for( int i = 0; i < finalpos.size(); ++i )
		{
			int finalposShortestDistance = -1;
			for( int j = 0; j < initpos.size(); ++j )
			{

				int candidateValue = abs(initpos[j].x-finalpos[i].x) + abs(initpos[j].y - finalpos[i].y);

				if (finalposShortestDistance == -1 || candidateValue < finalposShortestDistance )
				{
					finalposShortestDistance = candidateValue;
				}
			}
			cout<<"finalposShortestDistance "<<finalposShortestDistance<<endl;
			if (finalposShortestDistance > theGreatest)
				theGreatest = finalposShortestDistance;
		}
		return theGreatest;
	}

	void AntMultiPlanner::createWorkspace(dimension_t dimension, pos_vec_t initposition, pos_vec_t finalposition, int iteration, float cost, workspace_t &workspace)
	{
	  unsigned int count;

	  workspace.length_x = dimension.length_x;
	  workspace.length_y = dimension.length_y;
	  workspace.number_of_robots = initposition.size();
	  workspace.pos_start.clear();
	  workspace.pos_end.clear();
	  for (count = 0; count < workspace.number_of_robots; count++)
	  {
	    workspace.pos_start.push_back(initposition[count]);
	  }
	  for (count = 0; count < finalposition.size(); count++)
	  {
	    workspace.pos_end.push_back(finalposition[count]);
	  }
	  workspace.number_of_points = iteration;
	  ostringstream ss;
	  ss << cost;
	  string str(ss.str());
	  workspace.total_cost = str;
	}

	void AntMultiPlanner::generateZ3File(prim_vec_t primitives, pos_vec_t obstacles, vector<position_with_cost> alwaysEventuallyFreeObstacles, workspace_t workspace)
	{
	  ofstream ofp;
	  string constraints_file = static_files_folder+"constraints.smt2";
	  cout<<constraints_file<<" ----------------------------"<<endl;
	  ofp.open(constraints_file.c_str());

	  declareVariables(ofp, workspace);
	  ofp << endl;

	  writeInitialLocationConstraints(ofp, workspace);
	  ofp << endl;


	  writeFinalDestinationCoverageConstraints(ofp, workspace);
	  ofp << endl;

	  writeAlwaysEventuallyConstraints(ofp, alwaysEventuallyFreeObstacles);
	  ofp<<endl;
	  writeObstacleConstraints(ofp, obstacles, workspace);
	  ofp << endl;

	  writeTransitionConstraints(ofp, primitives, obstacles, workspace);
	  ofp << endl;


	  writeCostConstraint(ofp, workspace);
	  ofp << endl;

	  ofp << "(check-sat)" << endl;
	  //ofp << "(get-model)" << endl;
	  ofp << endl;

	  writeOutputConstraints(ofp, workspace);
	  ofp << endl;

	  ofp.close();
	}

	void AntMultiPlanner::generateTrajectories(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos, pos_vec_t finalpos, int max_length)
	{
	  unsigned int count;
	  workspace_t workspace;

	  float max_total_cost, min_total_cost, current_cost;

	  ifstream ifp;
	  string line;
	  bool sat_flag;
          string f_output;
          
          f_output = static_files_folder+"z3_output";
	  count = findTheGreatestManhattanDistance(initpos, finalpos);
	  while (count <= max_length)
	  {
	    if (count == max_length)
	      createWorkspace(dimension, initpos, finalpos, count, finalpos.size() * 1000, workspace);
	    else
	      createWorkspace(dimension, initpos, finalpos, count, 1000, workspace);
	    //writeWorkspace(workspace);

	    generateZ3File(primitives, obstacles, alwaysEventuallyFreeObstacles, workspace);
	    system(("z3 "+static_files_folder+"constraints.smt2 > "+ f_output).c_str());

	    ifp.open(f_output.c_str());
	    getline(ifp, line);
	    ifp.close();
	    cout << endl << "$$$$$$$$ " << count << " " << line << endl;

	    if (line == "unsat")
	    {
	      count = count + 5;
	      continue;
	    }
	    else
	    {
	      max_total_cost = extractTrajectoryCostInformation(f_output);
	      min_total_cost = 0;
	      current_cost = (max_total_cost + min_total_cost) / 2;
	      system(("mv " + static_files_folder+ "z3_output "+ static_files_folder + "z3_output_sat").c_str());
	    }

	    cout << endl;
	    cout << "max_total_cost = " << max_total_cost << endl;
	    cout << "min_total_cost = " << min_total_cost << endl;
	    cout << "current_cost  = " << current_cost << endl;
	    //ROS_ERROR("multi path cost tolerance variable %lf", multiPathCostTolerance);

	    if( final_smt_cost_optimization == true ){
			while (max_total_cost - min_total_cost > multiPathCostTolerance && max_total_cost - count > 10)
			{
			  /*
			   * adding current_cost as the fourth argument. the reason is not to limit the search to only `count` number of steps. this is due to
			   * added weights to some steps (which causes a shorter path to be more expensive than the longer one).
			   * */

			  int countAccountingForWeights = ceil(current_cost);

			  //createWorkspace(dimension, initpos, finalpos, countAccountingForWeights, current_cost, workspace);

			  //this version is without accounting for Weights
			  createWorkspace(dimension, initpos, finalpos, count, current_cost, workspace);
			  //writeWorkspace(workspace);

			  generateZ3File(primitives, obstacles, alwaysEventuallyFreeObstacles, workspace);
			  system(("z3 -T:"+z3TimeoutInSeconds+" "+static_files_folder + "constraints.smt2 > " + f_output).c_str());
			  ifp.open(f_output.c_str());
			  getline(ifp, line);
			  ifp.close();
			  //cout << "$$$$$$$$ " << count << " " << line << endl;
			  cout << line << endl;

			  if (line == "unsat")
			  {
				min_total_cost = current_cost;
				break;
			  }
			  else if (line == "sat")
			  {
				sat_flag = true;
				max_total_cost = extractTrajectoryCostInformation(f_output);
				cout<<"renaming z3 output"<<endl;
				system(("mv " + static_files_folder + "z3_output " + static_files_folder + "z3_output_sat").c_str());
			  }
			  else
			  {
				cout << "unknown output from z3.." << endl;
				min_total_cost = current_cost;
				if (sat_flag == true)
				  break;
			  }
			  current_cost = (max_total_cost + min_total_cost) / 2;
			  cout << "max_total_cost = " << max_total_cost << endl;
			  cout << "min_total_cost = " << min_total_cost << endl;
			  cout << "current_cost  = " << current_cost << endl;
			}

	    }


	    count = count + 1;
	    cout << "renaming z3 output back"<<endl;
	    system(("mv "+static_files_folder+"z3_output_sat "+ static_files_folder+"z3_output").c_str());

	    return;
	  }
	}
	
	pos_vec_t AntMultiPlanner::convertPosesIntoScaledPositions_(std::vector<ordered_pose_stamped::OrderedPoseStamped>& poses, std::map<position, ordered_pose_stamped::OrderedPoseStamped>& conversion_map)
	{
		pos_vec_t converted_poses;
		for (std::vector<ordered_pose_stamped::OrderedPoseStamped>::iterator it = poses.begin(); it != poses.end(); it++)
		{
			pos_2d temp_position;
			temp_position.x = it->pose.position.x;
			temp_position.y = it->pose.position.y;
			position implanPosition = metersToImplanUnits(temp_position);
			converted_poses.push_back(implanPosition);
			conversion_map[implanPosition] = *it;
		}

		return converted_poses;
	}

	std::vector<ordered_pose_stamped::OrderedPoseStamped> AntMultiPlanner::convertScaledPositionsIntoPoses(pos_vec_t & positions)
	{
		std::vector<ordered_pose_stamped::OrderedPoseStamped> converted_positions;
		for (int i = 0; i < positions.size(); i++)
		{
			ordered_pose_stamped::OrderedPoseStamped temp_pose;
			position temp_position = positions[i];
			pos_2d converted_position = implanUnitsToMeters(temp_position);
			temp_pose.pose.position.x = converted_position.x;
			temp_pose.pose.position.y = converted_position.y;
			temp_pose.header.frame_id="/map";
			temp_pose.pose.orientation.w = 1.0;

			converted_positions.push_back(temp_pose);
		}
		return converted_positions;
	}

	bool AntMultiPlanner::makePlan(std::vector<ordered_pose_stamped::OrderedPoseStamped>& start_poses,
	          std::vector<ordered_pose_stamped::OrderedPoseStamped>& goal_poses,
			  std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> >& assignments,
			  std::map<ordered_pose_stamped::OrderedPoseStamped, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >& plans)
	{
	  ros::NodeHandle private_nh("~");
	  //private_nh.param("ant_multi_planner/path_cost_tolerance", multiPathCostTolerance, 13.0);

	  pos_vec_t initpos, finalpos;
	  robot_pos_vec_t initposjson;
	  position last_pos, starting_pos;
	  int max_length;
	  vector<int> x_arr, y_arr, prim_arr;
	  string f_output;
	  int number_of_robots;
	  pos_vec_t tmp_pos_vec, tmp_plans, tmp_assignments;
	  map<ordered_pose_stamped::OrderedPoseStamped, pos_vec_t > tmp_plans_per_goal;
	  map<position, ordered_pose_stamped::OrderedPoseStamped> initposConversionMap, finalposConversionMap;

	  // variable to keep track of goal poses that are already assigned
	  set<ordered_pose_stamped::OrderedPoseStamped> assignedGoalPoses;

	  //number of robots is equal to number of starting poses (one starting pose = one robot)
	  number_of_robots = start_poses.size();

	  cout << endl << endl;
	  cout << "*** Concurrent Assignment and Planning ***" << endl << endl;

/*
	    readPositions(initpos, (static_files_folder+"initpos.txt").c_str());
	    cout << "Initial Positions of the Robots:" << endl;
	    writePositions(initpos);
	    */
	  cout <<"start and goal poses at beginning"<<endl;
	  for (int si = 0; si < start_poses.size();++si)
	  		cout<<start_poses[si].pose.position.x<<" "<<start_poses[si].pose.position.y<<endl;
	  for (int si = 0; si < goal_poses.size();++si)
	  	  		cout<<goal_poses[si].pose.position.x<<" "<<goal_poses[si].pose.position.y<<endl;

	  //convert from meters to implan grid units
	  initpos = convertPosesIntoScaledPositions_(start_poses, initposConversionMap);
	  finalpos = convertPosesIntoScaledPositions_(goal_poses, finalposConversionMap);
	  	/*
	    readPositions(finalpos, (static_files_folder+"finalpos.txt").c_str());
	    cout << "Positions of the Destinations:" << endl;
	    writePositions(finalpos);
	    */


/*
	  cout<<"finalpos conversions"<<endl;
	  cout<<"size: "<<finalposConversionMap.size()<<endl;

	  for(map<position, ordered_pose_stamped::OrderedPoseStamped>::iterator p_it = finalposConversionMap.begin(); p_it != finalposConversionMap.end(); p_it++)
		  cout<<p_it->first.x<<" "<<p_it->first.y<<"<->"<<p_it->second.pose.position.x<<" "<<p_it->second.pose.position.y<<endl;
*/

	  //max search length for implan. @indranil, why is this x + y?
	   max_length = dimension.length_x + dimension.length_y;

	   cout << "Maximum Length = " << max_length << endl << endl;

	   //generate optimal trajectories in the file z3_output
	   generateTrajectories(primitives, dimension, obstacles, initpos, finalpos, max_length);
	   f_output = static_files_folder+"z3_output";

	   float final_cost = extractTrajectoryCostInformation(f_output);
	   ofstream ofp;
	   string res_file =static_files_folder+"/costs/ant_multi_planner_costs.txt";
	   ofp.open(res_file.c_str(), ofstream::app);
	   ofp<<final_cost<<endl;
	   ofp.close();

	    for (int count = 1; count <= number_of_robots; count++){
	    	x_arr.clear();
	    	y_arr.clear();
	    	tmp_assignments.clear();
	    	tmp_plans.clear();
	    	tmp_plans_per_goal.clear();
	    	ordered_pose_stamped::OrderedPoseStamped starting_pose;

	    	// pose will be in meters, position in implan grid units
	    	starting_pose.pose.position.x = start_poses[count-1].pose.position.x;
	    	starting_pose.pose.position.y = start_poses[count-1].pose.position.y;
	    	cout<<starting_pose.pose.position.x<<" "<<starting_pose.pose.position.y<<endl;
	    	//from the file f_output read into x_arr and y_arr the trajectories for robot {count}
	    	extractTrajectoryInformation(count, x_arr, y_arr , prim_arr, f_output);

	    	//initialize to non-existing values (all the values in the map are positive)
	    	//this variable is to eliminate duplicates that happen to exist in the output
	    	last_pos.x = -100;
	    	last_pos.y = -100;

	    	//iteration over waypoints
	    	for (int count1 = 0; count1 < x_arr.size(); count1++)
	    	    {
	    		  position tmp_pos;
	    	      tmp_pos.x = x_arr[count1];
	    	      tmp_pos.y = y_arr[count1];
	    	      cout<<"plans: "<<endl<<endl;

	    	      // the if statement eliminates duplicates that may exist in the output file
	    	      if (last_pos.x != tmp_pos.x || last_pos.y != tmp_pos.y)
	    	      {
	    	    	position p;
	    	    	p.x = tmp_pos.x;
	    	    	p.y = tmp_pos.y;

	    	        last_pos.x = tmp_pos.x;
	    	        last_pos.y = tmp_pos.y;
	    	        cout<<p.x<<" "<<p.y<<endl;
	    	        tmp_plans.push_back(p);
	    	      }

	    	      for (int count2 = 0; count2 < finalpos.size(); count2++)
	    	      {
	    	    	// if currently found position is among the final positions we're trying to reach
	    	        if (finalpos[count2].x == tmp_pos.x && finalpos[count2].y == tmp_pos.y)
	    	        {
	    	          // if this position is not already added to the final positions **for this robot**
	    	          if (findPosition(tmp_assignments, tmp_pos) == false)
	    	          {
	    	        	ordered_pose_stamped::OrderedPoseStamped goal_pose;
	    	        	//pos_2d goal_pose_converted = implanUnitsToMeters(tmp_pos);

	    	        	// find the pose corresponding to tmp_pos
	    	        	goal_pose = finalposConversionMap[tmp_pos];
	    	        	goal_pose.header.frame_id="/map";
	    	        	//goal_pose.pose.position.x = goal_pose_converted.x;
	    	        	//goal_pose.pose.position.y = goal_pose_converted.y;

	    	            tmp_assignments.push_back(tmp_pos);
	    	            cout << x_arr[count1] << " " << y_arr[count1] << endl;

	    	            //add the plan for this starting pose to variable plans
	    	            plans[starting_pose][goal_pose]=convertScaledPositionsIntoPoses(tmp_plans);

	    	            //at the end, add goal pose one more time (because of rounding errors when converting between implan units and meters). this way we're sure that the last waypoint would be exactly goal_pose
	    	            plans[starting_pose][goal_pose].push_back(goal_pose);
	    	            //ROS_ERROR("goal_position: (%d, %d) added for starting position (%d, %d)", tmp_pos.x, tmp_pos.y, x_arr[0], y_arr[0]);
	    	            //ROS_ERROR("goal_pose: (%f, %f) added for starting pose (%f, %f)", goal_pose.pose.position.x, goal_pose.pose.position.y, starting_pose.pose.position.x, starting_pose.pose.position.y);
	    	            tmp_plans.clear();
	    	          }
	    	        }
	    	      }
	    	    }
	    	//some of the final positions found -> it should always be like this
	    	if (!tmp_assignments.empty()){
	    		cout<<"tmp_assignemnets non empt"<<endl;
	    		for (int i = 0; i < tmp_assignments.size();++i){
	    			cout<<tmp_assignments[i].x<<" "<<tmp_assignments[i].y<<endl;
	    		}
//				cout<<"starting pose: "<<endl;
//				cout<<starting_pose.pose.position.x<<" "<<starting_pose.pose.position.y<<endl;

				//assignments[starting_pose] = convertScaledPositionsIntoPoses(tmp_assignments);
				assignments[starting_pose].clear();
				std::vector<ordered_pose_stamped::OrderedPoseStamped> converted_positions;

				// adding the content from tmp_assignements to variable assignments
				for (int i = 0; i < tmp_assignments.size(); i++)
				{

					ordered_pose_stamped::OrderedPoseStamped temp_pose;
					position temp_position = tmp_assignments[i];
					temp_pose = finalposConversionMap[temp_position];
					if (assignedGoalPoses.count(temp_pose) == 0){
						assignments[starting_pose].push_back(temp_pose);
						assignedGoalPoses.insert(temp_pose);
					}
				}


				cout<<"assignment:"<<endl;
				for (int l = 0; l < assignments[starting_pose].size(); ++l){
					ordered_pose_stamped::OrderedPoseStamped cur_goal = assignments[starting_pose][l];
					cout<<cur_goal.pose.position.x<<" "<<cur_goal.pose.position.y<<endl;
					vector<ordered_pose_stamped::OrderedPoseStamped> cur_waypoints = plans[starting_pose][cur_goal];
					for (int cl = 0; cl < cur_waypoints.size(); ++cl){
						cout<<cur_waypoints[cl].pose.position.x<<" "<<cur_waypoints[cl].pose.position.y<<endl;
					}
					cout<<"--wp--"<<endl;
				}



/*
				for (int l = 0; l < temp_plans_per_agent.size(); ++l){
					plans[starting_pose].push_back(convertScaledPositionsIntoPoses(tmp_plans_per_agent[l]));

				}
				*/
				cout<<"converted plans"<<endl;

	    	}
	    }

	    //printTrajectories(initpos.size(), initpos, finalpos);



	  
	return true;
	}

	bool AntMultiPlanner::findPosition (pos_vec_t posvec, position pos)
	{
	  unsigned int count;

	  for (count = 0; count < posvec.size(); count++)
	  {
	    if (posvec[count].x == pos.x && posvec[count].y == pos.y)
	      return true;
	  }
	  return false;
	}

};
