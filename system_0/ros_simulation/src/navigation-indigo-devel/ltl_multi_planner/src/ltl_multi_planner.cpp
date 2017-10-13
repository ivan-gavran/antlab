#include <pluginlib/class_list_macros.h>
#include <multi_robot_move/multi_planner_base.h>
#include <ltl_multi_planner/ltl_multi_planner.h>
#include <ltl_multi_planner/primitive.h>
#include <ltl_multi_planner/readinputs.h>
#include <ltl_multi_planner/writeconstraints.h>
#include <ltl_multi_planner/extractoutput.h>
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

PLUGINLIB_EXPORT_CLASS(ltl_multi_planner::LtlMultiPlanner, multi_planner_base::MultiPlanner)

namespace ltl_multi_planner {
	LtlMultiPlanner::LtlMultiPlanner() : initialized_(false)
	{
		ros::NodeHandle private_nh("~");
		ROS_ERROR("LtlMultiPlanner constructor");


		string default_value = "240";
		string primitives_filename_default_value= "primitive_movements_manhattan.txt";
		private_nh.param("ltl_multi_planner/path_cost_tolerance", multiPathCostTolerance, 5.0);
		private_nh.param("ltl_multi_planner/planning_patience", z3TimeoutInSeconds, default_value);
		private_nh.param("ltl_multi_planner/final_optimization", final_smt_cost_optimization, false);
		private_nh.param("ltl_multi_planner/primitives", primitives_filename, primitives_filename_default_value);
		double testParam;
		private_nh.setParam("ltl_multi_planner/testParam", 1.0);
		// put this to ros params
		static_files_folder = "src/multiple_robots_stage/static_files_folder/";
		system_config_files_folder = "../config/";
		initialize();
	}

	void LtlMultiPlanner::initialize()
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

