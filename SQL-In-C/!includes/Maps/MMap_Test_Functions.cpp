#include "MMap_Test_Functions.h"

MMap<int, int> getMMap()
{
    srand(time(NULL));

    MMap<int, int> mmap;

    for (int i = 0; i < 100; i++) {
        mmap[i % 10 * 3] += rand() % 1000 + 1;
    }

    return mmap;
}

void testMMapClearFunction()
{
    cout << "========== Testing Clear ==========" << endl << endl;

    MMap<int, int> m;

    cout << "Calling Clear on empty tree;" << endl;
    cout << "m.clear();" << endl;
    m.clear();
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling clear on tree;" << endl;
    cout << "m.clear();" << endl;
    m.clear();
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "========== END ==========" << endl;
}

void testMMapContains()
{
    cout << "========== Testing Count ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling contains on empty tree;" << endl;
    cout << "m.contains(5) ====> " << m.contains(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling contains on tree (item is missing);" << endl;
    cout << "m.contains(5) ====> " << m.contains(5) << endl << endl;

    cout << "Calling contains on tree (item is there);" << endl;
    cout << "m.contains(6) ====> " << m.contains(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMMapGet()
{
    cout << "========== Testing Count ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling get on empty tree;" << endl;
    cout << "m.get(5) ====> " << m.get(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling get on tree (item is missing);" << endl;
    cout << "m.get(5) ====> " << m.get(5) << endl << endl;

    cout << "Calling get on tree (item is there);" << endl;
    cout << "m.get(6) ====> " << m.get(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMMapFind()
{
    cout << "========== Testing Find ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling find on empty tree;" << endl;
    cout << "m.find(5) ====> " << m.find(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling find on tree (item is missing);" << endl;
    cout << "m.find(5) ====> " << m.find(5) << endl << endl;

    cout << "Calling find on tree (item is there);" << endl;
    cout << "m.find(6) ====> " << m.find(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMMapInsert()
{
    cout << "========== Testing Erase ==========" << endl << endl;
    srand(time(NULL));

    MMap<int, int> m;

    int num;

    for (int i = 0; i < 100; i++) {

        cout << "Inserting value #" << i + 1 << endl;

        m.insert(rand() % 10, rand() % 10000);

        cout << "m:" << endl << endl;

        cout << m << endl;

    }

    cout << "========== END ==========" << endl;
}

void testMMapErase()
{
    cout << "========== Testing Erase ==========" << endl << endl;

    MMap<int, int> m;

    cout << "Calling erase on empty tree;" << endl;
    cout << "m.erase(5);" << endl;
    m.erase(5);
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling erase on tree(item is not there);" << endl;
    cout << "m.erase(5);" << endl;
    m.erase(5);
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "Calling erase on empty tree;" << endl;
    cout << "m.erase(12);" << endl;
    m.erase(12);
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "========== END ==========" << endl;
}

void testMMapCount()
{
    cout << "========== Testing Count ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling count on empty tree;" << endl;
    cout << "m.count(5) ====> " << m.count(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling count on tree (item is missing);" << endl;
    cout << "m.count(5) ====> " << m.count(5) << endl << endl;

    cout << "Calling count on tree (item is there);" << endl;
    cout << "m.count(6) ====> " << m.count(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMMapIsValid()
{
    cout << "========== Testing isValid ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling isValid on empty tree;" << endl;
    cout << "m.is_valid() ====> " << m.is_valid() << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling isValid on tree;" << endl;
    cout << "m.is_valid() ====> " << m.is_valid() << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMMapOutput()
{
    cout << "========== Testing Output ==========" << endl << endl;

    MMap<int, int> m;
    cout << "Calling '<<' on empty tree;" << endl;
    cout << "cout << m:" << endl;

    cout << m << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMMap();

    cout << "Calling '<<' on tree;" << endl;
    cout << "cout << m:" << endl;

    cout << m << endl << endl;

    cout << "========== END ==========" << endl;
}
