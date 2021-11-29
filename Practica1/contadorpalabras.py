	import os
	import threading as th
	 
	 
	def worker(ruta, nombre, n_palabras, d_conteo, d_frecuencias):
	    f = open(ruta, encoding='utf-8')
	    texto = f.read()
	    f.close()
	    texto = texto.split()
	    total_palabras = len(texto)
	    n_palabras.append(total_palabras)
	    vocabulario = sorted(list(set(texto)))
	    conteos = list()
	    frecuencias = list()
	    for palabra in vocabulario:
	        conteo = texto.count(palabra)
	        frecuencia = conteo/total_palabras
	        conteos.append((palabra, conteo))
	        frecuencias.append((palabra, frecuencia))
	    d_conteo[nombre] = conteos
	    d_frecuencias[nombre] = frecuencias
	 
	 
	if __name__ == '__main__':
	    ruta = "./Archivos"
	    contenido = os.listdir(ruta)
	    hilos = list()
	    conteos_totales = list()
	    conteos_indi = dict()
	    frecuencias_indi = dict()
	   
	    for archivo in contenido:
	        t = th.Thread(target=worker, args=(ruta+'/'+archivo, archivo,conteos_totales, conteos_indi,frecuencias_indi,))
	        hilos.append(t)
	        t.start()
	        t.join()
	 
	    cuenta_total = 0
	    for cuenta in conteos_totales:
	        cuenta_total += cuenta
	    conteo_vocabulario = dict(zip(['amor','casa','enojo','jardin','juego','pelota'],[0,0,0,0,0,0]))
	    frecuencias_vocabulario = dict()
	    for key in conteos_indi:
	        lista = conteos_indi.get(key)
	        for tupla in lista:
	            conteo_vocabulario[tupla[0]] += tupla[1]
	    for key in conteo_vocabulario:
	        frecuencias_vocabulario[key] = conteo_vocabulario[key]/cuenta_total
	 
	    print("\nConteo de palabras de cada archivo:")
	    for key in conteos_indi:
	        lista = conteos_indi.get(key)
	        print("\nArchivo: "+key)
	        for tupla in lista:
	            print(tupla[0]+": %d"%tupla[1])
	   
	    print("\nFrecuencia de palabras de cada archivo:")
	    for key in frecuencias_indi:
	        lista = frecuencias_indi.get(key)
	        print("\nArchivo: "+key)
	        for tupla in lista:
	            print(tupla[0]+": %f"%tupla[1])
	           
	    print("\nConteo de palabras total en los archivos:")
	    for key in conteo_vocabulario:
	        print("\n"+key+": %d" %conteo_vocabulario[key])
	       
	    print("\nFrecuencias de palabras en todos los archivos:")
	    for key in frecuencias_vocabulario:
	        print("\n"+key+": %f" %frecuencias_vocabulario[key])
