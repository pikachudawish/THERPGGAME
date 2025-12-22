#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "structs_hash.h"
#include "freefuncs.h"
#include "hashfuncs.h"

int main(int argc, char* argv[]) {
    hashtable* ht = create_ht();
    
    if(!gameloop()) {
        freeht(ht); 
        return 1;
    } 

    freeht(ht);

    return 0;
}