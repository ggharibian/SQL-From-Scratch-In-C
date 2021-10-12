#include "BPlusTree_Test_Functions.h"

BPlusTree<int> getBPlusTree()
{
    srand(time(NULL));

    BPlusTree<int> b;

    for (int i = 0; i < 100; i++) {
        b.insert(rand() % 1000 + 1);
    }

    return b;
}

void testBPlusTreeClearFunction()
{
    cout << "========== Testing Clear ==========" << endl << endl;

    BPlusTree<int> b;

    cout << "Calling Clear on empty tree;" << endl;
    cout << "b.clear_tree();" << endl;
    b.clear_tree();
    cout << "outputting 'b':" << endl << endl;

    cout << endl << b << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling clear_tree on tree;" << endl;
    cout << "b.clear_tree();" << endl;
    b.clear_tree();
    cout << "outputting 'b':" << endl << endl;

    cout << endl << b << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeContains()
{
    cout << "========== Testing Contains ==========" << endl << endl;

    BPlusTree<int> b;
    cout << "Calling contains on empty tree;" << endl;
    cout << "b.contains(5) ====> " << b.contains(5) << endl << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling contains on tree (item is missing);" << endl;
    cout << "b.contains(5) ====> " << b.contains(5) << endl << endl;

    cout << "Calling contains on tree (item is there);" << endl;
    cout << "b.contains(6) ====> " << b.contains(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeGet()
{
    cout << "========== Testing Get ==========" << endl << endl;

    BPlusTree<int> b;
    cout << "Calling get on empty tree;" << endl;
    cout << "b.get(5) ====> " << b.get(5) << endl << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling get on tree (item is missing);" << endl;
    cout << "b.get(5) ====> " << b.get(5) << endl << endl;

    cout << "Calling get on tree (item is there);" << endl;
    cout << "b.get(6) ====> " << b.get(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeFind()
{
    cout << "========== Testing Find ==========" << endl << endl;

    BPlusTree<int> b;
    cout << "Calling find on empty tree;" << endl;
    cout << "b.find(5) ====> " << b.find(5) << endl << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling find on tree (item is missing);" << endl;
    cout << "b.find(5) ====> " << b.find(5) << endl << endl;

    b.insert(6);

    cout << "Calling find on tree (item is there);" << endl;
    cout << "b.find(6) ====> " << b.find(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeInsert()
{
    cout << "========== Testing Insert ==========" << endl << endl;
    srand(time(NULL));

    BPlusTree<int> b;

    for (int i = 0; i < 20; i++) {

        cout << "Inserting value #" << i + 1 << endl;

        b.insert(rand() % 10000);

        cout << "b:" << endl << endl;

        cout << b << endl;

    }

    cout << "========== END ==========" << endl;
}

void testBPlusTreeErase()
{
    cout << "========== Testing Erase ==========" << endl << endl;

    BPlusTree<int> b;

    cout << "Calling remove on empty tree;" << endl;
    cout << "b.remove(5);" << endl;
    b.remove(5);
    cout << "outputting 'b':" << endl << endl;

    cout << endl << b << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling remove on tree(item is not there);" << endl;
    cout << "b.remove(5);" << endl;
    b.remove(5);
    cout << "outputting 'b':" << endl << endl;

    cout << endl << b << endl;

    cout << "Calling remove on empty tree;" << endl;
    cout << "b.remove(12);" << endl;
    b.remove(12);
    cout << "outputting 'b':" << endl << endl;

    cout << endl << b << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeIsValid()
{
    cout << "========== Testing isValid ==========" << endl << endl;

    BPlusTree<int> b;
    cout << "Calling isValid on empty tree;" << endl;
    cout << "b.is_valid() ====> " << b.is_valid() << endl << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling isValid on tree;" << endl;
    cout << "b.is_valid() ====> " << b.is_valid() << endl << endl;

    cout << "========== END ==========" << endl;
}

void testBPlusTreeOutput()
{
    cout << "========== Testing Output ==========" << endl << endl;

    BPlusTree<int> b;
    cout << "Calling '<<' on empty tree;" << endl;
    cout << "cout << b:" << endl;

    cout << b << endl << endl;

    cout << "Initializing 'b'" << endl << endl;

    b = getBPlusTree();

    cout << "Calling '<<' on tree;" << endl;
    cout << "cout << b:" << endl;

    cout << b << endl << endl;

    cout << "========== END ==========" << endl;
}

