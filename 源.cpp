#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void search(int);
void menu(int);

struct books
{
	int book_num;
	char book_name[20];
	char ISBN[20];
	char book_writter[20];
	char type[20];
	char book_intro[600];
	char book_publisher[20];
	double price;
	int book_year = 0;
	int book_month = 0;
	int book_day = 0;
	int exist_now = 0;
	int exist_all = 0;
};

struct borrowlist
{
	int lib_num;
	char name[40];
	int year;
	int month;
	int day;
	struct borrowlist* next;
};

struct check
{
	int book_num;
	char book_name[40];
	char ISBN[20];
	char book_writter[20];
	char type[20];
	char book_intro[600];
	char book_publisher[20];
	double price;
	int book_year = 0;
	int book_month = 0;
	int book_day = 0;
	int exist_now = 0;
	int exist_all = 0;
	struct check* next;
};

void classify(int)
{
	struct books book;
	while (1)
	{
		printf("请输入入库书籍信息，书号输入0时结束入库：\n");

		//输入书籍信息
		printf("请输入书号：");
		scanf("%d", &book.book_num);
		if (book.book_num == 0)
		{
			printf("已关闭入库。\n");
			break;
		}
		while (book.book_num < 0)
		{
			printf("书号输入错误！请重新输入：");
			scanf("%d", &book.book_num);
		}
		printf("请输入书名：");
		scanf("\n%[^\n]", &book.book_name);
		printf("请输入ISBN：");
		scanf("%s", &book.ISBN);
		printf("请输入作者：");
		scanf("\n%[^\n]", &book.book_writter);
		printf("请输入类型：");
		scanf("\n%[^\n]", &book.type);
		printf("请输入书籍简介：");
		scanf("\n%[^\n]", &book.book_intro);
		printf("请输入出版社：");
		scanf("\n%[^\n]", &book.book_publisher);
		printf("请输入价格：");
		scanf("%lf", &book.price);
		while (book.price <= 0)
		{
			printf("价格输入错误！请重新输入：");
			scanf("%lf", &book.price);
		}
		printf("请输入出版日期（格式为 year.month.day)：");
		scanf("%d.%d.%d", &book.book_year, &book.book_month, &book.book_day);
		while ((book.book_month <= 0 || book.book_month > 12) || (book.book_day <= 0 || book.book_day > 31))
		{
			printf("出版日期输入错误！请重新输入：");
			scanf("%d.%d.%d", &book.book_year, &book.book_month, &book.book_day);
		}

		//读取文件
		FILE* fp;
		if ((fp = fopen("book.txt", "r")) == NULL)
		{
			printf("图书管理文件打开失败。\n");
			return;
		}

		//建立链表
		struct check* phead, * pend, * pnew;
		phead = NULL;
		pend = pnew = (struct check*)malloc(sizeof(struct check));
		int panduan = 0;
		int n = 0;
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		while (!feof(fp))
		{
			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			//判断书号是否重叠，书名是否相同
			if (pnew->book_num == book.book_num && strcmp(pnew->book_name, book.book_name) != 0 && panduan == 0)
			{
				printf("登记失败！该书号已存在。\n");
				panduan = -1;
			}
			else if (strcmp(pnew->book_name, book.book_name) == 0 && panduan == 0)
			{
				printf("该图书已登记，已增加总库存量。\n");
				pnew->exist_all += 1;
				pnew->exist_now += 1;
				panduan = 1;
			}

			pnew = (struct check*)malloc(sizeof(struct check));
			fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
			if (pnew->book_num == pend->book_num)
			{
				break;
			}
			n++;
		}
		free(pnew);
		fclose(fp);

		//打开文件，写入旧信息
		if ((fp = fopen("book.txt", "w")) == NULL)
		{
			printf("图书管理文件打开失败。\n");
			return;
		}
		while (phead != NULL)
		{
			if (n == 0)
			{
				break;
			}
			fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
			phead = phead->next;
		}
		fclose(fp);

		//打开文件，添加新书籍
		if (panduan == 0)
		{
			if ((fp = fopen("book.txt", "a")) == NULL)
			{
				printf("存入失败！图书管理文件打开失败。\n");
				return;
			}
			fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", book.book_num, book.book_name, book.ISBN, book.book_writter, book.type, book.book_intro, book.book_publisher, book.price, book.book_year, book.book_month, book.book_day, ++book.exist_now, ++book.exist_all);
			printf("登记成功！\n");
		}
		fclose(fp);
	}
}

