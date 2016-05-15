#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <chrono>

// BST

//using namespace std;
using namespace std::chrono;

#include "uthash.h"

struct ht {
    const char *word;                    /* key */
    int count;
    UT_hash_handle hh;         /* makes this structure hashable */
};

int name_sort(struct ht *a, struct ht *b) {
    return (b->count - a->count);
}

struct alphabet_only: std::ctype<char> 
{
        alphabet_only(): std::ctype<char>(get_table()) {}

        static std::ctype_base::mask const* get_table()
        {
            static std::vector<std::ctype_base::mask> 
                rc(std::ctype<char>::table_size,std::ctype_base::space);

            std::fill(&rc['A'], &rc['['], std::ctype_base::upper);
            std::fill(&rc['a'], &rc['{'], std::ctype_base::lower);
            return &rc[0];
        }
};

int main()
{
    std::ifstream file;
    file.open ("big.txt");

    file.imbue(std::locale(std::locale(), new alphabet_only()));
    struct ht *s, *words = NULL;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    std::string word;
    while (file >> word) {

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        char *w;
        w = new char[word.size() + 1];
        std::copy(word.begin(), word.end(), w);
        w[word.size()] = '\0';

        HASH_FIND_STR(words, w, s);  /* id already in the hash? */
        if (s==NULL) {
            s = (struct ht *) malloc(sizeof(struct ht));
            s->count = 1;
            s->word = w;
            HASH_ADD_KEYPTR(hh, words, w, word.size(), s);
        } else {
            s->count++;
        }
    }

    HASH_SORT(words, name_sort);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

	int i = 0;
    for(s=words; s != NULL; s=(struct ht *)s->hh.next) {
    	if(i >= 10) break;
        printf("%d %s\n", s->count, s->word);
        i++;         
    }
    
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    std::cout << duration;

    return 0;
}

