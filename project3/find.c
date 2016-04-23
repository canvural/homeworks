#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void find(char *fn,char *dir);

int main(int argc, char *argv[])
{
    char *fn = NULL;
    char *dir = NULL;

    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "f:d:")) != -1) {
        switch (c) {
            case 'f':
            fn = optarg;
            break;
            case 'd':
            dir = optarg;
            break;
            default:
            return 1;
        }
    }

    find(fn, dir);

    return 0;
}



// Parametre olarak bir dosya ismi ve içinde arama yapılacak klasör ismi alıyor.
// Klasörü recursive olarak tarıyor.
void find(char *fn, char *dire)
{
    int found = 0;

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(dire)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        // Klasörün içinde başka bir klasör varsa, o klasörü de tarıyoruz.
        if (entry->d_type == DT_DIR) {
            char p[1024];
            strcpy(p, dire);
            strcat(p, "/");
            strcat(p, entry->d_name);
            // Şimdiki ve bir üst klasörü temsil eden . ve .. yı es geçiyoruz.
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            find(fn, p);
        }
        else {
            if((strcmp(fn, entry->d_name)) == 0) {
                found = 1;

                struct stat file_stats;

                char file[1024];
                strcpy(file, dire);
                strcat(file, "/");
                strcat(file, entry->d_name);

                // Dosyanın bilgilerini alıyoruz
                if((stat(file, &file_stats)) == -1) {
                     return;
                }

                printf("%s/%s,\t%ld,\t%ld,\t%s\n",
                        dire,
                        entry->d_name,
                        file_stats.st_ino,
                        file_stats.st_size,
                        ctime(&file_stats.st_mtime)
                );
            }
        }
    } while (entry = readdir(dir));

    if(!found) {
        printf("File %s could not be found in %s\n", fn, dire);
    }

    closedir(dir);
}
