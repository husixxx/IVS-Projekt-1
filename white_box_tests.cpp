//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//
using namespace ::testing;


class EmptyHashMap : public Test{
    void SetUp(){
        map = hash_map_ctor();
        
    }
    protected:
    hash_map_t* map;
};

class NonEmptyHashMap : public Test{
    void SetUp(){
        map = hash_map_ctor();
        hash_map_put(map,"a",1);
        hash_map_put(map,"b",2);
        hash_map_put(map,"c",3);
        hash_map_put(map,"d",4);
        hash_map_put(map,"e",5);
        hash_map_put(map,"f",6);
        
        
    }
    protected:
    hash_map_t* map;
};

TEST_F(EmptyHashMap, CreateTest){
    ASSERT_TRUE(map != NULL);
    ASSERT_TRUE(map->index != NULL);
    ASSERT_EQ(map->allocated, HASH_MAP_INIT_SIZE);
    ASSERT_EQ(map->used,0);
    ASSERT_TRUE(map->first == NULL);
    ASSERT_TRUE(map->last==NULL);
    ASSERT_EQ(hash_map_contains(map,"hello123"),false);
    int value;
    ASSERT_EQ(hash_map_get(map,"hello",&value),KEY_ERROR);
    hash_map_dtor(map);
};
TEST_F(NonEmptyHashMap, CreateTest){
    ASSERT_TRUE(map != NULL);
    ASSERT_TRUE(map->index != NULL);
    ASSERT_EQ(map->allocated, hash_map_capacity(map));
    ASSERT_TRUE(map->used != 0);
    ASSERT_TRUE(map->first != NULL);
    ASSERT_TRUE(map->last != NULL);
    ASSERT_EQ(hash_map_contains(map,"hello123"),false);
    int value;
    ASSERT_EQ(hash_map_get(map,"hello",&value),KEY_ERROR);
    hash_map_dtor(map);
};
TEST_F(EmptyHashMap, PutTest){
    int value;
    int value2;
    ASSERT_EQ(hash_map_put(map,"hello",42), OK);
    ASSERT_EQ(hash_map_put(map,"supp",420), OK);
    ASSERT_EQ(hash_map_contains(map,"hello"),true);
    ASSERT_EQ(hash_map_contains(map,"hello123"),false);
    ASSERT_EQ(hash_map_get(map,"hello",&value),OK);
    ASSERT_EQ(value,42);
    ASSERT_EQ(hash_map_get(map,"hello123",&value),KEY_ERROR);
    size_t size = hash_map_size(map);
    ASSERT_EQ(hash_map_pop(map,"hello",&value2),OK);
    ASSERT_EQ(hash_map_get(map,"hello",&value2),KEY_ERROR);
    ASSERT_EQ(hash_map_contains(map,"hello"),false);
    hash_map_dtor(map);

}
TEST_F(EmptyHashMap, GetTest){
    int val;
    ASSERT_EQ(hash_map_get(map,"a",&val), KEY_ERROR);
    ASSERT_EQ(hash_map_contains(map,"a"),false);
    hash_map_dtor(map);
}
TEST_F(NonEmptyHashMap, GetTest){
    int val;
    int val2;
    ASSERT_EQ(hash_map_get(map,"a",&val), OK);
    ASSERT_EQ(hash_map_get(map,"a",&val2), OK);
    ASSERT_EQ(val,val2);
    ASSERT_EQ(hash_map_contains(map,"a"),true);
    hash_map_dtor(map);
}

TEST_F(NonEmptyHashMap, PutTest){
    int value;
    int value2;
    ASSERT_EQ(hash_map_put(map,"hello",42), OK);
    ASSERT_EQ(hash_map_put(map,"supp",420), OK);
    ASSERT_EQ(hash_map_contains(map,"hello"),true);
    ASSERT_EQ(hash_map_contains(map,"hello123"),false);
    ASSERT_EQ(hash_map_get(map,"hello",&value),OK);
    ASSERT_EQ(value,42);
    ASSERT_EQ(hash_map_get(map,"hello123",&value),KEY_ERROR);
    size_t size = hash_map_size(map);
    ASSERT_EQ(hash_map_pop(map,"hello",&value2),OK);
    ASSERT_EQ(hash_map_get(map,"hello",&value2),KEY_ERROR);
    ASSERT_EQ(hash_map_contains(map,"hello"),false);
    hash_map_dtor(map);
}
TEST_F(EmptyHashMap, DeleteTest){
    ASSERT_EQ(hash_map_remove(map,"NON"),KEY_ERROR);
    ASSERT_EQ(hash_map_remove(map,"AWOJ"),KEY_ERROR);
    hash_map_dtor(map);

}
TEST_F(NonEmptyHashMap, DeleteTest){
    ASSERT_EQ(hash_map_remove(map,"NON"),KEY_ERROR);
    ASSERT_TRUE(hash_map_contains(map,"a"));
    ASSERT_EQ(hash_map_remove(map,"a"),OK);
    ASSERT_FALSE(hash_map_contains(map,"a"));
    hash_map_dtor(map);

}
TEST_F(NonEmptyHashMap, FailTest){
    ASSERT_EQ(hash_map_put(map,"a",1),KEY_ALREADY_EXISTS);
    hash_map_reserve(map, 100);
    ASSERT_EQ(map->allocated, 100);
    hash_map_dtor(map);
}
/*** Konec souboru white_box_tests.cpp ***/
