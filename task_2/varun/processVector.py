import glob
import os
import re
import subprocess
import csv
from subprocess import call
from pprint import pprint
import pandas as pd
import numpy as np

def write_to_csv(d, fileName):
	# dtype=[('fname','|S100'), ('RAR','>i4'), ('RAW','>i4'), ('TotalNumberOfDependencies','>i4'), ('WAR','>i4'), ('WAW','>i4'), \
	# ('MeanCycle_fvec','>i4'), ('MeanCycle_novec','>i4'), ('MeanCycle_vec','>i4'), ('Vector','|S100'),('factor','|S100')]
	# result = np.empty( (len(d),), dtype=dtype)
	# i = 0
	# for k, v in d.items():
	# 	r = (k, v['Dependency']['RAR'], v['Dependency']['RAW'], v['Dependency']['TotalNumberOfDependencies'], v['Dependency']['WAR'], v['Dependency']['WAW'], \
	# 		v['MeanCycle_fvec'], v['MeanCycle_novec'] , v['MeanCycle_vec'],v['Vector'][0],  v['Vector'][1])
	# 	result[i] = r
	# 	i+=1	

	dtype=[('fname','|S100'), \
	('MeanCycle_fvec','>i4'), ('MeanCycle_novec','>i4'), ('MeanCycle_vec','>i4'), ('Vector','|S100'),('factor','|S100')]
	result = np.empty( (len(d),), dtype=dtype)
	i = 0
	for k in sorted(d):
		v = d[k]
		r = (k, v['MeanCycle_fvec'], v['MeanCycle_novec'] ,v['MeanCycle_vec'], v['Vector'][0],  v['Vector'][1])
		result[i] = r
		i+=1	



	df = pd.DataFrame(result)
	

	df.to_csv(fileName,header=True)
	return df
	#df = df[df['MeanCycle_vec']!=-1]
	#df = df[df['MeanCycle_fvec']!=-1]
	#df = df[df['MeanCycle_novec']!=-1]

	#df.to_csv('filtered_'+ fileName,header=True)

def runCommand(command):
	p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	lines = p.stdout.readlines()
	return lines

def getAverageCycles(file):
	fileName = "./"+file
	command = fileName + " ./input 1000"
	commandOutput = runCommand(command)
	if "Segmentation" in commandOutput[-1]:
		print "Core dump for " + file
		return -1
	lastLine = commandOutput[-1].split()
	if len(lastLine)<3:
		return -1
	meanCycle = unicode(lastLine[2], 'utf-8')
	if meanCycle.isnumeric():
		return meanCycle
	else:
		print "Failed for file: " + file + " --- " + commandOutput[-1]
		return 1

def verifyMakeOutput(lines):
	return "main.optrpt" in lines[-1]

def getSpeed(lines):
	reason = ""
	for line in lines:
		if "estimated potential speedup" in line:
			reason = line.split()[-1]
	return reason

def getDependency(fileName, plutoLocation, directory):
	command = plutoLocation + " --moredebug " + fileName
	commandOutput = runCommand(command)
	listResult = []
	mapResult = dict()
	for line in commandOutput:
		if "--- Dep" in line:
			listResult.append(line.split()[-1])
	
	os.system(command + ' > ' + directory + "/" + fileName)

	if listResult:
		mapResult["TotalNumberOfDependencies"] = len(listResult)
		mapResult["WAW"] = listResult.count('WAW')
		mapResult["RAW"] = listResult.count('RAW')
		mapResult["RAR"] = listResult.count('RAR')
		mapResult["WAR"] = listResult.count('WAR')
	else:
		mapResult["TotalNumberOfDependencies"] = 0
		mapResult["WAW"] = 0
		mapResult["RAW"] = 0
		mapResult["RAR"] = 0
		mapResult["WAR"] = 0
	return mapResult

def getReason(str):
	if "inefficient" in str:
		return "Vectorization not profitable"
	elif "vector dependence" in str:
		return "Dependence present (Any type)"
	elif "inner loop was already vectorized" in str:
		return "Inner loop was already vectorized"
	else:
		return str

def isVectorized(fileName):
	with open(fileName) as f:
		content = f.readlines()
	substringNotVectorized = "loop was not vectorized"
	substringVectorized = "LOOP WAS VECTORIZED"
	isVector = True
	reason = ""
	for s in content:
		if substringNotVectorized in s:
			isVector = False
			reason = getReason(s)
			break
		elif substringVectorized in s:
			reason = getSpeed(content)
			break
	if isVector:
		reason = getSpeed(content)
	return isVector, reason

def main(folder, plutoLocation):

	os.chdir(folder)
	makeClean = runCommand("make clean")
	makeVec = runCommand("make vec CC=icc")
	
	# Keep the dependency information (in a text file) it will serve you for future tasks.
	directoryPluto = "plutoDependency"
	runCommand("rm -rf " + directoryPluto)
	os.makedirs(directoryPluto)

	invalidFiles = []
	fileMap = dict()

	if not verifyMakeOutput(makeVec):
		print "Make file not compiled correctly"
		return

	for file in glob.glob("*.optrpt"):
		res, reason = isVectorized(file)
		name = re.search('.*line[0-9]+', file)
		if not name:
			continue
		name = name.group(0)

		if name not in fileMap:
			fileMap[name] = dict()
		fileMap[name]["Vector"] = [res, reason]

	for fileType in ["*.vec", "*.fvec", "*.novec"]:
		makeClean = runCommand("make clean")
		fType = fileType.split('.')[-1]
		command = "make " + fType + " CC=icc"
		runCommand(command)
		for fileName in glob.glob(fileType):
			meanCycle = getAverageCycles(fileName)

			name = re.search('.*line[0-9]+', fileName)
			if not name:
				continue
			name = name.group(0)

			if meanCycle ==-1:
				invalidFiles.append(fileName)

			if name not in fileMap:
				fileMap[name] = dict()
			fileMap[name]["MeanCycle_"+fType] = meanCycle


	# for fileName in glob.glob("*_loop.c"):
	# 	os.chdir(folder)
	# 	dependency = getDependency(fileName, plutoLocation, directoryPluto)

	# 	name = re.search('.*line[0-9]+', fileName)
	# 	if not name:
	# 		continue
	# 	name = name.group(0)

	# 	if name not in fileMap:
	# 		fileMap[name] = dict()
	# 	fileMap[name]["Dependency"] = dependency

	# commandOutput = runCommand("cat /proc/cpuinfo")
	# instructionSets = set()

	# for line in commandOutput:
	# 	if "sse" in line:
	# 		instructionSets.add("SSE")

	# 	if "avx" in line:
	# 		instructionSets.add("AVX")

	# 	if "avx2" in line:
			# instructionSets.add("AVX2")
	df = write_to_csv(fileMap, 'results.csv')
	
	print "\n\nResult:"
	pprint(fileMap)
	print "\n\nInvalid files: "
	pprint(invalidFiles)
	# print "\n\nInstruction sets: "
	# pprint(instructionSets)

if __name__ == '__main__':
	# Location of extractedLoops
	folder = "/home/varun/hpa/task_2/varun/loops"

	# Location of polycc executable
	plutoLocation = "/home/akshay/Tool/pluto-0.11.4/polycc"

	main(folder, plutoLocation)
