#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cstdio>
#include <fstream>
#define max 26
using namespace std;

typedef struct trienode
{
	string Key; //节点上所存单词
	string Translate; //翻译
	bool Isword;  //判断是否为一个单词的结尾
	int branch;  //表示当前节点存在多少分支
	struct trienode* next[max]; //连接分支
}TrieNode;

class trieNode
{
	public:TrieNode* root= createtrie(); //创建全局树根
	private:bool exist;

	private:
	//部分搜索模式函数
	void mode_1(char* word)
	{
		TrieNode* proot = root;
		exist = false; //判断核心搜索代码中是否找到单词，初始化为false

		while (*word && proot)
		{
			proot = proot->next[*word - 'a'];
			word++;
		}
		cout << endl << "                             查找结果如下：" << endl;
		if (proot)
		{
			partsearch(proot);
		}
		if (!exist)
		{
			cout << "                             查找失败！无相匹配单词" << endl;
			return;
		}

		return;
	}

	//删除功能
	void Del_1(char* word)
	{
		TrieNode* proot = root;
		while (*word && proot)
		{
			proot = proot->next[*word - 'a'];
			proot->branch--;   //减少路径上分支数
			word++;
		}
		if (proot && proot->Isword)
		{
			proot->Isword = false;   //去除标记
			proot->branch--;
			cout << "                             删除成功！" << endl;
		}
		else
			cout << "                             删除失败！单词不存在" << endl;
		return;
	}

	//部分搜索核心递归
	void partsearch(trienode* pnew)
	{
		int i;
		if (pnew->Isword) //判断该节点是否为某单词的结尾
		{
			cout << "                             " << "单词：" << pnew->Key << "   词意为：" << pnew->Translate << endl;
			exist = true;
		}
		for (i = 0; i < max; i++)  //递归查询
			if (pnew->next[i])
				partsearch(pnew->next[i]);
	}

	public:
	trienode* createtrie() //初始化节点
	{
		trienode* proot;
		proot = new trienode();
		proot->Isword = false;
		proot->branch = 0;
		memset(proot->next, NULL, sizeof(proot->next));//初始化分支
		return proot;
	}
	void Search()
	{
		getchar(); //读掉选项回车

		int mode = 0;
		char* word, * tmp;
		word = (char*)malloc(sizeof(char) * 30); // 申请单词空间
		tmp = word;

		cout << endl;
		cout << "                            ========查找单词========" << endl;
		cout << endl;
		cout << "                             1.部分查找" << endl;
		cout << "                             2.全拼查找" << endl;
		cout << "                             输入选择查找模式：";
		while (1)
		{
			cin >> mode;
			if (mode != 1 && mode != 2)
				cout << "                             输入模式错误！请重新输入：";
			else
				break;
		}
		cout << "                             输入查找单词：";
		word = Input(word); //输入单词

		if (mode == 1)
		{
			mode_1(word);
		}
		else
		{
			TrieNode* proot = root;
			while (*tmp && proot)
			{
				proot = proot->next[*tmp - 'a'];
				tmp++;
			}
			if (proot && proot->Isword)
				cout << endl << "                             查找成功！该词释义为：" << proot->Translate << endl << endl;
			else if (!(proot && proot->Isword) && mode == 2)
			{
				cout << endl << "                             查找失败！查无此词 " << endl
					<< "                       ========转为部分查找模式？======== " << endl
					<< "                               1.是         2.否  " << endl
					<< "                       输入选择：";
				while (1)
				{
					cin >> mode;
					if (mode != 1 && mode != 2)
						cout << "                             输入错误！请重新输入：";
					else
						break;
				}
				switch (mode)
				{
				case 1:mode_1(word); break;
				case 2:break;
				default:break;
				}
			}
		}

		return;
	}
	void Insert()
	{
		getchar(); //读掉选项回车

		int i = 0;
		string tran;
		char* a, * tmp;
		a = (char*)malloc(sizeof(char) * 30); // 申请单词空间
		tmp = a;

		cout << endl;
		cout << "                            ========添加单词========" << endl;
		cout << endl;
		cout << "                             输入添加单词：";
		a = Input(a); //输入单词
		cout << "                             输入对应翻译：";
		cin >> tran;

		TrieNode* proot = root;
		while (*a)
		{
			if ((proot->next[*a - 'a']) == NULL)
			{
				TrieNode* pnew = createtrie();
				proot->next[*a - 'a'] = pnew;
			}
			if (proot != root)
				proot->branch++;  //增加该节点上的分节点数
			proot = proot->next[*a - 'a'];
			a++;
		}
		if (proot->Isword)
		{
			cout << "                             添加失败！该单词已存在" << endl << endl;
		}
		else
		{
			proot->Isword = true;
			proot->Key = (string)tmp;
			proot->Translate = tran;
			cout << "                             添加成功！" << endl << endl;
		}

		return;
	}
	void Del()
	{
		getchar();  //读掉选项回车

		char* word, * tmp;
		word = (char*)malloc(sizeof(char) * 30); // 申请单词空间
		tmp = word;

		cout << endl;
		cout << "                            ========删除单词========" << endl;
		cout << endl;
		cout << "                             输入删除单词：";
		word = Input(word); //输入单词

		Del_1(word); 

		return;
	}

