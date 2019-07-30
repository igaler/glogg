#!/usr/bin/python
import sys
import time

def parseLine(args):
        print "<br>Lines to parse </br>", args[0]
        print "The arguments are: " , args[1]


def comboBox():
	print "Proj0","Proj1","Proj2","Proj3"


if __name__ == '__main__':
        print "<head><style>  b {       font-weight: bold; background-color:#ff0000;   }    </style></head>"
        print "<body>"
        print "<b>My Script called</b>"
        parseLine(sys.argv[1:])
        print "</body>"

