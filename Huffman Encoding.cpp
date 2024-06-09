#include<windows.h>
#include<iostream>
#include<stdint.h>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<string>
#include<bitset>
#include<cmath>
using namespace std;


void HuffmanCodes(char [],string,int, char [], int[]);


class compNode
{
	public:
		
		char c;
		int freq;
		int code[16]; 
		int len;
		compNode *cn;
		
		compNode()
		{ cn = NULL; }
		
		compNode(char ch, int num, int c_arr[], int top)
		{
			c = ch;
			freq = num;
			
			for(int i=0;i<top;i++)
			{ code[i] = c_arr[i]; }
			
			len = top;
			cn = NULL;	
		}	
		
};


class fileLL
{
	public:
		
		compNode *head;
		
		fileLL()
		{ head = NULL; }
		
		void insert(compNode *cN)
		{	
			if(head==NULL)
			{ head = cN; }
			
			else
			{
				compNode *ptr = head;
				
				while(ptr->cn != NULL)
				{ ptr = ptr->cn; }
				
				ptr->cn = cN;
			}
		}
};


class Node
{
	public:
	    char c;
	    int freq;
	    Node* right; 
		Node* left;
	
	    Node()
		{  }
	
	    Node(char ch,int f)
		{
	        c = ch;
	        freq = f;
	        right = NULL;
	        left = NULL;
	    }

};


class DLL
{	
	public:
		
		int size;
		Node *head,*tail;
		
		DLL()
		{
			size = 0;
			head = NULL;
			tail = NULL;
		}
		
		void append(char ch)
		{
			
			Node *n = new Node(ch,1);
			
			if(head==NULL)
			{	
				head = n;
				tail = n;	
			}
			
			else
			{	
				tail->right = n;
				n->left = tail;
				tail = n;
			}
			
			size++;
		}
		
		
		void updatefreq(char ch)
		{			
			Node *rtraverse=head, *ltraverse=tail;
			
			while(rtraverse!=NULL && ltraverse!=NULL)
			{		
				if(rtraverse->c == ch)
				{
					rtraverse->freq += 1;
					return;
				}
				
				else if(ltraverse->c == ch)
				{
					ltraverse->freq += 1;
					return;
				}
				
				rtraverse = rtraverse->right;
				ltraverse = ltraverse->left;
			}
			
			append(ch);	
		}
		
		void emptyLL(char ch[],int freq[])
		{
			Node *temp, *p=head; 
			int i=0;
			
			while(p!=NULL)
			{
				
				ch[i] = p->c;
				
				if(p->c == ' ')
				{ ch[i] = '_'; }
				
				else if(p->c == '\n' )
				{ ch[i] = '#'; }
				
				freq[i] = p->freq;
				i++;
				temp = p;
				p = p->right;
				delete temp;
			}		
				size = 0;
		}
};


class minHeap
{
	public:
	    int size;
	    int capacity;
	    Node **arr; 
	
	    minHeap()
		{  }
	
	    minHeap(int c)
		{
	        capacity = c;
	        size = 0;
	        arr = new Node*[c];
	      
    	}
};


Node* newNode(char ch, int f)
{
	Node *temp = new Node;
	temp->left = NULL;
	temp->right = NULL;
	temp->c = ch;
	temp->freq = f;
	return temp;
}


void swapNode(Node **x, Node **y)
{
    Node* temp = *x;
    *x = *y;
    *y = temp;
}


void minHeapify(minHeap *MH, int index)
{
    int lowest = index;
    int left = (2*index) + 1;
    int right = (2*index) + 2;

    if(left<(MH->size) && MH->arr[left]->freq < MH->arr[lowest]->freq)
	{ lowest = left; }

    if(right<(MH->size) && MH->arr[right]->freq < MH->arr[lowest]->freq)
	{ lowest = right; }

    if(lowest!=index)
	{	
        swapNode(&MH->arr[lowest],&MH->arr[index]);
		minHeapify(MH,lowest);
    }
}


bool isSizeOne(minHeap *MH)
{
    if(MH->size == 1) 
	{ return true; }
	
    return false;
}


Node* getMin(minHeap *MH)
{
    Node *temp = MH->arr[0];
    MH->arr[0] = MH->arr[MH->size-1];
    (MH->size) -= 1;
    minHeapify(MH,0);
    return temp;
}