void clear(int)
{
	//输入所要清除书名
	char name[40];
	printf("请输入所要清除书籍名：");
	scanf("\n%[^\n]", &name);

	//读取文件，建立链表
	FILE* fp;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("图书管理文件打开失败。");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (phead == NULL)
		{
			pnew->next = NULL;
			phead = pnew;
			pend = pnew;
		}
		else
		{
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}

		pnew = (struct check*)malloc(sizeof(struct check));
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		if (pnew->book_num == pend->book_num)
		{
			break;
		}
	}
	free(pnew);
	fclose(fp);

	//判断链表中是否有所要删除书籍，存在则删去
	int found = 0;
	pend = pnew = phead;
	while (pnew != NULL)
	{
		if (strcmp(pnew->book_name, name) == 0)
		{
			found = 1;
			if (pnew == phead)
			{
				phead = phead->next;
				free(pnew);
				pnew = pend = phead;
				break;
			}
			else
			{
				pend->next = pnew->next;
				break;
			}
		}
		pend = pnew;
		pnew = pnew->next;
	}

	//如果不存在，退出
	if (found == 0)
	{
		printf("清除失败！查无此书！\n ");
		return;
	}

	//存在，重新向文件写入删除后的链表
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("图书管理文件写入失败。");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	printf("清除成功！\n");
	fclose(fp);

}

void borrow(int)
{
	//输入借书信息
	struct borrowlist reader;
	printf("请输入图书证号：");
	scanf("%d", &reader.lib_num);
	while (reader.lib_num <= 0)
	{
		printf("图书证号输入错误！请重新输入：");
		scanf("%d", &reader.lib_num);
	}
	printf("请输入借阅书籍名：");
	scanf("\n%[^\n]", &reader.name);
	printf("请输入借阅日期：");
	scanf("%d.%d.%d", &reader.year, &reader.month, &reader.day);
	while ((reader.year <= 0) || (reader.month <= 0 || reader.month > 12) || (reader.day <= 0 || reader.day > 31))
	{
		printf("借阅日期输入错误！，请重新输入：");
		scanf("%d.%d.%d", &reader.year, &reader.month, &reader.day);
	}

	//打开图书管理文件，建立链表
	FILE* fp;
	int found = 0;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("图书管理文件打开失败。");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (strcmp(reader.name, pnew->book_name) == 0)
		{
			found = 1;     //判断是否有此书
			if (pnew->exist_now == 0)
			{
				printf("抱歉，库存不足，借阅失败。\n");       //判断库存是否有剩余，无剩余直接退出
				return;
			}
			pnew->exist_now--;     //有剩余，现库存量减一
		}

		if (phead == NULL)
		{
			pnew->next = NULL;
			phead = pnew;
			pend = pnew;
		}
		else
		{
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}

		pnew = (struct check*)malloc(sizeof(struct check));
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		if (pnew->book_num == pend->book_num)
		{
			break;
		}
	}
	free(pnew);
	fclose(fp);

	//判断图书管理文件里是否有此书，若无，直接退出
	if (found == 0)
	{
		printf("借阅失败！查无此书！\n");
		return;
	}

	//将减少现库存量后的链表写入图书管理文件
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("图书管理文件写入失败\n");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	fclose(fp);

	//登记借书信息到借阅管理文件
	FILE* fp2;
	if ((fp2 = fopen("borrowbook.txt", "a")) == NULL)
	{
		printf("借阅管理文件打开失败。\n");
		return;
	}
	fprintf(fp2, "%d\n%s\n%d %d %d\n\n", reader.lib_num, reader.name, reader.year, reader.month, reader.day);
	printf("借阅成功！\n");
	fclose(fp2);

}

