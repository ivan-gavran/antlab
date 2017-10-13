## Packages involved

- *multi\_global\_planner* <br/>
This package contains infrastructure for publishing the waypoints that multi-planner produced to the move base (a package for moving a single robot).
It accepts an implementation of *multi\_planner\_base:MultiPlanner* as a plugin. (so, multi\_global\_planner would always be present in the launch file and a particular instance
of multi\_planner\_base would be given as an argument to it)

- *multi\_planner\_base* (multi\_robot\_move) <br/>
the confusion in naming comes from the fact that the folder is named multi\_robot\_move, while the namespace is multi\_planner\_base. (That will be changed in the future)
This is an interface for multi planners, prescribing which functions have to be implemented in a planner.

- *ant\_multi\_planner* <br />
inherits from multi\_planner\_base:MultiPlanner. This particular implementation is the one that uses SMT-based solution to multi-robot planning problem.