void insert(minHeap *MH, Node* mhNode)
{

    (MH->size)++;
    int i = (MH->size) - 1;
 
    while (i && mhNode->freq < MH->arr[(i - 1) / 2]->freq) 
	{ 
        MH->arr[i] = MH->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    MH->arr[i] = mhNode;
}


void buildHeap(minHeap *MH)
{
    int n = MH->size - 1;
    int i;
    
    for (int i = (n - 1)/2; i >= 0; i--)
    { minHeapify(MH, i); }
}


bool isLeaf(Node* root)
{
    if(root->left==NULL && root->right==NULL) 
	{ return true; }

    return false;
}


minHeap* createAndHeapify(char ch[], int f[], int size)
{
    
	minHeap *MH = new minHeap(size);

    for(int i=0;i<size;i++)
	{  	
        MH->arr[i] = newNode(ch[i],f[i]);
		(MH->size)++;
	}

    buildHeap(MH);
    return MH;
}


Node* HuffmanTree(char c[], int f[], int size)
{
    Node *top, *left, *right;
    minHeap *MH = createAndHeapify(c,f,size);
	
    while (!isSizeOne(MH))
    {	
        left = getMin(MH);
        right = getMin(MH);

        top = newNode('$',left->freq + right->freq);
        top->left = left;
        top->right = right;
		
        insert(MH,top);
    }

    return getMin(MH);
}


int i = 0;


void printCodes(Node* root, string s, int top, char data[], string id[])
{
    if (root->left != NULL) 
	{ printCodes(root->left, s+'0', top + 1, data, id); }
	
    if (root->right != NULL)
	{ printCodes(root->right, s+'1', top + 1, data, id); }
 
    if (isLeaf(root)) 
	{ 
		data[i] = root->c;    
		id[i] = s;
		i++;
		cout<< root->c <<" : ";
		cout<<s<<endl;
    }
}


void printFile(Node* root, int top, int code[], fileLL *fll)
{
 		
    if (root->left != NULL) 
	{  	
    	code[top] = 0;
        printFile(root->left,top + 1,code,fll);
    }
    if (root->right != NULL)
	{
    	code[top] = 1;
        printFile(root->right,top + 1,code,fll);
    }
 
    if (isLeaf(root)) 
	{
		compNode *temp = new compNode(root->c,root->freq,code,top);
		fll->insert(temp);
	}
}


void HuffmanCodes(char c[], int f[], int size, char data[], string id[])
{
	ofstream fp1("compfile2.txt");
	
	for(int i=0;i<size;i++)
	{ fp1<<c[i]<<f[i]<<char(167); }
	
	Node* root = HuffmanTree(c, f, size);

    string s="";
	char n;
	int i=0, h=0;
	unsigned char val = 0;
	
	int top = 0, arr[100];
	fileLL *fll = new fileLL();

	ifstream fp("file.txt");
	
    printCodes(root, s, top, data,id);

	fp1<<'\n';

	printFile(root,top,arr,fll);
	
	while(fp.get(n))
	{
		compNode *ptr = fll->head;
		
		if(n==' ')
		{ n='_'; }
		
		else if(n=='\n')
		{ n = '#'; }
		
		while(ptr != NULL && ptr->c != n)
		{ ptr = ptr->cn; }
			
		if(ptr->c == n)
		{
			for(i=0;i<ptr->len;i++)
			{				
				if(h<7)
				{
					if(ptr->code[i] == 1)
					{	
						val++;
						val = val<<1;
						h++;
					}
					
					else
					{
						val = val<<1;
						h++;
					}
				
				}
				
				else if(h==7)
				{
					if(ptr->code[i]==1)
					{
						val++;
						h=0;
					}
					
					else
					{ h=0; }
					
					fp1.put(val);
					val = 0;
				}
			}
		}
		
	}
	
	for (i = 0; i < 7 - h; i++) 
	{ val = val << 1; }
    
    fp1.put(val);
	
	fp.close();
	fp1.close();
}


int calcindex(char c, char data[])
{
	int i = 0;
	
	while(1)
	{
		if(data[i]==c)
		{ return i; }	
		
		i++;
	}
}


int checkbit(char ch)
{    
    if(ch=='1') 
	{ return 1; }
	
    return 0;
}


void WriteFile(char  letter)
{
	ofstream DecryptFile;
	
	DecryptFile.open("newfile.txt",ios::app);
	char space=' ';
	
	if(DecryptFile.fail())
	{ exit(1); }
	
	else
	{
		if(letter=='_')
		{	
			cout<<space;
			DecryptFile.put(space);
		}
		
		else if(letter=='#')
		{	
			cout<<endl;
			DecryptFile << endl;
		}
		
		else
		{
			cout<<letter;
			DecryptFile<<letter;
		}
	}
	
	DecryptFile.close();
	
}


void DecryptFile()
{
	fflush(stdin);
    ifstream EncryptFile;
    string bin;
    char letter;
    int count=0;
    
	EncryptFile.open("compfile2.txt", ios::in);
	
	if(EncryptFile.fail())
	{ exit(1); } 
	
	string line;
	
	getline(EncryptFile,line);
	
	int len= line.length();
	int s=0;
	char section = 167;

	for(int f=0;f<len-1;f++)
	{
		if(line[f]==section)
		s++;
	}
	
	int fre[s];
	char data[s];
	int i=0,x=0;
	

	while (s>=x)
	{
		if(count==0)
		{
			data[i]=line[count];
			i++;
			count++;
		}
		
		else if(line[count]==section)
		{
			count++;
			data[i]=line[count];
			i++; 
			count++;
		}
		
		else
		{
			int val[10];
			int ind=0;
			while(line[count]!=section)
			{
				val[ind]=(int)line[count]-48;
				ind++;
				count++;
			}
			
			int ten=pow(10,ind-1);
			fre[x]=0;
			
			for(int v=0;v<ind;v++)
			{
				val[v]*=ten;
				fre[x]+=val[v];
				ten/=10;
			}
			//cout << endl << fre[x] << endl;
			x++;
		}
	}
	
	int arr[100];
	Node* root = HuffmanTree(data, fre, s+1);
	
	int size=(root->freq)-1;
	Node* temp=root;
	char ch;
	
	int scount=0,flag=0;
	int num_char = len+1;
	
	while(scount<size-1)
	{	
		num_char++;
		EncryptFile.seekg(num_char,ios::beg);
		EncryptFile.get(ch);
		
		if(EncryptFile.eof())
		{
			EncryptFile.clear();
			ch=26;
			EncryptFile.seekg(num_char,ios::beg);
			scount--;
		}
		
		bin = "";
		bin = bitset<8>(ch).to_string();
		
		if(ch==26)
		{ flag = 1; }
		
		count=0;
		ch = 0;
		
		while (count<8)
		{
			letter = 0;
			
			if(scount>size)
			{ count=8; }
					
			if(temp->right==NULL && temp->left==NULL && count<8)
			{	
				scount++;
				letter=temp->c;
				WriteFile(letter);
				
				temp=root;
			}
			
			else if(count<8)
			{
				if(bin[count]=='0')
				{	
					temp=temp->left;
				}
				else if(bin[count]=='1')
				{
					temp=temp->right;
				}
			count++;
			}
		}	
	}
	WriteFile(char(8));
	EncryptFile.close();	
}


void loadingBar()
{
	system("color 03"); 
	char a=177, b=219;

	cout<<"\t\t\t\t\t\n\t\t\t\t\t";

	for(int i=0;i<15;i++)
	{ cout<<a; }

	cout<<"\r\t\t\t\t\t";

	for(int i=0;i<15;i++) 
	{
		cout<<b; 
		Sleep(250);
	}
}


int main()
{
	DLL doublyLL;
	int option = 0;
	
	
	while(option!=1 && option !=2)
	{
		system("color 75");
			
		cout<<"\t\t----------WELCOME TO TEXT FILE COMPRESSION USING HUFFMAN ENCODING----------"<<endl<<endl
			<<"\t1.ENCODING\n\t2.DECODING"<<endl<<endl
			<<"Enter Operation You Want To Perform: ";
		cin>>option;
		
		switch(option)
		{
			case 1: //encryption
			{
				
				system("cls");
				char c;
				string filename;
				
				cout<<"\n\n\n\t\t\t\tENTER FILE NAME TO BE ENCODED: ";
				cin>>filename;
				if(filename[filename.length()-4] != '.'){
					filename += ".txt";
				}
				
				ifstream txtfile;
				txtfile.open(filename.c_str());
				
				if(txtfile) 
				{	
			        while(txtfile.get(c)) 
					{ doublyLL.updatefreq(c); }
			    }
			    
				txtfile.close();
				
				int size = doublyLL.size;
			    char data[size];
			    int freq[size];
			    	
			    doublyLL.emptyLL(data,freq);
			    
				char ch[size];
			    string id[size];
			    system("cls");
				cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\tENCODING...\n";
				loadingBar();
				system("cls");
				system("color 0F");
			    cout<<"\t\t\t\tPRINTING ENCODED CODES FOR EACH CHARACTERS:"<<endl<<endl;
				HuffmanCodes(data, freq, size, ch, id);	
				break;
			}
			
			case 2: //decryption
			{
				system("cls");
				cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\tDECODING...\n";
				loadingBar();
				system("cls");
				system("color 0F");
				remove("newfile.txt");
				cout<<"\t\t\t\tPRINTING DECODED FILE:"<<endl<<endl<<endl;
				DecryptFile();
				break;
			}
			
			default: //in case of wrong choice
			{ 
				cout<<endl<<endl<<"ENTER CORRECT OPTION!!"; 
				Sleep(1000);
				system("cls");
				option = -1;
				break;
			}
		}
	}
    return 0;
}

