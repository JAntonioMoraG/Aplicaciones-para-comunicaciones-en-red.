import java.net.Socket;
import java.net.ServerSocket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.lang.Thread;
import java.nio.ByteBuffer;
import java.util.Scanner;

class Servidor
{
  // lee del DataInputStream todos los bytes requeridos

  static void read(DataInputStream f,byte[] b,int posicion,int longitud) throws Exception
  {
    while (longitud > 0)
    {
      int n = f.read(b,posicion,longitud);
      posicion += n;
      longitud -= n;
    }
  }

  static class Worker extends Thread
  {
    Socket conexion;

    Worker(Socket conexion)
    {
      this.conexion = conexion;
    }

    public void run()
    {
      try
      {
        DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
        DataInputStream entrada = new DataInputStream(conexion.getInputStream());
        boolean fish = false;
        String mensajeRecv, mensajeEnvi;
        int longitud;
        Scanner teclado = new Scanner(System.in);


        while(fish != true){
          mensajeEnvi = teclado.nextLine();
          if(mensajeEnvi == "fish"){
            fish = true;
            salida.close();
            entrada.close();
            conexion.close();
          }else{
            salida.writeInt(mensajeEnvi.length());
            salida.write(mensajeEnvi.getBytes());
          }
          longitud = entrada.readInt();
          byte[] buffer = new byte[longitud];
          read(entrada,buffer,0,longitud);
          System.out.println(new String(buffer,"UTF-8"));
        }
      }
      catch (Exception e)
      {
        System.err.println(e.getMessage());
      }
    }
  }

  public static void main(String[] args) throws Exception
  {
    ServerSocket servidor = new ServerSocket(50000);

    while(true){
      Socket conexion = servidor.accept();
      Worker w = new Worker(conexion);
      w.start();
      //w.join();
    }
  }
}