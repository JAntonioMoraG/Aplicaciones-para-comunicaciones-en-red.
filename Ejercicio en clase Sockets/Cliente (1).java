import java.net.Socket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;
import java.lang.Thread;
import java.util.Scanner;

class Cliente
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

  public static void main(String[] args) throws Exception
  {
    Socket conexion = null;
    
    for(int i = 0; i<500000; i++){
      try
      {
    	  conexion = new Socket("localhost",50000);
          break;
      }
      catch (Exception e)
      {
        Thread.sleep(13000);
      }      
    }

    DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
    DataInputStream entrada = new DataInputStream(conexion.getInputStream());
    boolean fish = false;
    String mensajeRecv, mensajeEnvi;
    int longitud;
    Scanner teclado = new Scanner(System.in);
    while(fish != true){
      longitud = entrada.readInt();
      byte[] buffer = new byte[longitud];
      read(entrada,buffer,0,longitud);
      System.out.println(new String(buffer,"UTF-8"));
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
    }
  }
}