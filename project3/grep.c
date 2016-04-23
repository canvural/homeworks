#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// 4 modes for operations
#define LIST_MOD 1
#define COPY_MOD 2
#define RENAME_MOD 3
#define DELETE_MOD 4

// Global variable for the operation
int mod = 0;

const char *search_word      = NULL,
           *search_directory = NULL,
           *copy_directory   = NULL,
           *rename_word      = NULL;

void search(const char *search_word, const char *search_directory);
char *read_line(FILE *file);
void search_word_in_file(char *file_name, const char *search_word, const char *directory);
void copy_files(char *file_name, const char *search_word, const char *search_directory, const char *copy_directory);
void delete_files(char *file_name, const char *search_word, const char *search_directory);
void rename_file(char *file_name, const char *search_word, const char *directory, const char *new_ext);

int main(int argc, char *argv[])
{
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "xlw:d:c:r:")) != -1) {
        switch (c) {
            case 'w':
                search_word = optarg;
            break;
            case 'd':
                search_directory = optarg;
            break;
            case 'l':
                mod = LIST_MOD;
            break;
            case 'c':
                copy_directory = optarg;
                mod = COPY_MOD;
            break;
            case 'r':
                rename_word = optarg;
                mod = RENAME_MOD;
            break;
            case 'x':
                mod = DELETE_MOD;
            break;
            case '?':
            return 1;
            default:
            return 1;
        }
    }

    if(!mod) {
        printf("Please specify a mod!");
        return 1;
    }

    if(search_word == NULL) {
        printf("Please give a word to search!");
        return 1;
    }

    if(search_directory == NULL) {
        printf("Please give a search directory!");
        return 1;
    }

    search(search_word, search_directory);

    return 0;
}

void search(const char *search_word, const char *search_directory)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(search_directory)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        // If it is a directory, search recursively
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path) - 1, "%s/%s", search_directory, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            search(search_word, path);
        }
        else {
            // Check if the file is a text file by checking if
            // it contains .txt
            const char *txt = ".txt";

            // If it is not a text file, skip it
            if(strstr(entry->d_name, txt) == NULL) {
                continue;
            }

            switch(mod) {
                case LIST_MOD:
                    search_word_in_file(entry->d_name, search_word, search_directory);
                break;
                case COPY_MOD:
                    copy_files(entry->d_name, search_word, search_directory, copy_directory);
                break;
                case DELETE_MOD:
                    delete_files(entry->d_name, search_word, search_directory);
                break;
                case RENAME_MOD:
                    rename_file(entry->d_name, search_word, search_directory, rename_word);
                break;
                default:
                    printf("You didn't select a mod!!");
                return;
            }
        }
    } while (entry = readdir(dir));

    closedir(dir);
}

void search_word_in_file(char *file_name, const char *search_word, const char *directory)
{
    char file_path[1024];
    int len = snprintf(file_path, sizeof(file_path) - 1, "%s/%s", directory, file_name);
    file_path[len] = 0;

    FILE *f = fopen(file_path, "r");
    if(NULL == f) {
        printf("Can't open %s for reading\n", file_path);
        perror("Actual error: ");
        return;
    }

    char *line = NULL;
    int line_number = 1;

    // We are gonna read the file line by line
    while((line = read_line(f)) != NULL) {
        if(strstr(line, search_word) != NULL) {
            // We found our word in a line
            // So print it
            printf(
                "%s, line %d, %s\n",
                file_path,
                line_number,
                line
            );
        }

        line_number++;
        free(line);
    }

    fclose(f);
}

