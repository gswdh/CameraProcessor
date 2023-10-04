import os

suffixes = ['.h', '.c', '.tcl']

files = []

for root, directories, filenames in os.walk('.'):
	for filename in filenames:
		for suffix in suffixes:
			if suffix in filename:
				file = os.path.join(root, filename)
				files.append(file)


for file in files:
	changed = False
	f = open(file, 'r')
	try:
		data = f.read()
	except:
		pass
	else:
		if '#define configTICK_RATE_HZ (100)' in data:
			data = data.replace('#define configTICK_RATE_HZ (100)', '#define configTICK_RATE_HZ (1000)')
			changed = True
		if 'mask_write 0XF8000100 0x00000010 0x00000010' in data:
			data = data.replace('mask_write 0XF8000100 0x00000010 0x00000010', 'mask_write 0XF8000100 0x00000018 0x00000010')
			changed = True
		if 'mask_write 0XF8000104 0x00000010 0x00000010' in data:
			data = data.replace('mask_write 0XF8000104 0x00000010 0x00000010', 'mask_write 0XF8000104 0x00000018 0x00000010')
			changed = True
		if 'mask_write 0XF8000108 0x00000010 0x00000010' in data:
			data = data.replace('mask_write 0XF8000108 0x00000010 0x00000010', 'mask_write 0XF8000108 0x00000018 0x00000010')
			changed = True
		if '0XF8000100, 0x00000010U ,0x00000010U' in data:
			data = data.replace('0XF8000100, 0x00000010U ,0x00000010U', '0XF8000100, 0x00000018U ,0x00000010U')
			changed = True
		if '0XF8000104, 0x00000010U ,0x00000010U' in data:
			data = data.replace('0XF8000104, 0x00000010U ,0x00000010U', '0XF8000104, 0x00000018U ,0x00000010U')
			changed = True
		if '0XF8000108, 0x00000010U ,0x00000010U' in data:
			data = data.replace('0XF8000108, 0x00000010U ,0x00000010U', '0XF8000108, 0x00000018U ,0x00000010U')
			changed = True
		f.close()

		if changed:
			print(f'Changed {file}')
			f = open(file, 'w')
			f.write(data)
			f.close()
