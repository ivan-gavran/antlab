import pdb
import json
import os
import argparse
import json
import csv
from utils.tbot_json_encoder import TurtlesEncoder
from datetime import datetime


def get_immediate_subdirectories(a_dir):
    return [name for name in os.listdir(a_dir)
            if os.path.isdir(os.path.join(a_dir, name))]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--testFolder", dest='testFolder', default="/home/ivan/antlab/system_0/staticFilesTesting/")
    
    args, unknown = parser.parse_known_args()
    testingFolder = args.testFolder
    tests = get_immediate_subdirectories(testingFolder)
    for test in tests:
        results = {}
        jsonResultFiles = [testingFolder+test+'/'+t for t in os.listdir(testingFolder+test) if 'stats' in t]
        with open(testingFolder+'reachabilityTestResults/'+test+'.csv', "w") as csvfile:
            csvwriter = csv.writer(csvfile)
            csvwriter.writerow(['test_id', 'planning_time_ant_multi', 'execution_time_ant_mult', 'planning_time_metric_ff', 'execution_time_metric_ff','planning_time_baseplan', 'execution_time_baseplan'])
            resDict = {}
            
            for resultJsonFileName in jsonResultFiles:
                implanData = False
                if 'testLocations' in resultJsonFileName:
                    continue
                if 'ant_multi' in resultJsonFileName:
                    interestingColumns = {'exec':'execution_time_ant', 'plan':'planning_time_ant'}
                elif 'metricff' in resultJsonFileName:
                    interestingColumns = {'exec':'execution_time_metric_ff', 'plan':'planning_time_metric_ff'}
                else:
                    interestingColumns = {'exec':'execution_time_baseplan', 'plan':'planning_time_baseplan'}
                            
                with open(resultJsonFileName) as resultJsonFile:
                    resJson = json.load(resultJsonFile)
                    for res in resJson:
                        if res not in resDict:
                            resDict[res] = {}
                        try:
                            execTime = datetime.strptime( resJson[res]['sent_to_execution'], '%Y-%m-%d %H:%M:%S.%f' )
                            schedTime = datetime.strptime( resJson[res]['sent_to_scheduler'], '%Y-%m-%d %H:%M:%S.%f' )
                            resDict[res][interestingColumns['plan']] = (execTime - schedTime).total_seconds()
                        except:
                            
                            resDict[res][interestingColumns['plan']] = 0
                                                                          
                        try:                                            
                            execTime = datetime.strptime( resJson[res]['sent_to_execution'], '%Y-%m-%d %H:%M:%S.%f' )
                            finishedTime = datetime.strptime( resJson[res]['finished'], '%Y-%m-%d %H:%M:%S.%f' )
                            resDict[res][interestingColumns['exec']] = (finishedTime - execTime).total_seconds()
                        except:
                            resDict[res][interestingColumns['exec']] = 0                                                                        
            
            for res in resDict:
                try:
                    csvwriter.writerow( [ res, resDict[res]['planning_time_ant'], resDict[res]['execution_time_ant'], resDict[res]['planning_time_metric_ff'], resDict[res]['execution_time_metric_ff'],\
                                         resDict[res]['planning_time_baseplan'], resDict[res]['execution_time_baseplan'] ])
                except Exception as e:
                    print('exception! but why')
                    print(e)
                    print(test)
            #pdb.set_trace()
                        
            
             
            
        
        
    
if __name__ == '__main__':
    main()