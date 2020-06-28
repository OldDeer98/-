#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<cstdio>
#include <fstream>
#define max 26
using namespace std;

typedef struct trienode
{
	string Key; //�ڵ������浥��
	string Translate; //����
	bool Isword;  //�ж��Ƿ�Ϊһ�����ʵĽ�β
	int branch;  //��ʾ��ǰ�ڵ���ڶ��ٷ�֧
	struct trienode* next[max]; //���ӷ�֧
}TrieNode;

class trieNode
{
	public:TrieNode* root= createtrie(); //����ȫ������
	private:bool exist;

	private:
	//��������ģʽ����
	void mode_1(char* word)
	{
		TrieNode* proot = root;
		exist = false; //�жϺ��������������Ƿ��ҵ����ʣ���ʼ��Ϊfalse

		while (*word && proot)
		{
			proot = proot->next[*word - 'a'];
			word++;
		}
		cout << endl << "                             ���ҽ�����£�" << endl;
		if (proot)
		{
			partsearch(proot);
		}
		if (!exist)
		{
			cout << "                             ����ʧ�ܣ�����ƥ�䵥��" << endl;
			return;
		}

		return;
	}

	//ɾ������
	void Del_1(char* word)
	{
		TrieNode* proot = root;
		while (*word && proot)
		{
			proot = proot->next[*word - 'a'];
			proot->branch--;   //����·���Ϸ�֧��
			word++;
		}
		if (proot && proot->Isword)
		{
			proot->Isword = false;   //ȥ�����
			proot->branch--;
			cout << "                             ɾ���ɹ���" << endl;
		}
		else
			cout << "                             ɾ��ʧ�ܣ����ʲ�����" << endl;
		return;
	}

	//�����������ĵݹ�
	void partsearch(trienode* pnew)
	{
		int i;
		if (pnew->Isword) //�жϸýڵ��Ƿ�Ϊĳ���ʵĽ�β
		{
			cout << "                             " << "���ʣ�" << pnew->Key << "   ����Ϊ��" << pnew->Translate << endl;
			exist = true;
		}
		for (i = 0; i < max; i++)  //�ݹ��ѯ
			if (pnew->next[i])
				partsearch(pnew->next[i]);
	}

	public:
	trienode* createtrie() //��ʼ���ڵ�
	{
		trienode* proot;
		proot = new trienode();
		proot->Isword = false;
		proot->branch = 0;
		memset(proot->next, NULL, sizeof(proot->next));//��ʼ����֧
		return proot;
	}
	void Search()
	{
		getchar(); //����ѡ��س�

		int mode = 0;
		char* word, * tmp;
		word = (char*)malloc(sizeof(char) * 30); // ���뵥�ʿռ�
		tmp = word;

		cout << endl;
		cout << "                            ========���ҵ���========" << endl;
		cout << endl;
		cout << "                             1.���ֲ���" << endl;
		cout << "                             2.ȫƴ����" << endl;
		cout << "                             ����ѡ�����ģʽ��";
		while (1)
		{
			cin >> mode;
			if (mode != 1 && mode != 2)
				cout << "                             ����ģʽ�������������룺";
			else
				break;
		}
		cout << "                             ������ҵ��ʣ�";
		word = Input(word); //���뵥��

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
				cout << endl << "                             ���ҳɹ����ô�����Ϊ��" << proot->Translate << endl << endl;
			else if (!(proot && proot->Isword) && mode == 2)
			{
				cout << endl << "                             ����ʧ�ܣ����޴˴� " << endl
					<< "                       ========תΪ���ֲ���ģʽ��======== " << endl
					<< "                               1.��         2.��  " << endl
					<< "                       ����ѡ��";
				while (1)
				{
					cin >> mode;
					if (mode != 1 && mode != 2)
						cout << "                             ����������������룺";
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
		getchar(); //����ѡ��س�

		int i = 0;
		string tran;
		char* a, * tmp;
		a = (char*)malloc(sizeof(char) * 30); // ���뵥�ʿռ�
		tmp = a;

		cout << endl;
		cout << "                            ========��ӵ���========" << endl;
		cout << endl;
		cout << "                             ������ӵ��ʣ�";
		a = Input(a); //���뵥��
		cout << "                             �����Ӧ���룺";
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
				proot->branch++;  //���Ӹýڵ��ϵķֽڵ���
			proot = proot->next[*a - 'a'];
			a++;
		}
		if (proot->Isword)
		{
			cout << "                             ���ʧ�ܣ��õ����Ѵ���" << endl << endl;
		}
		else
		{
			proot->Isword = true;
			proot->Key = (string)tmp;
			proot->Translate = tran;
			cout << "                             ��ӳɹ���" << endl << endl;
		}

		return;
	}
	void Del()
	{
		getchar();  //����ѡ��س�

		char* word, * tmp;
		word = (char*)malloc(sizeof(char) * 30); // ���뵥�ʿռ�
		tmp = word;

		cout << endl;
		cout << "                            ========ɾ������========" << endl;
		cout << endl;
		cout << "                             ����ɾ�����ʣ�";
		word = Input(word); //���뵥��

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
					cout << "                             ������󣡰����Ƿ��ַ��� " << a[i] << endl;
					flag = 0;
				}
				if (a[i] >= 'A' && a[i] <= 'Z')
				{
					a[i] += 32;
				}
			}
			if (!flag)
				cout << "                             ���������룺";
			else
				return a;
		}
	}
};

