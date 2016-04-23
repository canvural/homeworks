package oyun;

public abstract class OyunNesnesi {
    public String ad;
    public int xCoord;
    public int yCoord;
    public int xHiz;
    public int yHiz;
    public int yenilenHamsi = 0;
    
    public OyunNesnesi(String ad, int xCoord, int yCoord, int xHiz, int yHiz)
    {
        this.ad = ad;
        this.xCoord = xCoord;
        this.yCoord = yCoord;
        this.xHiz = xHiz;
        this.yHiz = yHiz;
    }
    
    public abstract void hareketEt();
    
    @Override
    public String toString()
    {
        return this.ad + ", [" + this.xCoord + ", " + this.yCoord + "]";
    }
}