		      readDimension(dimension, static_files_folder+"ltl_dimension.txt");
		      readPositions(obstacles, static_files_folder+"ltl_obstacle.txt");
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
	position LtlMultiPlanner::metersToImplanUnits(pos_2d pos){
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

	position LtlMultiPlanner::metersToImplanUnits2(int x, int y){
			  ROS_WARN("transformation");
			  position p;
			  ostringstream os, os1;
			  double IMPLAN_UNIT_SIZE = map_resolution * map_scale;
			  cout<<"IMPLAN_UNIT_SIZE "<<IMPLAN_UNIT_SIZE<<endl;
			  double IMPLAN_MAP_WIDTH = map_width;
			  cout<<"map_width "<<map_width<<endl;
			  os <<"received position ("<< x<<", "<<y<<") in meters";
			  cout<<os.str()<<endl;

			  p.x = round(x / IMPLAN_UNIT_SIZE);
			  os << p.x;
			  cout<<os.str()<<endl;
			  p.y = round(IMPLAN_MAP_WIDTH - (y*1.0 / IMPLAN_UNIT_SIZE));
			  os1<<"transformed it in ("<<p.x<<", "<<p.y<<") in implan units";
			  cout<<os1.str()<<endl;
			  ROS_WARN("transformation finished");
			  //throw;
			  return p;
		  }



	  pos_2d LtlMultiPlanner::implanUnitsToMeters(position pos){
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

  int LtlMultiPlanner::findTheGreatestManhattanDistance(pos_vec_t initpos, pos_vec_t finalpos)
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

	void LtlMultiPlanner::createWorkspace(dimension_t dimension, pos_vec_t initposition)
	{
	  unsigned int count;
	  ofstream ofp;
	  ofp.open((static_files_folder + "ltl_workspace.txt").c_str());
	  ofp<<dimension.length_x<<endl;
	  ofp<<dimension.length_y<<endl;
	  ofp<<initposition.size()<<endl;

	  for (count = 0; count < initposition.size(); count++)
	  {
	    ofp<<initposition[count].x<<" "<<initposition[count].y<<endl;
	  }
	  for (count = 0; count < initposition.size(); count++)
	  {
	    ofp<<"-1 -1"<<endl;
	  }
	  ofp<<"20"<<endl;
	  ofp<<"1000"<<endl;

	  ofp.close();
	}





	pos_vec_t LtlMultiPlanner::convertPosesIntoScaledPositions_(std::vector<ordered_pose_stamped::OrderedPoseStamped>& poses, std::map<position, ordered_pose_stamped::OrderedPoseStamped>& conversion_map)
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

	std::vector<ordered_pose_stamped::OrderedPoseStamped> LtlMultiPlanner::convertScaledPositionsIntoPoses(pos_vec_t & positions)
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

	std::map<string, std::vector<ordered_pose_stamped::OrderedPoseStamped> > LtlMultiPlanner::readAndConvertPropositions()
	{
	  std::map<string, std::vector<ordered_pose_stamped::OrderedPoseStamped> > propositionMap;
	  cout<<"reading propositions"<<endl;
	  ifstream ifp;
	  ofstream ofp;
	  string line;
	  string prop;
	  int location;
	  position pos_tmp;
	  string originalPropositionsFile = static_files_folder + "original_ltl_propositions";
	  string propositionsFile = static_files_folder + "propositions_ltl_planner";

	  ifp.open(originalPropositionsFile.c_str());
	  ofp.open(propositionsFile.c_str());
	  if (ifp.is_open() && ofp.is_open())
	  {
		while (getline(ifp, line))
		{
		  cout<<line<<endl;
		  location = line.find(' ');
		  string name = line.substr(0, location);
		  ofp<<name<<" ";
		  line = line.substr(location + 1);
		  location = line.find(' ');

		  while (location != -1)
		  {
			ordered_pose_stamped::OrderedPoseStamped temp_goal;
			int x, y;
			istringstream (line.substr(0, location)) >> x;
			line = line.substr(location + 1);
			cout<<line<<endl;
			cout<<"x = "<<x<<endl;

			location = line.find(' ');
			if (location != -1)
			{
			  istringstream (line.substr(0, location)) >> y;
			  line = line.substr(location + 1);
			  cout<<line<<endl;
			}
			else
			  istringstream (line.substr(location + 1)) >> y;
			cout<<"y = "<<y<<endl;
			position p = metersToImplanUnits2(x, y);
			ofp<<p.x<<" "<<p.y;
			temp_goal.pose.position.x = x;
			temp_goal.pose.position.y = y;
			cout<<p.x<<" "<<p.y;
			location = line.find(' ');
			propositionMap[name].push_back(temp_goal);
		  }

		  cout<<endl;
		  ofp<<endl;
		}
	  }
	  ifp.close();
	  ofp.close();
	  return propositionMap;
	}

	bool LtlMultiPlanner::makePlan(std::vector<ordered_pose_stamped::OrderedPoseStamped>& start_poses,
	          std::vector<ordered_pose_stamped::OrderedPoseStamped>& goal_poses,
			  std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> >& assignments,
			  std::map<ordered_pose_stamped::OrderedPoseStamped, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >& plans)
	{
	  ros::NodeHandle private_nh("~");
	  //private_nh.param("ltl_multi_planner/path_cost_tolerance", multiPathCostTolerance, 13.0);
	  system("rm src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output");
	  std::map<string, std::vector<ordered_pose_stamped::OrderedPoseStamped> > propositionLocationMap;

	  // in this map there are propositions given in meters
	  propositionLocationMap = readAndConvertPropositions();
	  goal_poses.clear();

	  for (map<string, vector<ordered_pose_stamped::OrderedPoseStamped> >::iterator mi = propositionLocationMap.begin(); mi != propositionLocationMap.end(); ++mi)
	  {
		  goal_poses.push_back(mi->second[0]);
		  cout<<"pushing to the goal_poses "<<mi->second[0].pose.position.x<<" "<<mi->second[0].pose.position.y<<endl;
	  }

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
	  std::vector<string> propositions;


	  // variable to keep track of goal poses that are already assigned
	  set<ordered_pose_stamped::OrderedPoseStamped> assignedGoalPoses;

	  //number of robots is equal to number of starting poses (one starting pose = one robot)
	  number_of_robots = start_poses.size();
	  max_length = dimension.length_x + dimension.length_y;

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



	  createWorkspace(dimension, initpos);
	  system("src/navigation-indigo-devel/ltl_multi_planner/utils/examples/run.sh");
	  f_output = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output";
	  string assignmentFileName = static_files_folder + "assignmentFile.txt";

	  	map<int, vector<position> > assignmentMap = extractAssignments(assignmentFileName);
	    for (int count = 1; count <= number_of_robots; count++){
	    	cout<<"robot "<<count-1<<endl;
	    	vector<position> goalPositions = assignmentMap[count-1];
	    	if (goalPositions.size() == 0){
	    		cout<<"size of goalPositions map for "<<count-1<<" = 0"<<endl;
	    		continue;
	    	}

	    	//string robotName = "r"+tostr(count);
	    	x_arr.clear();
	    	y_arr.clear();
	    	tmp_assignments.clear();
	    	tmp_plans.clear();
	    	tmp_plans_per_goal.clear();
	    	ordered_pose_stamped::OrderedPoseStamped starting_pose;

	    	// pose will be in meters, position in implan grid units
	    	starting_pose.pose.position.x = start_poses[count-1].pose.position.x;
	    	starting_pose.pose.position.y = start_poses[count-1].pose.position.y;
	    	cout<<"starting pose "<<starting_pose.pose.position.x<<" "<<starting_pose.pose.position.y<<endl;
	    	//from the file f_output read into x_arr and y_arr the trajectories for robot {count}
	    	extractTrajectoryInformation(count, x_arr, y_arr , prim_arr, f_output);


	    	//initialize to non-existing values (all the values in the map are positive)
	    	//this variable is to eliminate duplicates that happen to exist in the output
	    	last_pos.x = -100;
	    	last_pos.y = -100;
	    	bool planEmpty = true;
	    	//iteration over waypoints
	    	cout<<"plans: "<<endl<<endl;
	    	for (int count1 = 0; count1 < x_arr.size(); count1++)
	    	{
	    		planEmpty = false;
	    	    position tmp_pos;
	    	      tmp_pos.x = x_arr[count1];
	    	      tmp_pos.y = y_arr[count1];
	    	      cout<<"tmp_pos: "<<tmp_pos.x<<" "<<tmp_pos.y<<endl;


	    	      // the if statement eliminates duplicates that may exist in the output file
	    	      if (last_pos.x != tmp_pos.x || last_pos.y != tmp_pos.y)
	    	      {
	    	    	position p;
	    	    	p.x = tmp_pos.x;
	    	    	p.y = tmp_pos.y;

	    	        last_pos.x = tmp_pos.x;
	    	        last_pos.y = tmp_pos.y;
	    	        tmp_plans.push_back(p);
	    	      }

	    	      for (int count2 = 0; count2 < finalpos.size(); count2++)
	    	      {
	    	    	// if currently found position is among the final positions we're trying to reach
	    	    	  cout<<"finalpos: "<<finalpos[count2].x<<", "<<finalpos[count2].y<<endl;
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
	    	        	goal_pose.pose.orientation.w = 1.0;
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

//	    	      for (int vi = 0; vi < goalPositions.size(); ++vi)
//	    	      {
//	    	    	  if (goalPositions[vi].x == tmp_pos.x && goalPositions[vi].y == tmp_pos.y)
//	    	    	  {
//	    	    		  tmp_assignments.push_back(tmp_pos);
//	    	    		  goalPose = implanUnitsToMeters(tmp_pos);
//	    	    		  plans[starting_pose][goal_pose]=convertScaledPositionsIntoPoses(tmp_plans);
//	    	    		  assignments[starting_pose].push_back(goalPose);
//	    	    		  tmp_plans.clear();
//	    	    	  }
//	    	      }


	    	  }

//			ordered_pose_stamped::OrderedPoseStamped dummy_goal;
//			dummy_goal.pose.position.x = -1;
//			dummy_goal.pose.position.y = -1;
//			plans[starting_pose][dummy_goal]=convertScaledPositionsIntoPoses(tmp_plans);


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

//			tmp_plans.clear();
//
//
//			 if (planEmpty == false)
//			 {
//				tmp_assignments.push_back(dummy_goal);
//				assignments[starting_pose] = tmp_assignments;
//			 }
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

	bool LtlMultiPlanner::findPosition (pos_vec_t posvec, position pos)
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


