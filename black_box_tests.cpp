//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu

//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//
using namespace ::testing;

class EmptyTree : public Test{

protected:
    BinaryTree testingTree;
};



class NonEmptyTree : public Test{

protected:
    virtual void SetUp(){
    int values[] = {1,2,3,4,5,6,7,8,9};
    for(auto it : values){
        testingTree.InsertNode(it);
        }
    }

    BinaryTree testingTree;
};

class TreeAxioms : public Test{

protected:
virtual void SetUp(){
    int values[] = {1,2,3,4,5,6,7,8,9};
    for(auto it : values){
        testingTree.InsertNode(it);
        }
    }
    BinaryTree testingTree;
};

TEST_F(EmptyTree, InsertNode){
    auto Node = testingTree.InsertNode(42);
    EXPECT_TRUE(Node.first);
    EXPECT_EQ(Node.second->key,42);
    auto Node_Two = testingTree.InsertNode(42);
    EXPECT_FALSE(Node_Two.first);
    EXPECT_EQ(Node.second,Node_Two.second);
}

TEST_F(EmptyTree, DeleteNode){
    auto Node = testingTree.DeleteNode(42);
    EXPECT_FALSE(Node);
    
}

TEST_F(EmptyTree, FindNode){
    auto Node = testingTree.FindNode(42);
    EXPECT_FALSE(Node);

    
}
TEST_F(NonEmptyTree, InsertNode){
    auto Node = testingTree.InsertNode(42);
    EXPECT_TRUE(Node.first);
    EXPECT_EQ(Node.second->key,42);
    auto Node_Two = testingTree.InsertNode(42);
    EXPECT_FALSE(Node_Two.first);
    EXPECT_EQ(Node.second,Node_Two.second);
}

TEST_F(NonEmptyTree, DeleteNode){
    auto Node = testingTree.DeleteNode(42);
    EXPECT_FALSE(Node);
    Node = testingTree.DeleteNode(1);
    EXPECT_TRUE(Node);
    Node = testingTree.DeleteNode(1);
    EXPECT_FALSE(Node);
    testingTree.InsertNode(42);
    Node = testingTree.DeleteNode(42);
    EXPECT_TRUE(Node);
}

TEST_F(NonEmptyTree, FindNode){
    auto Node = testingTree.FindNode(42);
    EXPECT_FALSE(Node);
    Node = testingTree.FindNode(1);
    EXPECT_TRUE(Node);
    
    testingTree.InsertNode(42);
    Node = testingTree.FindNode(42);
    EXPECT_TRUE(Node);
    testingTree.DeleteNode(42);
    Node = testingTree.FindNode(42);
    EXPECT_FALSE(Node);
    
}

TEST_F(TreeAxioms, Axiom1){
    std::vector<Node_t*> nodes {};
    testingTree.GetLeafNodes(nodes);
    for(auto node : nodes){
        EXPECT_EQ(BLACK,node->color);
    }
}
TEST_F(TreeAxioms, Axiom2){
    std::vector<Node_t*> nodes {};
    testingTree.GetAllNodes(nodes);
    for(auto node : nodes){
        if(node->color == RED){
            EXPECT_EQ(BLACK,node->pLeft->color);
            EXPECT_EQ(BLACK,node->pRight->color);
        }
    }
}
TEST_F(TreeAxioms, Axiom3){
    std::vector<Node_t*> leaf_nodes {};
    testingTree.GetLeafNodes(leaf_nodes);
    int blackcount = 0;
    int previouscount = -1;
    Node_t* Node;
    for(auto node : leaf_nodes){
        blackcount = 0;
        Node = node;
        while(Node){
            if(Node->color == BLACK){
                blackcount++;
            }
            Node = Node->pParent;

        }
    if(previouscount != -1){
        EXPECT_EQ(previouscount,blackcount);

    }
    previouscount = blackcount;
    }
    
    
}














/*** Konec souboru black_box_tests.cpp ***/
