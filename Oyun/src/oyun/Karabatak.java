package oyun;

public class Karabatak extends OyunNesnesi {
    
    public Karabatak(String ad, int xCoord, int yCoord, int xHiz, int yHiz)
    {
        super(ad, xCoord, yCoord, xHiz, yHiz);
    }

    @Override
    public void hareketEt()
    {
        int yeniX = this.xCoord + this.xHiz;
        int yeniY = this.yCoord + this.yHiz;
        
        if(yeniY > 20) {
            this.yCoord -= (yeniY - 20);
            this.yHiz = -this.yHiz;
        }
        
        if(yeniY < 5) {
            this.yCoord = -yeniY + 5;
            this.yHiz = -this.yHiz;
        }
        
        if(yeniX > 20) {
            this.xCoord -= yeniX - 20;
            this.xHiz = -this.xHiz;
        }
        
        if(yeniX < 0) {
            this.xCoord = -yeniX;
            this.xHiz = -this.xHiz;
        }
    }
    
    @Override
    public String toString()
    {
        return super.toString() + " Yenilen Hamsi: " + this.yenilenHamsi;
    }

}
