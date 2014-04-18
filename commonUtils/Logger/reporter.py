import re
header = open ("./logger_files/header.html", 'r')
logTxt = open ("/home/pablon/Escritorio/concurrentes.log", 'r')
footer = open ("./logger_files/footer.html", 'r')
output = open ("log.html", 'w')

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

	if level == "FATAL":
		row += rowHeader.format("danger fatal")
	elif level == "INFO":
		row += rowHeader.format("info")
	elif level == "WARN":
		row += rowHeader.format("warning")
	elif level == "DEBUG":
		row += rowHeader.format("success debug")
	elif level == "ERROR":
		row += rowHeader.format("danger error")
	else:
		continue

	row += attribute.format(pid)
	row += attribute.format(fecha)
	row += attribute.format(level)
	row += attribute.format(tag)
	row += attribute.format(msj)

	output.write(row)

for line in footer:
		output.write(line)
