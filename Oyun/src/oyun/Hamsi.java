package oyun;

public class Hamsi extends OyunNesnesi {

    public Hamsi(String ad, int xCoord, int yCoord, int xHiz, int yHiz)
    {
        super(ad, xCoord, yCoord, xHiz, yHiz);
    }

    @Override
    public void hareketEt()
    {
        this.xCoord += this.xHiz;
        this.yCoord += this.yHiz;
        
        if(this.yCoord > 10) {
            this.yCoord -= (this.yCoord - 10);
            // Denizin en üstüne geldiğinde, hızı değiştirip diğer tarafa doğru
            // gidecek.
            this.yHiz = -this.yHiz;
        }
        
        if(this.yCoord < 0) {
            this.yCoord = -this.yCoord;
            this.yHiz = -this.yHiz;
        }
        
        if(this.xCoord > 20) {
            this.xCoord -= this.xCoord - 20;
            this.xHiz = -this.xHiz;
        }
        
        if(this.xCoord < 0) {
            this.xCoord = -this.xCoord;
            this.xHiz = -this.xHiz;
        }
    }
}
