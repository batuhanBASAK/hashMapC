#include "hashmap.h"

int main()
{
    hashmap_t *map = init_hashmap();
    
    // put some entry
    put(map, "CSE101", "Introduction to computer science");
    put(map, "CSE107", "Introduction to computer science laboratory");
    put(map, "CSE102", "Computer programming");
    put(map, "CSE108", "Computer programming laboratory");
    put(map, "CSE222", "Data Structures and algorithms");
    put(map, "CSE232", "Logic circuits and design");
    put(map, "CSE241", "Object oriented programming");
    put(map, "CSE234", "Logic circuits and design laboratory");
    put(map, "CSE343", "Software engineering");

    // print map
    printMap(map);

    // test get function
    printf("key 'CSE241' maps '%s'\n", get(map, "CSE241"));
    

    // test put method to change content of value for a key.
    put(map, "CSE232", "Logic");
    printf("CSE232 maps '%s' after put function\n", get(map, "CSE232"));


    // deallocate map
    delete_hashmap(&map);
    return 0;
}