	char* Input(char* a)
	{
		while (1)
		{
			int flag = 1, i;
			cin >> a;
			for (i = 0; a[i]; i++)
			{
				if (a[i] == '\n')
					break;
				else if (!((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z')))
				{
					cout << "                             输入错误！包含非法字符： " << a[i] << endl;
					flag = 0;
				}
				if (a[i] >= 'A' && a[i] <= 'Z')
				{
					a[i] += 32;
				}
			}
			if (!flag)
				cout << "                             请重新输入：";
			else
				return a;
		}
	}
};

void menu(trieNode trie);
void inFile(trieNode trie); //读取文件
void outFile(trienode* pnew, ofstream& outfile); //保存文件

int main(string arg[])
{
	trieNode trie;
	inFile(trie); //读取文件
	menu(trie);
	trienode* pnew = trie.root;
	ofstream outfile("text.txt", ios::out);
	if (!outfile)
		cout << "                             文件保存失败";
	else
		outFile(pnew, outfile);

	outfile.close();
	cout << "                             程序已退出。";
	return 0;
}

void menu(trieNode trie)
{
	while (1)
	{
		int i = 0;
		cout << "                             ========主菜单========" << endl;
		cout << "                             " << endl;
		cout << "                              1.查询单词" << endl;
		cout << "                              2.添加单词" << endl;
		cout << "                              3.删除单词" << endl;
		cout << "                              4.退出程序" << endl;
		cout << "                             " << endl;
		cout << "                             ======================" << endl;
		while (1)
		{
			cout << "                             请输入选项：";
			cin >> i;
			if (i >= 1 && i <= 4)
				break;
			else
				cout << "                             输入错误！请重新输入" << endl;
		}

		switch (i)
		{
		case 1:trie.Search(); break;
		case 2:trie.Insert(); break;
		case 3:trie.Del(); break;
		case 4:cout << endl; return;
		default:break;
		}
	}
	return;
}

void inFile(trieNode trie)
{
	//文本编码需为ANSI
	int keyNum = 0;  //记录已读取单词数量
	ifstream infile("text.txt", ios::in); //只读
	if (!infile)
	{
		cout << "                             文件不存在" << endl;
		return;
	}
	while (!infile.eof() && infile.peek() != EOF)  //当未读到文件结尾且所读内容不为空时继续读入单词
	{
		TrieNode* proot = trie.root;
		string inKey;
		string tran;
		infile >> inKey;
		infile >> tran;
		infile.get();  //读掉回车

		char* a = (char*)malloc(sizeof(char) * inKey.length());  //申请所读入单词长度数组空间
		strcpy(a, inKey.c_str());  //将单词保存至数组，.c_str()表示返回C语言的字符串
		a[inKey.length()] = '\0'; //最后一个元素设为空

		while (*a)  //插入单词
		{
			if ((proot->next[*a - 'a']) == NULL)
			{
				TrieNode* pnew = trie.createtrie();
				proot->next[*a - 'a'] = pnew;
				if (proot != trie.root)
					proot->branch++;  //增加该节点上的分节点数
			}
			proot = proot->next[*a - 'a'];
			a++;
		}
		proot->Isword = true;
		proot->Key = inKey;
		proot->Translate = tran;
		keyNum++;

		if (infile.fail())   //防止到文件结尾仍多读一次
			break;
	}
	cout << "                             已读取单词数量：" << keyNum << endl;
	infile.close();
	return;
}

void outFile(trienode* pnew, ofstream& outfile)
{
	int i;
	if (pnew->Isword)
	{
		outfile << pnew->Key << " " << pnew->Translate << endl;
	}
	for (i = 0; i < max; i++)
		if (pnew->next[i])
			outFile(pnew->next[i], outfile);
	return;
}