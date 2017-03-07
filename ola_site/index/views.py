#!/usr/bin/env python
# -*- coding: utf-8 -*- 
from django.shortcuts import render
import subprocess
from pipes import quote
from pexpect import run
import os

curdir = os.getcwd()
# Create your views here.
def hello_world(request):
	os.chdir(curdir + "/ola_compiler")
	fread = open('dema.p', 'r')
	dema = fread.read().decode('utf8')
	input1 = dema[6:-15]
	fread1 = open('demb.p', 'r')
	demb = fread1.read().decode('utf8')
	input2 = demb[6:-15]
	fread2 = open('demc.p', 'r')
	demc = fread2.read().decode('utf8')
	input3 = demc[6:-15]
	fread3 = open('demd.p', 'r')
	demd = fread3.read().decode('utf8')
	input4 = demd[6:-15]
	if "code" in request.POST:
		input = request.POST['code']
		x = u'demoʖ\n'
		y = u'\n━━o(･ω･｀) demo'
		demo = x + input + y
		f = open('demo.p', 'w')
		f.write(demo.encode('utf8'))
		f.close()
		out, returncode = run("sh -c " + quote('./parser demo.p'), withexitstatus=1)
		if not out.strip():
			res = subprocess.Popen('java -jar jasmin-2.4/jasmin.jar demo.j;java demo', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout
			res.readline()
			return render(request, 'index.html', {'result': res.read(), 'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})
		else:
			return render(request, 'index.html', {'result':out, 'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})
	input = input1
	return render(request, 'index.html', {'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})

	