void back(int)
{
	//输入归还书籍信息
	int lib_num;
	char book_name[40];
	printf("请输入图书证号：");
	scanf("%d", &lib_num);
	while (lib_num <= 0)
	{
		printf("图书证号输入错误！请重新输入：");
		scanf("%d", &lib_num);
	}
	printf("请输入归还书籍名： ");
	scanf("\n%[^\n]", &book_name);


	{
		//从借阅管理文件读取信息，建立链表
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("借阅管理文件打开失败。\n");
			return;
		}
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
			fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
			if (pnew->lib_num == 0)
			{
				break;
			}
		}
		free(pnew);
		fclose(fp2);

		//判断归还书籍和图书证号是否存在于借阅管理文件，若存在，删去
		int found = 0;
		pnew = pend = phead;
		while (pnew != NULL)
		{
			if (pnew->lib_num == lib_num && strcmp(pnew->name, book_name) == 0)
			{
				found = 1;    //标识存在
				if (pnew == phead)
				{
					phead = phead->next;
					free(pnew);
					break;
				}
				else
				{
					pend->next = pnew->next;
				}
			}
			pend = pnew;
			pnew = pnew->next;
		}

		//当不存在时，直接退出
		if (found == 0)
		{
			printf("归还失败！请检查图书证号及书名是否正确。\n");
			return;
		}

		//存在时，将删去后的新链表存回借阅管理文件
		if ((fp2 = fopen("borrowbook.txt", "w")) == NULL)
		{
			printf("借阅管理文件写入失败。\n");
			return;
		}
		while (phead != NULL)
		{
			fprintf(fp2, "%d\n%s\n%d %d %d\n\n", phead->lib_num, phead->name, phead->year, phead->month, phead->day);
			phead = phead->next;
		}
		fclose(fp2);
	}

	//从图书管理文件读取信息，建立链表
	FILE* fp;
	int found = 0;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("图书管理文件打开失败。");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (strcmp(book_name, pnew->book_name) == 0)
		{
			found = 1;     //标示此书仍在库中
			pnew->exist_now++;     //现存量加一
		}

		if (phead == NULL)
		{
			pnew->next = NULL;
			phead = pnew;
			pend = pnew;
		}
		else
		{
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}

		pnew = (struct check*)malloc(sizeof(struct check));
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		if (pnew->book_num == pend->book_num)
		{
			break;
		}
	}
	free(pnew);
	fclose(fp);

	//库中该书已被清除时，直接退出
	if (found == 0)
	{
		printf("归还失效，该书籍已被从库中清除，请将书籍交予前台。\n");
		return;
	}

	//库中该书仍存在，将增加现存量后的新链表写回图书管理文件
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("图书管理文件打开失败。\n");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	printf("归还成功！\n");
	fclose(fp);

}

//算出任意两个日期的差值（单位：天）
int day_diff(int year_start, int month_start, int day_start, int year_end, int month_end, int day_end)
{
	int y2, m2, d2;
	int y1, m1, d1;

	m1 = (month_start + 9) % 12;
	y1 = year_start - m1 / 10;
	d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_start - 1);

	m2 = (month_end + 9) % 12;
	y2 = year_end - m2 / 10;
	d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day_end - 1);

	return (d2 - d1);
}

