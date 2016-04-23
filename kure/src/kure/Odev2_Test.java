package kure;

import java.util.Scanner;

public class Odev2_Test
{

    public static void main(String[] args)
    {
        Odev2 kure1 = new Odev2();
        Odev2 kure2 = new Odev2();
        
        Scanner s = new Scanner(System.in);
        
        kure1.setKure(s.nextLine());
        kure2.setKure(s.nextLine());
        
        kure1.bilgileriYazdir();
        kure2.bilgileriYazdir();
        
        kure1.kesiyorMu(kure2);
        kure1.ayniMi(kure2);
        
        int i = s.nextInt();
        kure1.hacimKiyasla(kure2, i);
        
        s.close();
    }
    
}
