import java.io.*;
import java.util.*;
import java.text.*;;

public class Prelab4 {

	public static final Scanner scan = new Scanner(System.in);

	public static void main(String[] args) throws FileNotFoundException {

		System.out.print("Enter case number: ");
		int caseVal = scan.nextInt();
		Scanner scanFile = new Scanner(new File("Employee.txt"));
		NumberFormat fmt = NumberFormat.getCurrencyInstance(Locale.US);

		switch(caseVal)
		{
			case 1:
				int quality = 0;
				int production = 0;
				int accounting = 0;
				int purchasing = 0;
				String line;

				while(scanFile.hasNextLine()) {
				   	line = scanFile.nextLine();
					if(line.indexOf("Quality") != -1) {
						quality++;
					} else if(line.indexOf("Production") != -1) {
						production++;
					} else if(line.indexOf("Accounting") != -1) {
						accounting++;
					} else if(line.indexOf("Purchasing") != -1) {
						purchasing++;
					}
				}

				System.out.printf("The Number of Employees in Quality Department: %d\n", quality);
				System.out.printf("The Number of Employees in Production Department: %d\n", production);
				System.out.printf("The Number of Employees in Accounting Department: %d\n", accounting);
				System.out.printf("The Number of Employees in Purchasing Department: %d\n", purchasing);
				break;
			case 2:
				System.out.print("Enter salary: ");
				int salary = scan.nextInt();

				if(salary < 100) {
					System.out.println("Salary must be bigger than 100");
					System.exit(1);
				} else if(salary > 1000) {
					System.out.println("There is no employee has this salary.");
					System.exit(1);
				}

				while(scanFile.hasNextLine()) {
				   	line = scanFile.nextLine();

				   	String[] split = line.split(" ");
				   	int eSalary = Integer.parseInt(split[split.length - 2]);

				   	if(eSalary > salary) {
						System.out.printf("%s %s %s\n", split[0], split[1], fmt.format(eSalary));
				   	}
				}
				break;
			case 3:
				while(scanFile.hasNextLine()) {
				   	line = scanFile.nextLine();

				   	String[] split = line.split(" ");

				   	if(split[2].equals("Ankara") || split[2].equals("Istanbul")) {
				   		System.out.printf("%s %s %s\n", split[split.length - 1], split[0], split[1].toUpperCase() );
				   	}
				}
				break;
		    case 4:
		    		while(scanFile.hasNextLine()) {
				   	line = scanFile.nextLine();

				   	String[] split = line.split(" ");
				   	String[] tarih = split[split.length - 1].split("/");
				   	int yil = Integer.parseInt(tarih[tarih.length - 1]);
				   	int eSalary = Integer.parseInt(split[split.length - 2]);

				   	if(yil >= 2010) {
				   	   	int yeni = eSalary + (eSalary * 15)/100;
				   		System.out.printf("%s %s %s\n",split[0], split[1], fmt.format(yeni));
				   	}
				}
				break;
			case 5:
				while(scanFile.hasNextLine()) {
				   	line = scanFile.nextLine();

				   	String[] split = line.split(" ");
				   	String name = split[0];

				   	if(name.length() > 5) {
				   		String[] tarih = split[split.length - 1].split("/");
				   		System.out.printf("%s %s-%s-%s\n", name, tarih[0], tarih[1], tarih[2]);
				   	}
				}
				break;
		}
	}
}