void menu(trieNode trie);
void inFile(trieNode trie); //��ȡ�ļ�
void outFile(trienode* pnew, ofstream& outfile); //�����ļ�

int main(string arg[])
{
	trieNode trie;
	inFile(trie); //��ȡ�ļ�
	menu(trie);
	trienode* pnew = trie.root;
	ofstream outfile("text.txt", ios::out);
	if (!outfile)
		cout << "                             �ļ�����ʧ��";
	else
		outFile(pnew, outfile);

	outfile.close();
	cout << "                             �������˳���";
	return 0;
}

void menu(trieNode trie)
{
	while (1)
	{
		int i = 0;
		cout << "                             ========���˵�========" << endl;
		cout << "                             " << endl;
		cout << "                              1.��ѯ����" << endl;
		cout << "                              2.��ӵ���" << endl;
		cout << "                              3.ɾ������" << endl;
		cout << "                              4.�˳�����" << endl;
		cout << "                             " << endl;
		cout << "                             ======================" << endl;
		while (1)
		{
			cout << "                             ������ѡ�";
			cin >> i;
			if (i >= 1 && i <= 4)
				break;
			else
				cout << "                             �����������������" << endl;
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
	//�ı�������ΪANSI
	int keyNum = 0;  //��¼�Ѷ�ȡ��������
	ifstream infile("text.txt", ios::in); //ֻ��
	if (!infile)
	{
		cout << "                             �ļ�������" << endl;
		return;
	}
	while (!infile.eof() && infile.peek() != EOF)  //��δ�����ļ���β���������ݲ�Ϊ��ʱ�������뵥��
	{
		TrieNode* proot = trie.root;
		string inKey;
		string tran;
		infile >> inKey;
		infile >> tran;
		infile.get();  //�����س�

		char* a = (char*)malloc(sizeof(char) * inKey.length());  //���������뵥�ʳ�������ռ�
		strcpy(a, inKey.c_str());  //�����ʱ��������飬.c_str()��ʾ����C���Ե��ַ���
		a[inKey.length()] = '\0'; //���һ��Ԫ����Ϊ��

		while (*a)  //���뵥��
		{
			if ((proot->next[*a - 'a']) == NULL)
			{
				TrieNode* pnew = trie.createtrie();
				proot->next[*a - 'a'] = pnew;
				if (proot != trie.root)
					proot->branch++;  //���Ӹýڵ��ϵķֽڵ���
			}
			proot = proot->next[*a - 'a'];
			a++;
		}
		proot->Isword = true;
		proot->Key = inKey;
		proot->Translate = tran;
		keyNum++;

		if (infile.fail())   //��ֹ���ļ���β�Զ��һ��
			break;
	}
	cout << "                             �Ѷ�ȡ����������" << keyNum << endl;
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