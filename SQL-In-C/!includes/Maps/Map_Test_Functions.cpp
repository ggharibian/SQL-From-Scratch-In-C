#include "Map_Test_Functions.h"

Map<int, int> getMap()
{
    srand(time(NULL));

    Map<int, int> map;

    for (int i = 0; i < 20; i++) {
        map[i * 3] += rand() % 1000 + 1;
    }

    return map;
}

void testMapClearFunction()
{
    cout << "========== Testing Clear ==========" << endl << endl;

    Map<int, int> m;

    cout << "Calling Clear on empty tree;" << endl;
    cout << "m.clear();" << endl;
    m.clear();
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling clear on tree;" << endl;
    cout << "m.clear();" << endl;
    m.clear();
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "========== END ==========" << endl;
}

void testMapContains()
{
    cout << "========== Testing Contains ==========" << endl << endl;

    Map<int, int> m;
    cout << "Calling contains on empty tree;" << endl;
    cout << "m.contains(5) ====> " << m.contains(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling contains on tree (item is missing);" << endl;
    cout << "m.contains(5) ====> " << m.contains(5) << endl << endl;

    cout << "Calling contains on tree (item is there);" << endl;
    cout << "m.contains(6) ====> " << m.contains(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMapGet()
{
    cout << "========== Testing Count ==========" << endl << endl;

    Map<int, int> m;
    cout << "Calling get on empty tree;" << endl;
    cout << "m.get(5) ====> " << m.get(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling get on tree (item is missing);" << endl;
    cout << "m.get(5) ====> " << m.get(5) << endl << endl;

    cout << "Calling get on tree (item is there);" << endl;
    cout << "m.get(6) ====> " << m.get(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMapFind()
{
    cout << "========== Testing Find ==========" << endl << endl;

    Map<int, int> m;
    cout << "Calling find on empty tree;" << endl;
    cout << "m.find(5) ====> " << m.find(5) << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling find on tree (item is missing);" << endl;
    cout << "m.find(5) ====> " << m.find(5) << endl << endl;

    cout << "Calling find on tree (item is there);" << endl;
    cout << "m.find(6) ====> " << m.find(6) << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMapInsert()
{
    cout << "========== Testing Erase ==========" << endl << endl;
    srand(time(NULL));

    Map<int, int> m;

    int num;

    for (int i = 0; i < 100; i++) {

        cout << "Inserting value #" << i + 1 << endl;

        m.insert(rand() % 10, rand() % 10000);

        cout << "m:" << endl << endl;

        cout << m << endl;

    }

    cout << "========== END ==========" << endl;
}

void testMapErase()
{
    cout << "========== Testing Erase ==========" << endl << endl;

    Map<int, int> m;

    cout << "Calling erase on empty tree;" << endl;
    cout << "m.erase(5);" << endl;
    m.erase(5);
    cout << "outputting 'm':" << endl << endl;

    cout << endl << m << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

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

void testMapIsValid()
{
    cout << "========== Testing isValid ==========" << endl << endl;

    Map<int, int> m;
    cout << "Calling isValid on empty tree;" << endl;
    cout << "m.is_valid() ====> " << m.is_valid() << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling isValid on tree;" << endl;
    cout << "m.is_valid() ====> " << m.is_valid() << endl << endl;

    cout << "========== END ==========" << endl;
}

void testMapOutput()
{
    cout << "========== Testing Output ==========" << endl << endl;

    Map<int, int> m;
    cout << "Calling '<<' on empty tree;" << endl;
    cout << "cout << m:" << endl;

    cout << m << endl << endl;

    cout << "Initializing 'm'" << endl << endl;

    m = getMap();

    cout << "Calling '<<' on tree;" << endl;
    cout << "cout << m:" << endl;

    cout << m << endl << endl;

    cout << "========== END ==========" << endl;
}
