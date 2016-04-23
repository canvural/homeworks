#include <stdio.h>
#include <time.h>

#include <curses.h>

// Oyuncunun skoru
int points = 0;

// Oyuncu engele çarptığında GAME OVER yazmak için
void lost()
{
	clear();
	refresh();
	endwin();
	printf("GAME OVER\n");
	printf("Total Score: %d", points);
}

int main()
{
	// Rastgele sayı oluşturmak için üreticiyi başlatıyoruz.
	srand(time(NULL));
	
	WINDOW *window = initscr();
    curs_set(0);
    cbreak();
	nodelay(window, TRUE);
	noecho();

	// Engellerin koordinatları
	int obstacleX = 0, obstacleY = rand() % 18 + 1;

	char obstacle = 219;
	char car = 'X';

	// Arabanın koordinatları
	int carX = 18, carY = 8;

	int i, k, j, c;

	// Oyunun oynanacağı harita
	char map[20][20];

	// Haritanın içini boşlukla doldurup, sınırları belirliyoruz
    for(i = 0; i < 20; ++i) {
    	for(k = 0; k < 20; ++k) {
    		map[i][k]  = ' ';
    	}
    	map[i][0]  = '|';
    	map[i][19] = '|';
    }

    // Sonsuz döngüye girip oyunu oynuyoruz. Çıkmak için q ya basılacak
    for(;;) {
		clear();

		c = wgetch(window);

		switch(c) {
			case 'd':
				// Sınırların dışına çıkmasın diye kontrol
				if((carY + 1 < 20) && map[carX][carY + 1] != '|') {
					if(map[carX][carY + 1] == obstacle) {
						lost();
						return 0;
					}
					map[carX][carY] = ' ';
		    		carY++;
		    		map[carX][carY] = car;
		    	}
			break;
			case 'a':
				if((carY - 1 >= 0) && map[carX][carY - 1] != '|') {
					if(map[carX][carY - 1] == obstacle) {
						lost();
						return 0;
					}
					map[carX][carY] = ' ';
			    	carY--;
			    	map[carX][carY] = car;
			    }
			break;
			case 'q':
				lost();
				return 0;
			break;
		}

		// Arabayı haritaya koyuyoruz
		map[carX][carY] = car;

	    // Engelleri haritaya koyuyoruz
	    if((obstacleX + 1 < 20) && map[obstacleX + 1][obstacleY] == car) {
	    	lost();
	    	return 0;
	    }
      	map[obstacleX][obstacleY] = ' ';
      	obstacleX++;
      	map[obstacleX][obstacleY] = obstacle;
        if(obstacleX > 20) {
        	obstacleX = 0;
        	obstacleY = rand() % 18 + 1;
        }

        // Haritayı yazıyoruz
	    for(i = 0; i < 20; ++i) {
	    	for(j = 0; j < 20; ++j) {
	    		printw("%c", map[i][j]);
	    		refresh();
	    	}
	    	printw("\n");
	    	refresh();
	    }

	    printw("Points: %d", points);
	    refresh();

	    points++;

	    // Ne kadar hızlı gideceğini burası kontrol ediyor. Sayıyı değiştirip görebilirsiniz nolduğunu
	    usleep(60000);
    }

    endwin();

	return 0;
}