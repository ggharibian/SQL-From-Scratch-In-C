#include "BST_Functions_Test_Functions.h"

TreeNode<int>* getBalancedBinaryTree()
{
	int arr[15];

	for (int i = 0; i < 15; i++)
		arr[i] = (i + 1) * 2;

	TreeNode<int>* root = tree_from_sorted_list<int>(arr, 15);

	return root;
}

void testTreePrint()
{
	cout << "============ Testing Tree Print ============" << endl;
	cout << endl << "//Printing Empty Tree: tree_print<int>(root) -> "
		<< "*nothing*" << endl;

	TreeNode<int>* root = nullptr;

	cout << "tree_print<int>(root) ==> " << endl;
	
	tree_print(root);

	cout << endl << "//Printing Balanced Tree:" << endl;
	
	root = getBalancedBinaryTree();

	cout << "tree_print<int>(root) ==> " << endl;

	tree_print(root);


	cout << "\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreePrintPreInPostOrder(){
	cout << "============ Testing Tree Print In / Pre / Post -Fix "
		<< "============" << endl;

	TreeNode<int>* root = getBalancedBinaryTree();

	cout << endl << "//Printing Balanced Tree:" << endl;

	cout << endl << endl << "//Printing Inorder: tree_print(root) -> "
		<< "[2]->[4]->[6]->[8]->[10]->[12]->[14]->[16]->"
		<< "[18]->[20]->[22]->[24]->[26]->[28]->[30]->" << endl << endl;

	cout << "tree_print_inorder(root) ==> " << endl;

	tree_print_inorder(root);

	cout << endl << endl << "//Printing Preorder: tree_print(root) -> "
		<< "[16]->[8]->[4]->[2]->[6]->[12]->[10]->"
		<< "[14]->[24]->[20]->[18]->[22]->[28]->[26]->[30]->" << endl << endl;

	cout << "tree_print_preorder(root) ==> " << endl;

	tree_print_preorder(root);

	cout << endl << endl << "//Printing Postorder: tree_print(root) -> "
		<< "[2]->[6]->[4]->[10]->[14]->[12]->[8]->[18]->"
		<< "[22]->[20]->[26]->[30]->[28]->[24]->[16]->" << endl << endl;

	cout << "tree_print_postorder(root) ==> " << endl;

	tree_print_postorder(root);


	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeInsert()
{
	cout << "============ Testing Tree Insert ============" << endl;
	cout << "//Inserting into empty Tree:" << endl << endl;

	TreeNode<int>* root = nullptr;

	cout << "//Calling tree_insert(root, 5)" << endl << endl;
	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n//Inserting into Balanced Tree:" << endl << endl;

	root = getBalancedBinaryTree();

	cout << "//Calling tree_insert(root, 3)" << endl << endl;
	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);


	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeSearch()
{
	cout << "============ Testing Tree Search ============" << endl;
	cout << "//Searching in empty Tree:" << endl << endl;

	TreeNode<int>* root = nullptr;

	cout << "//Calling tree_search(root, 5) ==> 00000000" << endl << endl;
	
	cout << "tree_search(root, 5) ==> " << tree_search(root, 5) 
		<< endl << endl;

	cout << "\n\n//Searching in Balanced Tree:" << endl << endl;

	root = getBalancedBinaryTree();

	cout << "//Calling tree_search(root, 5) ==> 00000000" << endl << endl;

	cout << "tree_search(root, 5) ==> " << tree_search(root, 5) 
		<< endl << endl;

	cout << "//Calling tree_search(root, 6) ==> |6|" << endl << endl;

	cout << "*tree_search(root, 5) ==> " << *tree_search(root, 6) 
		<< endl << endl;

	cout << "============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeClear()
{
	cout << "============ Testing Tree Clear ============" << endl;
	cout << "//Clearing empty Tree:" << endl << endl;

	TreeNode<int>* root = nullptr;

	cout << "//Calling tree_clear(root)" << endl << endl;

	tree_clear(root);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n//Clearing Balanced Tree:" << endl << endl;

	root = getBalancedBinaryTree();

	cout << "//Calling tree_clear(root)" << endl << endl;

	tree_clear(root);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeErase()
{
	cout << "============ Testing Tree Erase ============" << endl;

	cout << "//Erasing from empty Tree:" << endl << endl;

	TreeNode<int>* root = nullptr;

	cout << "//Calling tree_erase(root, 5)" << endl << endl;

	tree_erase(root, 5);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n//Erasing from Balanced Tree:" << endl << endl;

	root = getBalancedBinaryTree();

	cout << "\n//Calling tree_erase(root, 5)" << endl << endl;

	tree_erase(root, 5);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n//Calling tree_erase(root, 6)" << endl << endl;

	tree_erase(root, 6);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeRemoveMax()
{
	cout << "============ Testing Tree Remove Max ============" << endl;

	cout << "//Removing Max from empty Tree:" << endl << endl;

	int max;
	TreeNode<int>* root = nullptr;

	cout << "//Calling tree_remove_max(root, max)" << endl << endl;

	tree_erase(root, max);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n//Removing Max from Balanced Tree:" << endl << endl;

	root = getBalancedBinaryTree();

	cout << "//Calling tree_remove_max(root, max)" << endl << endl;

	tree_erase(root, max);

	cout << "//Printing Balanced Tree:" << endl << endl;

	tree_print(root);

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);
}

void testTreeCopy()
{
	cout << "============ Testing Tree Copy ============" << endl;
	cout << "//Copying empty Tree:" << endl << endl;

	TreeNode<int>* root1 = nullptr;
	TreeNode<int>* root2 = nullptr;

	cout << "//Calling root2 = tree_copy(root1)" << endl << endl;

	root2 = tree_copy(root1);

	cout << "//Printing Balanced Tree:" << endl << endl;

	cout << "root1 : " << endl;
	tree_print(root1);

	cout << "\nroot2 : " << endl;
	tree_print(root2);

	cout << "\n\n//Copying Balanced Tree:" << endl << endl;

	root1 = getBalancedBinaryTree();

	cout << "//Calling root2 = tree_copy(root1)" << endl << endl;

	root2 = tree_copy(root1);

	cout << "//Printing Balanced Tree:" << endl << endl;

	cout << "root1 : " << endl;
	tree_print(root1);

	cout << "\nroot2 : " << endl;
	tree_print(root2);


	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root1);
	tree_clear(root2);
}

void testTreeAdd()
{
	cout << "============ Testing Tree Add ============" << endl;
	cout << "//Copying empty Tree:" << endl << endl;

	TreeNode<int>* root1 = getBalancedBinaryTree();
	TreeNode<int>* root2 = getBalancedBinaryTree();

	cout << "root1 : " << endl;
	tree_print(root1);

	cout << "\nroot2 : " << endl;
	tree_print(root2);

	cout << "\nroot1 + root2 : ";

	tree_add(root1, root2);

	tree_print(root1);

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root1);
	tree_clear(root2);
}

void testTreeFromSortedList()
{

	cout << "============ Testing Tree From Sorted List ============" << endl;
	cout << "//Making Balanced BST:" << endl << endl;

	TreeNode<int>* root;

	int arr[15];

	for (int i = 0; i < 15; i++)
		arr[i] = (i + 1) * 2;

	root = tree_from_sorted_list<int>(arr, 15);

	cout << "root: " << endl;
	tree_print(root);

	cout << "\n\n============ END TEST ========================" << endl
		<< endl;

	tree_clear(root);

}
