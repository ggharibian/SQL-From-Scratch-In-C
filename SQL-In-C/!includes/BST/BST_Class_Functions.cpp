#include "BST_Class_Functions.h"

BST<int> getBalancedBST()
{
	int arr[15];

	for (int i = 0; i < 15; i++)
		arr[i] = (i + 1) * 2;

	return BST<int>(arr, 15);
}

void testBSTCopyConstructor()
{
	cout << "============ Testing Copy Constructor ============" << endl;
	cout << endl << "Copying Filled Stack:" << endl;
	cout << "//Calling 'copy = s'; copy ==> H->[10]->[20]-> ... ->[100]->|||"
		<< endl << endl;

	BST<int> b = getBalancedBST();

	BST<int> copy(b);

	b.erase(30);
	cout << "Popping 30 out of b." << endl << endl;

	cout << "Printing b: " << b << endl;
	cout << "Printing copy: " << copy;

	cout << endl << endl << "Copying Empty Stack:" << endl;
	cout << "//Calling 'otherCopy(s)'; otherCopy ==> H->|||" << endl << endl;

	b.~BST();

	BST<int> otherCopy(b);

	cout << "Printing b: " << b << endl;
	cout << "Printing otherCopy: " << otherCopy << endl;

	cout << "\n============ END TEST ========================" << endl
		<< endl;
}

void testBSTAssignementOperator()
{
	cout << "============ Testing '=' operator ============" << endl;
	cout << endl << "Copying Filled Stack:" << endl;
	cout << "//Calling 'copy = s'; copy ==> H->[10]->[20]-> ... ->[100]->|||"
		<< endl << endl;

	BST<int> b = getBalancedBST();

	BST<int> copy = b;

	b.erase(30);

	cout << "Popping 30 out of s." << endl << endl;

	cout << "Printing b: " << b << endl;
	cout << "Printing copy: " << copy;

	cout << endl << endl << "Copying Empty Stack:" << endl;
	cout << "//Calling 'copy = s'; copy ==> H->|||" << endl << endl;

	b.~BST();

	copy = b;

	cout << "Printing b: " << b << endl;
	cout << "Printing copy: " << copy;

	cout << "\n============ END TEST ========================" << endl
		<< endl;
}

void testBSTDeallocate()
{
	cout << "============ Testing Deallocation ============" << endl
		<< endl;
	cout << "//Calling b.~BST(); H->[10]->[20]->... ==> H->|||"
		<< endl << endl;

	BST<int> b = getBalancedBST();

	cout << b << endl << endl;

	b.~BST();

	cout << b << endl;

	cout << "\n============ END TEST ========================" << endl
		<< endl;
}

void testBSTInsert()
{
	cout << "============ Testing BST Insert ============" << endl;
	cout << "//Inserting into empty Tree:" << endl << endl;

	BST<int> b;

	cout << "//Calling b.insert(5)" << endl << endl;

	b.insert(5);

	cout << "//Printing Tree:" << endl << endl;

	cout << b;

	cout << "\n\n//Inserting into Balanced Tree:" << endl << endl;

	b = getBalancedBST();

	cout << "//Calling b.insert(3)" << endl << endl;

	b.insert(3);

	cout << "//Printing Balanced Tree:" << endl << endl;

	cout << b;


	cout << "\n\n============ END TEST ========================" << endl
		<< endl;
}

void testBSTErase()
{

}

void testBSTClear()
{
}

void testBSTSearch()
{
	cout << "============ Testing BST Search ============" << endl;
	cout << "//Searching in empty Tree:" << endl << endl;

	BST<int> b;
	TreeNode<int>* loc;

	cout << "//Calling tree_search(root, 5) ==> 00000000" << endl << endl;

	b.search(5, loc);

	cout << "tree_search(root, 5) ==> " << loc
		<< endl << endl;

	cout << "\n\n//Searching in Balanced Tree:" << endl << endl;

	b = getBalancedBST();

	cout << "//Calling tree_search(root, 5) ==> 00000000" << endl << endl;

	b.search(5, loc);

	cout << "tree_search(root, 5) ==> " << loc
		<< endl << endl;

	cout << "//Calling tree_search(root, 6) ==> |6|" << endl << endl;

	b.search(6, loc);

	cout << "*tree_search(root, 5) ==> " << *loc
		<< endl << endl;

	cout << "============ END TEST ========================" << endl
		<< endl;
}

void testBSTOutputOperator()
{
	cout << "============ Testing BST Output ============" << endl;
	cout << endl << "//Printing Empty Tree: tree_print<int>(root) -> "
		<< "*nothing*" << endl;

	BST<int> b;

	cout << "cout << b ==> " << endl;

	cout << b;

	cout << endl << "//Printing Balanced Tree:" << endl;

	b = getBalancedBST();

	cout << "tree_print<int>(root) ==> " << endl;

	cout << b;


	cout << "\n============ END TEST ========================" << endl
		<< endl;
}

void testBSTSummationOperator()
{
	cout << "============ Testing Tree Add ============" << endl;
	cout << "//Copying empty Tree:" << endl << endl;

	BST<int> b1 = getBalancedBST();
	BST<int> b2 = getBalancedBST();

	cout << "root1 : " << endl;
	cout << b1;

	cout << "\nroot2 : " << endl;
	cout << b2;

	cout << "\nroot1 + root2 : ";

	b1 += b2;;

	cout << b1;

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;
}
