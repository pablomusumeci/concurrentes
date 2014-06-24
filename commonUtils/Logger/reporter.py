import re
header = open ("./logger_files/header.html", 'r')
logTxt = open ("/home/pablon/Escritorio/concurrentes.log", 'r')
footer = open ("./logger_files/footer.html", 'r')
middle = open ("./logger_files/middle.html", 'r')
tmp = []
output = open ("log.html", 'w')
pids = []
for line in header:
	output.write(line)

for line in logTxt:
	r = re.split(r'\t+', line.rstrip('\t'))
	print r
	rowHeader =  "<tr class=\"{0}\">\n"
	attribute = "<td>{0}</td>\n"
	row = ""
	pid = r[0]
	fecha = r[1]
	level = r[2]
	tag = r[3]
	msj = r[4]
	if ("p_" + pid) not in pids: 
		pids.append("p_" + pid)

	if level == "FATAL":
		row += rowHeader.format("p_" + pid)
	elif level == "INFO":
		row += rowHeader.format("p_" + pid)
	elif level == "WARN":
		row += rowHeader.format("p_" + pid)
	elif level == "DEBUG":
		row += rowHeader.format("p_" + pid)
	elif level == "ERROR":
		row += rowHeader.format("p_" + pid)
	else:
		continue

	row += attribute.format(pid)
	row += attribute.format(fecha)
	row += attribute.format(level)
	row += attribute.format(tag)
	row += attribute.format(msj)

	tmp.append(row)#output.write(row)

for pid in sorted(pids):
	output.write("<button id=\"{0}Button\"type=\"button\" class=\"btn btn-sm btn-info\">{1}</button>".format(pid, pid[2:]))
for line in middle:
	output.write(line)
for line in tmp:
	output.write(line)	
for line in footer:
		output.write(line)

for pid in pids:
	output.write("$( \"#"+ pid +"Button\" ).click(function() {$( \"#filas tr." + pid + "\" ).toggleClass(\"success\");$( \"#"+ pid +"Button\" ).toggleClass(\"active\")});")
output.write("</script></body></html>")
