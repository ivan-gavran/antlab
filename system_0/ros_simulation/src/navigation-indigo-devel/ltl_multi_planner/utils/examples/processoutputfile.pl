#!/usr/local/bin/perl

$file = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/z3_output";
open(FH, $file);
@lines = <FH>;
close(FH);

$file = "src/navigation-indigo-devel/ltl_multi_planner/utils/examples/planner_output";
open(FH, ">$file");

$flag = 0;
$flag1 = 0;
foreach $line (@lines)
{
  if ($line =~ "sat")
  {
    print FH "$line";
  }
  if($line =~ "vel")
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
  if($line =~ "x_")
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
  if($line =~ "y_")
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
  if($line =~ "l_" && not($line =~ "ve") && not($line =~ "g++"))
  {
    $line =~ s/\(\(//g;
    $line =~ s/\)\)//g;
    print FH "$line";
  }
}

close(FH); 
