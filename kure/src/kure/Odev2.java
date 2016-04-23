package kure;

public class Odev2 {
    private double merkezX, merkezY, merkezZ;
    private double yaricap;
    public double pi = 3.14;
    
    public void setKure(String formul)
    {
        /**
         * formul stringi içinde "*x" stringinin pozisyonunu buluyoruz.
         * 
         * 18. karakterden başlayıp bu pozisyona kadar olan string bizim sayımız.
         * Formulün başındaki "x^2 + y^2 + z^2 + " kısmı sabit olduğu için 18
         * değerini kullanabiliriz.
         */
        
        int posX = formul.indexOf("*x");
        double x = Double.parseDouble(formul.substring(18, posX));
        
        // Diğerler değerler içinde aynı işlem.
        // +5 "*y + " stringini geçmek için
        int posY = formul.indexOf("*y", posX);
        double y = Double.parseDouble(formul.substring(posX + 5, posY));
        
        int posZ = formul.indexOf("*z", posY);
        double z = Double.parseDouble(formul.substring(posY + 5, posZ));
        
        double d = Double.parseDouble(formul.substring(posZ + 5, formul.indexOf(" =")));
        
        if(gecerliMi(x, y, z, d)) {
            merkezX = -x / 2;
            merkezY = -y / 2;
            merkezZ = -z / 2;
            yaricap = Math.sqrt(x*x + y*y + z*z - 4*d) / 2;
        } else {
            // Eğer geçerli bir küre değilse ne yapılması gerekiyor yazılmamış.
            // Sen kendin halledersin burayı.
        }
    }
    
    private boolean gecerliMi(double a, double b, double c, double d)
    {
        double delta = a*a + b*b + c*c - 4*d;
        
        return delta > 0;
    }
    
    public void bilgileriYazdir()
    {
        System.out.printf("%.2f, %.2f, %.2f, %.2f\n", merkezX, merkezY, merkezZ, yaricap);
        System.out.printf("%.2f\n", yuzeyAlani());
        System.out.printf("%.2f\n", hacmi());
    }
    
    public double yuzeyAlani()
    {
        return 4 * pi * yaricap * yaricap;
    }
    
    public double hacmi()
    {
        return (4/3) * pi * yaricap * yaricap * yaricap;
    }
    
    private double uzaklikHesapla(Odev2 kure)
    {
        return  Math.sqrt(
                (kure.getMerkezX() - merkezX) * (kure.getMerkezX() - merkezX) +
                (kure.getMerkezY() - merkezY) * (kure.getMerkezY() - merkezY) +
                (kure.getMerkezZ() - merkezZ) * (kure.getMerkezZ() - merkezZ)
        );
    }
    
    public boolean kesiyorMu(Odev2 kure)
    {
        if( uzaklikHesapla(kure) <= (yaricap + kure.getYaricap())) {
            System.out.println("Evet");
            return true;
        }
        
        System.out.println("Hayır");
        return false;
    }
    
    public boolean ayniMi(Odev2 kure)
    {
        if(merkezX == kure.getMerkezX() &&
                merkezY == kure.getMerkezY() &&
                merkezZ == kure.getMerkezZ() &&
                yaricap == kure.getYaricap()) {
            System.out.println("Evet");
            return true;
        }
        
        System.out.println("Hayır");
        return false;
    }
    
    public boolean hacimKiyasla(Odev2 kure, int i)
    {
        if(Math.abs(hacmi() - kure.hacmi()) < i) {
            System.out.println("Evet");
            return true;
        }
        
        System.out.println("Hayır");
        return false;
    }

    public double getMerkezX()
    {
        return merkezX;
    }

    public double getMerkezY()
    {
        return merkezY;
    }

    public double getMerkezZ()
    {
        return merkezZ;
    }

    public double getYaricap()
    {
        return yaricap;
    }
}
