#!/usr/bin/python

import os
# part of espeak python library
from subprocess import call
from sys import argv

# execute: python voiceover.py sample_text.txt
# script = voiceover.py
# filename = sample_text.txt
# argv reads voiceover.py and sample_text.txt and assigns it to script and filename respectively
script,filename = argv

# open the filename assigned
txt = open(filename)

# for each word, lets give voice output
for word in txt:
	call(["espeak",word])