void copy_files(char *file_name, const char *search_word, const char *search_directory, const char *copy_directory)
{
    char file_path[1024];
    char target_path[1024];
    int len = snprintf(file_path, sizeof(file_path) - 1, "%s/%s", search_directory, file_name);
    int lenn = snprintf(target_path, sizeof(target_path) - 1, "%s/%s", copy_directory, file_name);
    file_path[len] = 0;
    target_path[lenn] = 0;

    FILE *f = fopen(file_path, "r");
    if(NULL == f) {
        printf("Can't open %s for reading\n", file_path);
        perror("Actual error: ");
        return;
    }

    // Create target directory if its not exists
    if(mkdir(copy_directory, 0777) == 0) {
        printf("Directory %s does not exist, created\n", copy_directory);
    }

    char *line = NULL;

    // We are gonna read the file line by line
    while((line = read_line(f)) != NULL) {
        if(strstr(line, search_word) != NULL) {
            // We found our word in a line
            // copy it to the target directory
            FILE *target = fopen(target_path, "w");
            if(NULL == target) {
                printf("Can't open %s for writing\n", target_path);
                perror("Actual error: ");
                return;
            }

            char ch;

            // Copy the file char by char
            while((ch = fgetc(f) )!= EOF )
                fputc(ch, target);

            printf("Copied %s to %s\n", file_path, copy_directory);
            fclose(target);
            break;
        }
        free(line);
    }

    fclose(f);
}

void delete_files(char *file_name, const char *search_word, const char *search_directory)
{
    char file_path[1024];
    int len = snprintf(file_path, sizeof(file_path) - 1, "%s/%s", search_directory, file_name);
    file_path[len] = 0;

    FILE *f = fopen(file_path, "r");
    if(NULL == f) {
        printf("Can't open %s for reading\n", file_path);
        perror("Actual error: ");
        return;
    }

    char *line = NULL;

    // We are gonna read the file line by line
    while((line = read_line(f)) != NULL) {
        if(strstr(line, search_word) != NULL) {
            // We found our word in a line
            // First close the file
            fclose(f);

            // Then delete
            if(unlink(file_path) == 0) {
                printf("Found and deleted %s\n", file_path);
            } else {
                perror("Error while deleting file: ");
            }

            // We deleted the file. So our work is done
            free(line);
            return;
        }
        free(line);
    }

    fclose(f);
}

void rename_file(char *file_name, const char *search_word, const char *directory, const char *new_ext)
{
    char new_name[255];
    sscanf(file_name, "%[^.]", new_name);
    sprintf(new_name, "%s.%s", new_name, new_ext);

    char file_path[1024];
    char new_file_path[1024];
    int len = snprintf(file_path, sizeof(file_path) - 1, "%s/%s", directory, file_name);
    int lenn = snprintf(new_file_path, sizeof(new_file_path) - 1, "%s/%s", directory, new_name);
    file_path[len] = 0;
    new_file_path[lenn] = 0;

    FILE *f = fopen(file_path, "r");
    if(NULL == f) {
        printf("Can't open %s for reading\n", file_path);
        perror("Actual error: ");
        return;
    }

    char *line = NULL;
    int line_number = 1;

    // We are gonna read the file line by line
    while((line = read_line(f)) != NULL) {
        if(strstr(line, search_word) != NULL) {
            // We found our word in a line

            fclose(f);

            if(rename(file_path, new_file_path) == -1) {
                perror("Renaming a file failed: ");
            } else {
                printf("Renamed %s as %s\n", file_path, new_file_path);
            }

            free(line);
            return;
        }

        line_number++;
        free(line);
    }

    fclose(f);
}

char *read_line(FILE *file)
{
    if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        return NULL;
    }

    // Allocate 255 byte for one line. +1 for NULL terminator.
    char *line = malloc(1024);
    if (line == NULL) {
        fprintf(stderr, "Can not allocate memory for line buffer!");
        return NULL;
    }

    if(fgets(line, 1024, file) != NULL) {
        size_t ln = strlen(line) - 1;
        if (line[ln] == '\n')
            line[ln] = '\0';
        if (line[ln - 1] == '\r')
            line[ln - 1] = '\0';
        return line;
    }

    // There should be an error if we are here so
    // free the allocated space and return NULL
    free(line);
    return NULL;
}
