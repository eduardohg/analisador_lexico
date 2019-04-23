import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.Scanner;

public class lexico {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Digite o caminho do arquivo pascal");
		String path = "C:/Users/guilh/Desktop/pascal.txt";
		System.out.println("Abrindo..." + path);
		
		BufferedReader reader = new BufferedReader(
			    new InputStreamReader(
			        new FileInputStream(path),
			        Charset.forName("UTF-8")));
			int c;
			while((c = reader.read()) != -1) {
			  char character = (char) c;
			  System.out.print(character);
			  
			  //analisadorLexico aqui
			}
			
		
	
			
		}
	 
	}


