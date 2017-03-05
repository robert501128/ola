from django.shortcuts import render
import subprocess
import os

curdir = os.getcwd()
# Create your views here.
def hello_world(request):
	os.chdir(curdir + "/ola_compiler")
	if "code" in request.POST:
		input = request.POST['code'].encode('utf8')
		x = 'demo\xca\x96\n'
		y = '\n\xe2\x94\x81\xe2\x94\x81o(\xef\xbd\xa5\xcf\x89\xef\xbd\xa5\xef\xbd\x80) demo'
		demo = x + input + y
		f = open('demo.p', 'w')
		f.write(demo)
		f.close()
		p = subprocess.Popen('./parser demo.p', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout.read()
		print p
		
		if not p.strip():
			subprocess.Popen('java -jar jasmin-2.4/jasmin.jar demo.j', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
			res = subprocess.Popen('java demo', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout.read()
			return render(request, 'index.html', {'result': res, 'input': input})
		else:
			return render(request, 'index.html', {'result':p, 'input': input})
	fread = open('demo.p', 'r')
	demo = fread.read()
	input = demo[7:-26]
	return render(request, 'index.html', {'input': input})

	