/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oyun;

import java.util.Random;

/**
 *
 * @author can
 */
public class Test
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        OyunMotoru m = new OyunMotoru(12, 100000);
        
        // Hamsiler
        for(int i = 0; i < 10; i++) {
            Hamsi h = new Hamsi("Hamsi-" + (i + 1), 
                    getRandomNumberForGrid(20),
                    getRandomNumberForGrid(10),
                    getRandomNumberForGrid(5),
                    getRandomNumberForGrid(5)
            );
            
            m.oyunNesnesiEkle(h);
        }
        
        Yunus y = new Yunus("Yunus", 
                    getRandomNumberForGrid(20),
                    getRandomNumberForGrid(12),
                    getRandomNumberForGrid(10),
                    getRandomNumberForGrid(10)
        );
        
        m.oyunNesnesiEkle(y);
        
        Karabatak k = new Karabatak("Karabatak", 
                    getRandomNumberForGrid(20),
                    getRandomNumberForGrid(5) + 15,
                    getRandomNumberForGrid(7),
                    getRandomNumberForGrid(7)
        );
        
        m.oyunNesnesiEkle(k);
        
        
        m.oyunuBaslat();
    }
    
    private static int getRandomNumberForGrid(int max)
    {
        Random rand = new Random();
        
        int r = rand.nextInt(max);
        return r == 0 ? 1 : r;
    }
}