void borrowsearch(int)
{
	int book_num;
	char name[40];
	int lib_num;
	int now_year, now_month, now_day;
	int backtime;
	int n = 0, num = 0;

	//菜单界面
	while (1)
	{
		printf("\n\t\t       借阅查询       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)指定书名查询\n");
		printf("\t\t2)指定图书证查询\n");
		printf("\t\t3)逾期查询\n");
		printf("\t\t4)所有借阅\n");
		printf("\t\t5)退回查询主界面\n");
		printf("\t\t======================\n");
		printf("\t\t输入序号：");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("请输入查询书名：");
			scanf("\n%[^\n]", &name);
			break;
		}
		else if (n == 2)
		{
			printf("请输入所要查询图书证：");
			scanf("%d", &lib_num);
			while (lib_num <= 0)
			{
				printf("图书证输入错误！请重新输入：");
				scanf("%d", &lib_num);
			}
			break;
		}
		else if (n == 3)
		{
			printf("请输入当前时间(年.月.日)：");
			scanf("%d.%d.%d", &now_year, &now_month, &now_day);
			while ((now_year <= 0) || (now_month <= 0 && now_month > 12) || (now_day <= 0 && now_day > 12))
			{
				printf("日期输入错误！请重新输入：");
				scanf("%d.%d.%d", &now_year, &now_month, &now_day);
			}
			printf("请输入最大借阅期限（单位：天）：");
			scanf("%d", &backtime);
			while (backtime < 0)
			{
				printf("最大借阅期限输入错误！请重新输入： ");
				scanf("%d", &backtime);
			}
			break;
		}
		else if (n == 4)
		{
			printf("以下为所有借阅记录：\n");
			break;
		}
		else if (n == 5)
		{
			printf("已退回查询主界面。\n");
			return;
		}
	}

	//不同选项详细操作
	if (n == 1)
	{
		num = 0;

		//读取借阅管理文件，建立链表
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("借阅管理文件打开失败。\n");
			return;
		}
		printf("你所要查询借阅情况的书籍为：%s,以下为相关信息：\n", name);
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (strcmp(pnew->name, name) == 0)
			{
				printf("图书证号：%d 借阅日期：%d年.%d月.%d日\n", pnew->lib_num, pnew->year, pnew->month, pnew->day);
				num++;  //表示已借出的该书籍的本数。
			}

			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
			fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
			if (pnew->lib_num == 0)
			{
				break;
			}
		}
		free(pnew);
		fclose(fp2);

		//后续格式
		if (num)
		{
			printf("共找到%d条该图书借阅记录。\n", num);
		}
		else
		{
			printf("未找到任何有关该图书的借阅记录，请确定书名输入是否正确，或检查库中是否存在该书籍。\n");
		}
	}

	else if (n == 2)
	{
		num = 0;

		//从借阅管理文件读取信息，建立链表
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("借阅管理文件打开失败。\n");
			return;
		}
		printf("你所要查询借阅情况的图书证号为：%d ,以下为该用户所有借阅情况：\n", lib_num);
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (pnew->lib_num == lib_num)
			{
				printf("书名：%s 借阅日期：%d年.%d月.%d日\n", pnew->name, pnew->year, pnew->month, pnew->day);
				num++;  //表示该用户已借的书籍数量
			}

			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
			fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
			if (pnew->lib_num == 0)
			{
				break;
			}
		}
		free(pnew);
		fclose(fp2);

		//后续格式
		if (num)
		{
			printf("共找到%d条该用户借阅记录。\n", num);
		}
		else
		{
			printf("未找到任何有关该用户的借阅记录。\n");
		}
	}

	else if (n == 3)
	{
		int c = 0;
		num = 0;

		//从借阅管理文件读取信息，建立链表
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("借阅管理文件打开失败。\n");
			return;
		}
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			num = day_diff(pnew->year, pnew->month, pnew->day, now_year, now_month, now_day);  //计算现在时间与借阅时间的日期差
			if (num > backtime)
			{
				c++;  //表示已逾期的数量
				printf("图书证号：%d 书名：%s 借阅日期：%d年.%d月.%d日 已逾期%d天\n", pnew->lib_num, pnew->name, pnew->year, pnew->month, pnew->day, num - backtime);
			}
			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
			fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
			num = 0;
			if (pnew->lib_num == 0)
			{
				break;
			}
		}
		free(pnew);
		fclose(fp2);

		//后续格式
		if (c)
		{
			printf("共找到%d条逾期借阅记录。\n", c);
		}
		else
		{
			printf("未找到任何逾期借阅记录。\n");
		}
	}
	else if (n == 4)
	{
		num = 0;

		//从借阅管理文件读取信息，建立链表
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("借阅管理文件打开失败。\n");
			return;
		}
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (pnew->name != '\0')
			{
				printf("图书证号：%d 书名：%s 借阅日期：%d年.%d月.%d日\n", pnew->lib_num, pnew->name, pnew->year, pnew->month, pnew->day);  //逐条输出所有借阅情况
			}
			if (phead == NULL)
			{
				pnew->next = NULL;
				phead = pnew;
				pend = pnew;
			}
			else
			{
				pnew->next = NULL;
				pend->next = pnew;
				pend = pnew;
			}

			pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
			fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
			if (pnew->lib_num == 0)
			{
				break;
			}
			num++;
		}
		free(pnew);
		fclose(fp2);

		//后续格式
		if (num)
		{
			printf("共找到%d条借阅记录。\n\n", num);
		}
		else
		{
			printf("未找到任何借阅记录。\n\n");
		}
	}


}

