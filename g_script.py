#!/usr/bin/python
import sys
import time

def parseLine(*args):
	print "This is the name of the script: ", args[0]
	print "Number of arguments: ", len(args)
	print "The arguments are: " , str(args)


def comboBox():
	print "Proj0","Proj1","Proj2","Proj3"


if __name__ == '__main__':
	print "My Script clled"
	parseLine(sys.argv)

