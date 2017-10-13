def measureCost(z3OutputFile, assignmentFile):
    setOfActiveRobots = set()
    with open(assignmentFile) as assignment_f:
        for line in assignment_f:
            setOfActiveRobots.add(int(line.strip()[0]))
    with open(z3OutputFile) as f:
        cost = 0
        for line in f:
            for idx in setOfActiveRobots:
                keyString = "total_cost_"+str(idx+1) 
                if keyString in line:
                    line = line.replace(keyString, "")
                    line = line.strip("()\n\t ")
                    totalCostContents = line.split()
                    if "/" in line:
                        cost +=  float(totalCostContents[1]) / float(totalCostContents[-1])
                    else:
                        
                        cost += float(totalCostContents[0])
    with open("/home/ivan/antlab-repo/system_0/ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/costData", "w") as f_cost:

            f_cost.write(str(cost))
if __name__ == '__main__':
    measureCost("/home/ivan/antlab-repo/system_0/ros_simulation/src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output",\
                 "/home/ivan/antlab-repo/system_0/ros_simulation/src/multiple_robots_stage/static_files_folder/assignmentFile.txt")

   
