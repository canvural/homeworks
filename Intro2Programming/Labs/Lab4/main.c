#include <stdio.h>
#include <unistd.h>

#include "worldutils.h"

int main(int argc, char *argv[]) {
    char **s;
    int min, size, c;
    int flag_case = 0,
        flag_exact = 0;
    char line[512];

    while ((c = getopt (argc, argv, "iIxXcCs:")) != -1) {
        switch (c) {
            case 'i':
            case 'I':
                flag_case = 1;
                break;
            case 'x':
            case 'X':
                flag_exact = 1;
                break;
            case 's':
                min = atoi(optarg);
                break;
            case '?':
                if (optopt == 's') {
                    printf("Option -%c requires an argument.\n", optopt);
                }

                return 1;
            default:
                return 1;
        }
    }

    s = argv + optind;
    size = argc - optind;

    set_min_number(min);

    while(fgets(line, sizeof(line), stdin) != NULL) {
        if(is_matching(line, s, size, flag_case, flag_exact)) {
            puts(line);
        }
    }

    return 0;
}
