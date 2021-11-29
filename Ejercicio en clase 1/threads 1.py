import threading
import os
import threading as th
import random


numeros=[]
for i in range((random.randint(1,300))-2):
    numeros.append(random.randint(0,100000000000))

f=open('numeros.txt','w')
for i in range(100):
    f.write(str(numeros[i])+' ')

f.close()
print("Ingrese numero de hilos a usar")
entrada=input()
numhilos=int(entrada)
ruta="./numeros.txt"
tama=os.path.getsize(ruta)
hilobytes=int(tama/numhilos)
cont=0
conth=1;
def worker():
      datos=[]
      datos.append(f.readline(hilobytes))
      datosString = ' '.join(datos)
      datoslista=datosString.split()
      datoslista.sort()
      print(datoslista)
      

threads=[]
f=open('numeros.txt','r')
for i in range(numhilos):
    t = threading.Thread(target=worker)
    threads.append(t)
    t.start()
    print("hola soy el hilo %d y estos son mis numeros ordenados" %conth)
    conth=conth+1
    cont=cont+hilobytes
    t.join
    