void booksearch(int)
{
	//声明所用变量
	int book_num;
	char name[40];
	char ISBN[20];
	char writter[20];
	char type[20];

	//界面
	int n = 0;
	while (1)
	{
		printf("\n\t\t       书籍查询       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)书号查询\n");
		printf("\t\t2)书名查询\n");
		printf("\t\t3)ISBN查询\n");
		printf("\t\t4)作者查询\n");
		printf("\t\t5)类型查询\n");
		printf("\t\t6)退回查询主界面\n");
		printf("\t\t======================\n");
		printf("\t\t输入序号：");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("请输入书号：");
			scanf("%d", &book_num);
			while (book_num <= 0)
			{
				printf("书号输入错误！请重新输入：");
				scanf("%d", &book_num);
			}
			break;
		}
		else if (n == 2)
		{
			printf("请输入书名：");
			scanf("\n%[^\n]", name);
			break;
		}
		else if (n == 3)
		{
			printf("请输入ISBN：");
			scanf("%s", &ISBN);
			break;
		}
		else if (n == 4)
		{
			printf("请输入作者名字：");
			scanf("\n%[^\n]", writter);
			break;
		}
		else if (n == 5)
		{
			printf("请输入类型：");
			scanf("\n%[^\n]", type);
			break;
		}
		else if (n == 6)
		{
			printf("已退回。\n");
			return;
		}
		else
		{
			printf("输入错误！请重新输入:");
			scanf("%d", &n);
		}
	}

	//遍历图书管理文件，建立链表
	FILE* fp;
	int found = 0;
	int num = 0;
	if (n == 4)     //查询作者时的特殊格式
	{
		printf("\n你所要查询作者为： %s  查询结果如下：\n", writter);
	}
	else if (n == 5)   //查询类型时的特殊格式
	{
		printf("\n你所要查询类型为： %s 查询结果如下：\n", type);
	}
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("图书管理文件打开失败。");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (n == 1 && book_num == pnew->book_num)
		{
			printf("查询成功！图书信息如下：\n");
			printf("\n书号：%05d\n书名：%s\nISBN：%s\n作者：%s\n类型：%s\n简介：%s\n出版社：%s\n价格：%.2f\n出版日期：%d.%02d.%02d\n现库存量：%d\n总库存量：%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;  //表示已找到，下同
		}
		else if (n == 2 && strcmp(name, pnew->book_name) == 0)
		{
			printf("查询成功！图书信息如下：\n");
			printf("\n书号：%05d\n书名：%s\nISBN：%s\n作者：%s\n类型：%s\n简介：%s\n出版社：%s\n价格：%.2f\n出版日期：%d.%02d.%02d\n现库存量：%d\n总库存量：%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
		}
		else if (n == 3 && strcmp(ISBN, pnew->ISBN) == 0)
		{
			printf("查询成功！图书信息如下：\n");
			printf("\n书号：%05d\n书名：%s\nISBN：%s\n作者：%s\n类型：%s\n简介：%s\n出版社：%s\n价格：%.2f\n出版日期：%d.%02d.%02d\n现库存量：%d\n总库存量：%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
		}
		else if (n == 4 && strcmp(writter, pnew->book_writter) == 0)
		{
			printf("书号：%05d  书名：%s  ISBN：%s  出版社：%s  价格：%.2f  出版日期：%d.%02d.%02d  现库存量：%d  总库存量：%d\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);			
			found = 1;
			num++;   //表示同一作者所著书籍数量
		}
		else if (n == 5 && strcmp(type, pnew->type) == 0)
		{
			printf("书号：%05d  书名：%s  作者：%s  ISBN：%s  出版社：%s  价格：%.2f  出版日期：%d.%02d.%02d  现库存量：%d  总库存量：%d\n", pnew->book_num, pnew->book_name, pnew->book_writter, pnew->ISBN, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
			num++;  //表示同一类型书籍数量
		}


		if (phead == NULL)
		{
			pnew->next = NULL;
			phead = pnew;
			pend = pnew;
		}
		else
		{
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}

		pnew = (struct check*)malloc(sizeof(struct check));
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		if (pnew->book_num == pend->book_num)
		{
			break;
		}
	}
	free(pnew);
	fclose(fp);

	//当未找到指定内容时
	if (found == 0)
	{
		if (n == 1)
		{
			printf("未找到指定书号！\n");
		}
		else if (n == 2)
		{
			printf("未找到该书籍！\n");
		}
		else if (n == 3)
		{
			printf("未找到与输入ISBN相关的书籍！\n");
		}
		else if (n == 4)
		{
			printf("未找到与该作者相关书籍！\n");
		}
		else if (n == 5)
		{
			printf("未找到相关类型书籍！\n");
		}
	}

	//查询作者或类型时结尾处的特殊格式（已找到）
	if (n == 4 && found == 1)
	{
		printf("查询结束，共找到该作者所著书籍%d本。\n", num);
	}
	else if (n == 5 && found == 1)
	{
		printf("查询结束，共找到%d本该类型书籍。\n", num);
	}

	int n1 = 0;
	printf("\n\t\t       返回提示       ");
	printf("\n\t\t----------------------\n");
	printf("\t\t1)返回借阅查询系统\n");
	printf("\t\t2)返回书籍查询系统\n");
	printf("\t\t3)返回查询系统\n");
	printf("\t\t4)返回主菜单\n");
	printf("\t\t----------------------\n");
	printf("\t\t输入序号：");
	scanf("%d", &n1);
	while (n1 <= 0 || n1 > 4)
	{
		printf("输入错误！请重新输入:");
		scanf("%d", &n1);
	}
	if (n1 == 1)
	{
		borrowsearch(n1);
	}
	else if (n1 == 2)
	{
		booksearch(n1);
	}
	else if (n1 == 3)
	{
		search(n1);
	}
	else if (n == 4)
	{
		menu(n1);
	}
	else
	{
		printf("输入错误！\n");
	}
}

void search(int)
{
	int n = 0;
	while (1)
	{
		printf("\n\t\t       查询系统       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)书籍查询\n");
		printf("\t\t2)借阅查询\n");
		printf("\t\t3)退回主界面\n");
		printf("\t\t======================\n");
		printf("\t\t输入序号：");
		scanf("%d", &n);

		switch (n)
		{
		case 1:
			booksearch(n);
			break;
		case 2:
			borrowsearch(n);
			break;
		case 3:
			printf("\n已退回。");
			menu(n);
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

void cout(int)
{
	int i = 0, n = 0, j = 0;
	int booknum = 0;
	int nowincluded = 0;
	int allincluded = 0;
	struct check classify2[1000], temp;
	FILE* fp=fopen("book.txt", "r");

	if (fp == NULL)
	{
		printf("图书管理文件打开失败。\n");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	classify2[0] = *pnew;
	while (!feof(fp))
	{
		if (pnew->book_name != '\0')
		{
			booknum++;
			nowincluded += pnew->exist_now;
			allincluded += pnew->exist_all;
		}

		if (phead == NULL)
		{
			pnew->next = NULL;
			phead = pnew;
			pend = pnew;
		}
		else
		{
			pnew->next = NULL;
			pend->next = pnew;
			pend = pnew;
		}

		pnew = (struct check*)malloc(sizeof(struct check));
		fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
		n++;
		classify2[n] = *pnew;
		if (pnew->book_num == pend->book_num)
		{
			break;
		}
	}
	free(pnew);
	fclose(fp);

	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			if (classify2[i].book_num > classify2[j].book_num)
			{
				temp = classify2[i];
				classify2[i] = classify2[j];
				classify2[j] = temp;
			}
		}
	}

	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("图书管理文件写入失败!\n");
		return;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", classify2[i].book_num, classify2[i].book_name, classify2[i].ISBN, classify2[i].book_writter, classify2[i].type, classify2[i].book_intro, classify2[i].book_publisher, classify2[i].price, classify2[i].book_year, classify2[i].book_month, classify2[i].book_day, classify2[i].exist_now, classify2[i].exist_all);
	}
	fclose(fp);
	printf("已整理完毕。图书库藏书 %d本，总库存 %d本，现库存为 %d本，已借出书籍为 %d本。\n", booknum++, allincluded, nowincluded, allincluded - nowincluded);
}

void menu(int)
{
	int n = 0;
	while (n != 7)
	{
		printf("\n\t\t     图书管理系统       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)采编入库\n");
		printf("\t\t2)清除库存\n");
		printf("\t\t3)借阅\n");
		printf("\t\t4)归还\n");
		printf("\t\t5)查询图书信息\n");
		printf("\t\t6)统计并整理图书信息\n");
		printf("\t\t7)退出\n");
		printf("\t\t======================\n");
		printf("\t\t输入序号：");
		scanf("%d", &n);

		switch (n)
		{
		case 1:
			classify(n);
			break;
		case 2:
			clear(n);
			break;
		case 3:
			borrow(n);
			break;
		case 4:
			back(n);
			break;
		case 5:
			search(n);
			break;
		case 6:
			cout(n);
			break;
		case 7:
			printf("\n已关闭。");
			exit(0);
		default:
			printf("输入错误！\n");
			break;
		}

	}
}

int main()
{
	menu(0);
	return 0;
}