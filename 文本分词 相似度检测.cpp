#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <hash_map>
#include <math.h>

using namespace std;

struct tf_idf
{
	string word;
	double app;
	double tf;
	double app2;
	double tf2;
	double idf;
	struct tf_idf*next;
};
//链表结构体

struct tf_idf*create()
{
	struct tf_idf*head;
	head = new(struct tf_idf);
	head->next = NULL;
	head->word = "";
	head->app = 0;
	head->tf=0;
	head->idf=0;
	head->app2=0;
	head->tf2=0;
	return head;
}
//创建链表头结点
struct tf_idf *tt = create();
//建立链表头结点作为全局变量

struct tf_idf*longer(struct tf_idf*A,string p)
{
	struct tf_idf*head = A;
	struct tf_idf*B;
	while(1)
	{
		if (p == head->word)
		{
			head->app += 1;
			goto over2;
		}
		else if(head->next==NULL)
		{
			 B= new(struct tf_idf);
			 B->next = NULL;
			 B->word = p;
			 B->app = 1;
			 B->tf = 0;
			 B->app2 = 0;
			 B->tf2 = 0;
			 B->idf = 0.3;

			 head->next = B;
			goto over2;
		}
		head = head->next;
	}
over2:
	return A;
}
//第一个文本分词时链表延长算法
struct tf_idf*longer2(struct tf_idf*A, string p)
{
	struct tf_idf*head = A;
	struct tf_idf*B;
	while (1)
	{
		if (p == head->word)
		{
			head->app2 += 1;
			goto over2;
		}
		else if (head->next == NULL)
		{
			B = new(struct tf_idf);
			B->next = NULL;
			B->word = p;
			B->app = 0;
			B->tf = 0;
			B->app2 = 1;
			B->tf2 = 0;
			if(B->idf==0.3)
			{
				B->idf = 1;
			}
			else
			{
			    B->idf = 0.3;
			}


			head->next = B;
			goto over2;
		}
		head = head->next;
	}
over2:
	return A;
}
//第二个文本分词时链表延长算法
double tf(double n,double max)
{
	double tf;
	tf = n / max;
	return tf;
}
//求tf值
struct tf_idf*tf1(struct tf_idf*A, double num)
{
	struct tf_idf*head = A;
	head = head->next;
	while (head->next != NULL)
	{
		head->tf = tf(head->app, num);
		head = head->next;
	}
	return A;
}
//第一个文本分词时求tf
struct tf_idf*tf2(struct tf_idf*A, double num)
{
	struct tf_idf*head = A;
	head = head->next;
	while (head->next != NULL)
	{
		head->tf2 = tf(head->app2, num);
		head = head->next;
	}
	return A;
}
//第二个文本分词时求tf
int compare(string p1)
{
	int n=0;
	string line;
	ifstream infile("词典.txt");
	if(!infile.is_open())
	{
		cout << "打开词典失败" << endl;
		exit(-1);
	}
	else
	{
		while(getline(infile,line,'\n'))
		{
			if(p1.compare(line)==0)
			{
				n = 1;
				break;
			}
		}
	}
	return n;
}
//分词时用来和词典比较的函数
 string check(string p1)
 {
	 string p2 = "";//记录输出
	 string p3 = p1;//在内部计算时做中转
	 string test = p1;//在外部计算时做中转
	 int i = 0;
	 double num = 0;
	 while (1)
	 {
		 for (i = 0; i = i + 2;)
		 {
			 if ( compare(p3)==1)//比较成功
			 {
				 num++;
				 tt=longer(tt, p3);//
				 p2 = p3 +"/"+ p2;
				 int mark = i +2- p3.length();
				 test = test.substr(0, i+2-p3.length());
				 p3 = test;
				 if (mark== 0)
				 {
					 goto over;
				 }
				 break;
			 }
			 else if(i==int(test.length()))//到了最后一位
			 {
				 num++;
				 tt = longer(tt, p3);//
				 p2 = p3 + "/" + p2;
				 test = test.substr(0, i - 2);
				 p3 = test;
				 if (i == 2)
				 {
					 goto over;
				 }
				 break;
			 }
			 p3 = test.substr(i, test.length() - i);
		 }
	 }
 over:
	 tt = tf1(tt, num);
	 return p2;
 }
 //第一个文本分词函数
 string check2(string p1)
 {
	 string p2 = "";//记录输出
	 string p3 = p1;//在内部计算时做中转
	 string test = p1;//在外部计算时做中转
	 int i = 0;
	 double num=0;
	 while (1)
	 {
		 for (i = 0; i = i + 2;)
		 {
			 if (compare(p3) == 1)//比较成功
			 {
				 num++;
				 tt = longer2(tt, p3);//
				 p2 = p3 + "/" + p2;
				 int mark = i + 2 - p3.length();
				 test = test.substr(0, i + 2 - p3.length());
				 p3 = test;
				 if (mark == 0)
				 {
					 goto over;
				 }
				 break;
			 }
			 else if (i == int(test.length()))//到了最后一位
			 {
				 num++;
				 tt = longer2(tt, p3);//
				 p2 = p3 + "/" + p2;
				 test = test.substr(0, i - 2);
				 p3 = test;
				 if (i == 2)
				 {
					 goto over;
				 }
				 break;
			 }
			 p3 = test.substr(i, test.length() - i);
		 }
	 }
 over:
	 tt = tf2(tt, num);
	 return p2;
 }
 //第二个文本分词函数
