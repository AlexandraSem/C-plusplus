#pragma once
#include<iostream>

struct TreeNode
{
	int Data;
	TreeNode* Left = nullptr;
	TreeNode* Right = nullptr;
	TreeNode* Parent = nullptr;
	TreeNode(int value) :
		Data(value)
	{
	}
};

class BinaryTree
{
	TreeNode* m_root = nullptr;

public:
	BinaryTree() = default;

	void Insert(int value)
	{
		if (m_root == nullptr)
		{
			m_root = new TreeNode(value);
		}
		else
		{
			InsertRecursive(m_root, value);
		}
	}
	void InsertRecursive(TreeNode* node, int value)
	{
		if (value == node->Data)
		{
			return;
		}
		if (value < node->Data)
		{
			if (node->Left == nullptr)
			{
				TreeNode* NewNode = new TreeNode(value);
				node->Left = NewNode;
				NewNode->Parent = node;
			}
			else
			{
				InsertRecursive(node->Left, value);
			}

		}
		else
		{
			if (node->Right == nullptr)
			{
				TreeNode* NewNode = new TreeNode(value);
				node->Right = NewNode;
				NewNode->Parent = node;
			}
			else
			{
				InsertRecursive(node->Right, value);
			}
		}
	}
	void Print()
	{
		PrintRecursive(m_root);
	}

	void PrintRecursive(TreeNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		PrintRecursive(node->Left);
		std::cout << node->Data << " ";
		PrintRecursive(node->Right);
	}
	//
	TreeNode* FindRecursive(TreeNode* node, int value)
	{
		if (node != nullptr)
		{

			if (node->Data == value)
			{
				return node;
			}
			if (node->Data > value)
			{
				return FindRecursive(node->Left, value);

			}
			else
			{
				return FindRecursive(node->Right, value);
			}
		}
		else
		{
			return nullptr;
		}
	}

	TreeNode* Find(int value)
	{
		return FindRecursive(m_root, value);
	}	
	void Erase(TreeNode* node)
	{
		TreeNode* forReplace = nullptr;
		TreeNode* newParent = node->Parent;
		if (node->Left != nullptr && node->Right != nullptr)
		{
			TreeNode* forReplace = node->Right;
			while (forReplace->Left != nullptr)
			{
				forReplace = forReplace->Left;
			}
			forReplace->Data = std::move(node->Data);
			node = forReplace;
			forReplace = nullptr;
		}

		if (node->Left != nullptr)
		{
			forReplace = node->Left;
		}
		else if (node->Right != nullptr)
		{
			forReplace = node->Right;
		}
		if (forReplace != nullptr)
		{
			forReplace->Parent = newParent;
		}
		if (newParent)
		{
			if (newParent->Left == node)
			{
				newParent->Left = forReplace;
			}
			else
			{
				newParent->Right = forReplace;
			}
		}
		delete node;
	}
};
//main
#include<iostream>
#include"BinaryTree.h"


int main()
{
	BinaryTree Tree;
	Tree.Insert(8);
	Tree.Insert(5);
	Tree.Insert(3);
	Tree.Insert(10);
	Tree.Insert(12);
	Tree.Insert(0);

	Tree.Print();
	TreeNode* node = Tree.Find(3);
	Tree.Erase(node);
	std::cout << "\n";
	Tree.Print();
	return 0;
}
