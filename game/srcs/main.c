#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "../../hdrs/structs_hash.h"
#include "../../hdrs/freefuncs.h"
#include "../../hdrs/hashfuncs.h"
#include "../../hdrs/sdlfuncs.h"
#include "../../hdrs/dbfuncs.h"
#include "../../hdrs/filefuncs.h"

int main(int argc, char* argv[]) {
    hashtable* ht = create_ht();
    
    if(!gameloop()) {
        freeht(ht); 
        return 1;
    } 

    freeht(ht);

    return 0;
}