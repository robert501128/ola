from django.shortcuts import render
import subprocess
import os

curdir = os.getcwd()
# Create your views here.
def hello_world(request):
	os.chdir(curdir + "/ola_compiler")
	fread = open('dema.p', 'r')
	dema = fread.read()
	input1 = dema[7:-26]
	fread = open('demb.p', 'r')
	demb = fread.read()
	input2 = demb[7:-26]
	fread = open('demc.p', 'r')
	demc = fread.read()
	input3 = demc[7:-26]
	fread = open('demd.p', 'r')
	demd = fread.read()
	input4 = demd[7:-26]
	if "code" in request.POST:
		input = request.POST['code'].encode('utf8')
		x = 'demo\xca\x96\n'
		y = '\n\xe2\x94\x81\xe2\x94\x81o(\xef\xbd\xa5\xcf\x89\xef\xbd\xa5\xef\xbd\x80) demo'
		demo = x + input + y
		f = open('demo.p', 'w')
		f.write(demo)
		f.close()

		p = subprocess.Popen('./parser demo.p', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout.read()
		if not p.strip():
			res = subprocess.Popen('java -jar jasmin-2.4/jasmin.jar demo.j;java demo', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout
			res.readline()
			return render(request, 'index.html', {'result': res.read(), 'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})
		else:
			return render(request, 'index.html', {'result':p, 'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})
	input = input1
	return render(request, 'index.html', {'input': input, 'input1': input1, 'input2': input2, 'input3': input3, 'input4': input4})

	