int main(int argc,char*argv[])
{
	int i;
	double similar=0;
	double num1=0;
	double num2=0;
	double num3 = 0;
	string input;
	string output;
	ifstream infile("input.txt");
	if(!infile.is_open())
	{
		cout << "打开输入文件1失败" << endl;
		exit(-1);
	}	
	ofstream outfile("output.txt");
	if (!outfile.is_open())
	{
		cout << "打开输出文件失败" << endl;
		exit(-1);
	}

	while (getline(infile, input, '\n'))
	{
		output = "";
		if (input.length() <= 10)
		{
			output = check(input);
		}
		else
		{
			for (i = 0; (i * 10)<int((input.length())); i++)
			{
				if (input.length() - i * 10 >= 10)
				{
					output = check(input.substr(input.length() - 10 * (i + 1), 10)) + output;
				}
				else
				{
					output = check(input.substr(0, input.length() - i * 10)) + output;
				}
			}
		}
		outfile << output << endl;
		cout << output << endl;
	}
	
    infile=ifstream ("input2.txt");
	if (!infile.is_open())
	{
		cout << "打开输入文件1失败" << endl;
		exit(-1);
	}
	outfile=ofstream ("output2.txt");
	if (!outfile.is_open())
	{
		cout << "打开输出文件失败" << endl;
		exit(-1);
	}

	while (getline(infile, input, '\n'))
	{
		output = "";
		if (input.length() <= 10)
		{
			output = check2(input);
		}
		else
		{
			for (i = 0; (i * 10)<int((input.length())); i++)
			{
				if (input.length() - i * 10 >= 10)
				{
					output = check2(input.substr(input.length() - 10 * (i + 1), 10)) + output;
				}
				else
				{
					output = check2(input.substr(0, input.length() - i * 10)) + output;
				}
			}
		}
		outfile << output << endl;
		cout << output << endl;
	}
	while(tt->next!=NULL)
	{
		cout << tt->word << "     在第一篇文本的权重为" << (tt->tf)*(tt->idf) << "     在第二篇文本的权重为" << (tt->tf2)*(tt->idf) << endl;
		num1 += (tt->tf)*(tt->idf)*(tt->tf2)*(tt->idf);
		num2 += (tt->tf)*(tt->idf)*(tt->tf)*(tt->idf);
		num3 += (tt->tf2)*(tt->idf)*(tt->tf2)*(tt->idf);
		tt = tt->next;
	}

	similar = num1 /( sqrt(num2*num3));
	cout << "两篇文本的相似度为" << similar << endl;
	system("pause");
	return 0;
}