#!/usr/bin/python
import sys
import time

def parseLine(args):
        print "Lines to parse ", args[0]
        print "The arguments are: " , args[1]


def comboBox():
	print "Proj0","Proj1","Proj2","Proj3"


if __name__ == '__main__':
        print "My Script called"
        parseLine(sys.argv[1:])

