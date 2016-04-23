package oyun;

public class OyunMotoru
{
    public OyunNesnesi[] nesneler;
    public int sure;
    public int currentId = 0;
    
    public OyunMotoru(int nesneSayisi, int sure)
    {
        this.nesneler = new OyunNesnesi[nesneSayisi];
        this.sure = sure;
    }
    
    public void oyunNesnesiEkle(OyunNesnesi nesne)
    {
        this.nesneler[this.currentId++] = nesne;
    }
    
    public void oyunuBaslat()
    {
        int i;
        
        for(i = 1; i <= this.sure; i++) {
            int j;
            
            // Bütün nesneleri hareket ettir
            for(j = 0; j < this.nesneler.length; j++) {
                this.nesneler[j].hareketEt();
            }
            
            this.carpismaKontrol();
            
            for(j = 0; j < this.nesneler.length; j++) {
                System.out.println(this.nesneler[j]);
            }
        }
    }
    
    public void carpismaKontrol()
    {
        for (int j = 0; j < this.nesneler.length; j++) {
            for (int i = j + 1; i < this.nesneler.length; i++) {
                if ((this.nesneler[j].xCoord == this.nesneler[i].xCoord)
                        && (this.nesneler[j].yCoord == this.nesneler[i].yCoord)) {
                    if ((this.nesneler[j] instanceof Yunus && this.nesneler[i] instanceof Hamsi)
                            || (this.nesneler[j] instanceof Karabatak && this.nesneler[i] instanceof Hamsi)
                            || (this.nesneler[i] instanceof Yunus && this.nesneler[j] instanceof Hamsi)
                            || (this.nesneler[i] instanceof Karabatak && this.nesneler[j] instanceof Hamsi)) {
                    // Yenilen hamsiye ne olacağınıa burada siz karar verebilirsiniz.
                        // Ben sadece koordinatlarını ve hızını sıfırladım.
                        this.nesneler[i].xCoord = 0;
                        this.nesneler[i].yCoord = 0;
                        this.nesneler[i].xHiz = 0;
                        this.nesneler[i].yHiz = 0;

                        this.nesneler[j].yenilenHamsi++;
                    }
                }
            }
        }
    }
}
