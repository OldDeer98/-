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
		printf("����������鼮��Ϣ���������0ʱ������⣺\n");

		//�����鼮��Ϣ
		printf("��������ţ�");
		scanf("%d", &book.book_num);
		if (book.book_num == 0)
		{
			printf("�ѹر���⡣\n");
			break;
		}
		while (book.book_num < 0)
		{
			printf("�������������������룺");
			scanf("%d", &book.book_num);
		}
		printf("������������");
		scanf("\n%[^\n]", &book.book_name);
		printf("������ISBN��");
		scanf("%s", &book.ISBN);
		printf("���������ߣ�");
		scanf("\n%[^\n]", &book.book_writter);
		printf("���������ͣ�");
		scanf("\n%[^\n]", &book.type);
		printf("�������鼮��飺");
		scanf("\n%[^\n]", &book.book_intro);
		printf("����������磺");
		scanf("\n%[^\n]", &book.book_publisher);
		printf("������۸�");
		scanf("%lf", &book.price);
		while (book.price <= 0)
		{
			printf("�۸�����������������룺");
			scanf("%lf", &book.price);
		}
		printf("������������ڣ���ʽΪ year.month.day)��");
		scanf("%d.%d.%d", &book.book_year, &book.book_month, &book.book_day);
		while ((book.book_month <= 0 || book.book_month > 12) || (book.book_day <= 0 || book.book_day > 31))
		{
			printf("������������������������룺");
			scanf("%d.%d.%d", &book.book_year, &book.book_month, &book.book_day);
		}

		//��ȡ�ļ�
		FILE* fp;
		if ((fp = fopen("book.txt", "r")) == NULL)
		{
			printf("ͼ������ļ���ʧ�ܡ�\n");
			return;
		}

		//��������
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

			//�ж�����Ƿ��ص��������Ƿ���ͬ
			if (pnew->book_num == book.book_num && strcmp(pnew->book_name, book.book_name) != 0 && panduan == 0)
			{
				printf("�Ǽ�ʧ�ܣ�������Ѵ��ڡ�\n");
				panduan = -1;
			}
			else if (strcmp(pnew->book_name, book.book_name) == 0 && panduan == 0)
			{
				printf("��ͼ���ѵǼǣ��������ܿ������\n");
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

		//���ļ���д�����Ϣ
		if ((fp = fopen("book.txt", "w")) == NULL)
		{
			printf("ͼ������ļ���ʧ�ܡ�\n");
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

		//���ļ���������鼮
		if (panduan == 0)
		{
			if ((fp = fopen("book.txt", "a")) == NULL)
			{
				printf("����ʧ�ܣ�ͼ������ļ���ʧ�ܡ�\n");
				return;
			}
			fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", book.book_num, book.book_name, book.ISBN, book.book_writter, book.type, book.book_intro, book.book_publisher, book.price, book.book_year, book.book_month, book.book_day, ++book.exist_now, ++book.exist_all);
			printf("�Ǽǳɹ���\n");
		}
		fclose(fp);
	}
}

void clear(int)
{
	//������Ҫ�������
	char name[40];
	printf("��������Ҫ����鼮����");
	scanf("\n%[^\n]", &name);

	//��ȡ�ļ�����������
	FILE* fp;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("ͼ������ļ���ʧ�ܡ�");
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

	//�ж��������Ƿ�����Ҫɾ���鼮��������ɾȥ
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

	//��������ڣ��˳�
	if (found == 0)
	{
		printf("���ʧ�ܣ����޴��飡\n ");
		return;
	}

	//���ڣ��������ļ�д��ɾ���������
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("ͼ������ļ�д��ʧ�ܡ�");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	printf("����ɹ���\n");
	fclose(fp);

}

void borrow(int)
{
	//���������Ϣ
	struct borrowlist reader;
	printf("������ͼ��֤�ţ�");
	scanf("%d", &reader.lib_num);
	while (reader.lib_num <= 0)
	{
		printf("ͼ��֤������������������룺");
		scanf("%d", &reader.lib_num);
	}
	printf("����������鼮����");
	scanf("\n%[^\n]", &reader.name);
	printf("������������ڣ�");
	scanf("%d.%d.%d", &reader.year, &reader.month, &reader.day);
	while ((reader.year <= 0) || (reader.month <= 0 || reader.month > 12) || (reader.day <= 0 || reader.day > 31))
	{
		printf("��������������󣡣����������룺");
		scanf("%d.%d.%d", &reader.year, &reader.month, &reader.day);
	}

	//��ͼ������ļ�����������
	FILE* fp;
	int found = 0;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("ͼ������ļ���ʧ�ܡ�");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (strcmp(reader.name, pnew->book_name) == 0)
		{
			found = 1;     //�ж��Ƿ��д���
			if (pnew->exist_now == 0)
			{
				printf("��Ǹ����治�㣬����ʧ�ܡ�\n");       //�жϿ���Ƿ���ʣ�࣬��ʣ��ֱ���˳�
				return;
			}
			pnew->exist_now--;     //��ʣ�࣬�ֿ������һ
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

	//�ж�ͼ������ļ����Ƿ��д��飬���ޣ�ֱ���˳�
	if (found == 0)
	{
		printf("����ʧ�ܣ����޴��飡\n");
		return;
	}

	//�������ֿ�����������д��ͼ������ļ�
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("ͼ������ļ�д��ʧ��\n");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	fclose(fp);

	//�Ǽǽ�����Ϣ�����Ĺ����ļ�
	FILE* fp2;
	if ((fp2 = fopen("borrowbook.txt", "a")) == NULL)
	{
		printf("���Ĺ����ļ���ʧ�ܡ�\n");
		return;
	}
	fprintf(fp2, "%d\n%s\n%d %d %d\n\n", reader.lib_num, reader.name, reader.year, reader.month, reader.day);
	printf("���ĳɹ���\n");
	fclose(fp2);

}

void back(int)
{
	//����黹�鼮��Ϣ
	int lib_num;
	char book_name[40];
	printf("������ͼ��֤�ţ�");
	scanf("%d", &lib_num);
	while (lib_num <= 0)
	{
		printf("ͼ��֤������������������룺");
		scanf("%d", &lib_num);
	}
	printf("������黹�鼮���� ");
	scanf("\n%[^\n]", &book_name);


	{
		//�ӽ��Ĺ����ļ���ȡ��Ϣ����������
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("���Ĺ����ļ���ʧ�ܡ�\n");
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

		//�жϹ黹�鼮��ͼ��֤���Ƿ�����ڽ��Ĺ����ļ��������ڣ�ɾȥ
		int found = 0;
		pnew = pend = phead;
		while (pnew != NULL)
		{
			if (pnew->lib_num == lib_num && strcmp(pnew->name, book_name) == 0)
			{
				found = 1;    //��ʶ����
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

		//��������ʱ��ֱ���˳�
		if (found == 0)
		{
			printf("�黹ʧ�ܣ�����ͼ��֤�ż������Ƿ���ȷ��\n");
			return;
		}

		//����ʱ����ɾȥ����������ؽ��Ĺ����ļ�
		if ((fp2 = fopen("borrowbook.txt", "w")) == NULL)
		{
			printf("���Ĺ����ļ�д��ʧ�ܡ�\n");
			return;
		}
		while (phead != NULL)
		{
			fprintf(fp2, "%d\n%s\n%d %d %d\n\n", phead->lib_num, phead->name, phead->year, phead->month, phead->day);
			phead = phead->next;
		}
		fclose(fp2);
	}

	//��ͼ������ļ���ȡ��Ϣ����������
	FILE* fp;
	int found = 0;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("ͼ������ļ���ʧ�ܡ�");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (strcmp(book_name, pnew->book_name) == 0)
		{
			found = 1;     //��ʾ�������ڿ���
			pnew->exist_now++;     //�ִ�����һ
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

	//���и����ѱ����ʱ��ֱ���˳�
	if (found == 0)
	{
		printf("�黹ʧЧ�����鼮�ѱ��ӿ���������뽫�鼮����ǰ̨��\n");
		return;
	}

	//���и����Դ��ڣ��������ִ������������д��ͼ������ļ�
	if ((fp = fopen("book.txt", "w")) == NULL)
	{
		printf("ͼ������ļ���ʧ�ܡ�\n");
		return;
	}
	while (phead != NULL)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", phead->book_num, phead->book_name, phead->ISBN, phead->book_writter, phead->type, phead->book_intro, phead->book_publisher, phead->price, phead->book_year, phead->book_month, phead->book_day, phead->exist_now, phead->exist_all);
		phead = phead->next;
	}
	printf("�黹�ɹ���\n");
	fclose(fp);

}

//��������������ڵĲ�ֵ����λ���죩
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

	//�˵�����
	while (1)
	{
		printf("\n\t\t       ���Ĳ�ѯ       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)ָ��������ѯ\n");
		printf("\t\t2)ָ��ͼ��֤��ѯ\n");
		printf("\t\t3)���ڲ�ѯ\n");
		printf("\t\t4)���н���\n");
		printf("\t\t5)�˻ز�ѯ������\n");
		printf("\t\t======================\n");
		printf("\t\t������ţ�");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("�������ѯ������");
			scanf("\n%[^\n]", &name);
			break;
		}
		else if (n == 2)
		{
			printf("��������Ҫ��ѯͼ��֤��");
			scanf("%d", &lib_num);
			while (lib_num <= 0)
			{
				printf("ͼ��֤����������������룺");
				scanf("%d", &lib_num);
			}
			break;
		}
		else if (n == 3)
		{
			printf("�����뵱ǰʱ��(��.��.��)��");
			scanf("%d.%d.%d", &now_year, &now_month, &now_day);
			while ((now_year <= 0) || (now_month <= 0 && now_month > 12) || (now_day <= 0 && now_day > 12))
			{
				printf("��������������������룺");
				scanf("%d.%d.%d", &now_year, &now_month, &now_day);
			}
			printf("���������������ޣ���λ���죩��");
			scanf("%d", &backtime);
			while (backtime < 0)
			{
				printf("��������������������������룺 ");
				scanf("%d", &backtime);
			}
			break;
		}
		else if (n == 4)
		{
			printf("����Ϊ���н��ļ�¼��\n");
			break;
		}
		else if (n == 5)
		{
			printf("���˻ز�ѯ�����档\n");
			return;
		}
	}

	//��ͬѡ����ϸ����
	if (n == 1)
	{
		num = 0;

		//��ȡ���Ĺ����ļ�����������
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("���Ĺ����ļ���ʧ�ܡ�\n");
			return;
		}
		printf("����Ҫ��ѯ����������鼮Ϊ��%s,����Ϊ�����Ϣ��\n", name);
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (strcmp(pnew->name, name) == 0)
			{
				printf("ͼ��֤�ţ�%d �������ڣ�%d��.%d��.%d��\n", pnew->lib_num, pnew->year, pnew->month, pnew->day);
				num++;  //��ʾ�ѽ���ĸ��鼮�ı�����
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

		//������ʽ
		if (num)
		{
			printf("���ҵ�%d����ͼ����ļ�¼��\n", num);
		}
		else
		{
			printf("δ�ҵ��κ��йظ�ͼ��Ľ��ļ�¼����ȷ�����������Ƿ���ȷ����������Ƿ���ڸ��鼮��\n");
		}
	}

	else if (n == 2)
	{
		num = 0;

		//�ӽ��Ĺ����ļ���ȡ��Ϣ����������
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("���Ĺ����ļ���ʧ�ܡ�\n");
			return;
		}
		printf("����Ҫ��ѯ���������ͼ��֤��Ϊ��%d ,����Ϊ���û����н��������\n", lib_num);
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (pnew->lib_num == lib_num)
			{
				printf("������%s �������ڣ�%d��.%d��.%d��\n", pnew->name, pnew->year, pnew->month, pnew->day);
				num++;  //��ʾ���û��ѽ���鼮����
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

		//������ʽ
		if (num)
		{
			printf("���ҵ�%d�����û����ļ�¼��\n", num);
		}
		else
		{
			printf("δ�ҵ��κ��йظ��û��Ľ��ļ�¼��\n");
		}
	}

	else if (n == 3)
	{
		int c = 0;
		num = 0;

		//�ӽ��Ĺ����ļ���ȡ��Ϣ����������
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("���Ĺ����ļ���ʧ�ܡ�\n");
			return;
		}
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			num = day_diff(pnew->year, pnew->month, pnew->day, now_year, now_month, now_day);  //��������ʱ�������ʱ������ڲ�
			if (num > backtime)
			{
				c++;  //��ʾ�����ڵ�����
				printf("ͼ��֤�ţ�%d ������%s �������ڣ�%d��.%d��.%d�� ������%d��\n", pnew->lib_num, pnew->name, pnew->year, pnew->month, pnew->day, num - backtime);
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

		//������ʽ
		if (c)
		{
			printf("���ҵ�%d�����ڽ��ļ�¼��\n", c);
		}
		else
		{
			printf("δ�ҵ��κ����ڽ��ļ�¼��\n");
		}
	}
	else if (n == 4)
	{
		num = 0;

		//�ӽ��Ĺ����ļ���ȡ��Ϣ����������
		FILE* fp2;
		if ((fp2 = fopen("borrowbook.txt", "r")) == NULL)
		{
			printf("���Ĺ����ļ���ʧ�ܡ�\n");
			return;
		}
		struct borrowlist* pnew, * pend, * phead = NULL;
		pend = pnew = (struct borrowlist*)malloc(sizeof(struct borrowlist));
		fscanf(fp2, "%d\n%[^\n]%*c%d%d%d", &pnew->lib_num, &pnew->name, &pnew->year, &pnew->month, &pnew->day);
		while (!feof(fp2))
		{
			if (pnew->name != '\0')
			{
				printf("ͼ��֤�ţ�%d ������%s �������ڣ�%d��.%d��.%d��\n", pnew->lib_num, pnew->name, pnew->year, pnew->month, pnew->day);  //����������н������
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

		//������ʽ
		if (num)
		{
			printf("���ҵ�%d�����ļ�¼��\n\n", num);
		}
		else
		{
			printf("δ�ҵ��κν��ļ�¼��\n\n");
		}
	}


}

void booksearch(int)
{
	//�������ñ���
	int book_num;
	char name[40];
	char ISBN[20];
	char writter[20];
	char type[20];

	//����
	int n = 0;
	while (1)
	{
		printf("\n\t\t       �鼮��ѯ       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)��Ų�ѯ\n");
		printf("\t\t2)������ѯ\n");
		printf("\t\t3)ISBN��ѯ\n");
		printf("\t\t4)���߲�ѯ\n");
		printf("\t\t5)���Ͳ�ѯ\n");
		printf("\t\t6)�˻ز�ѯ������\n");
		printf("\t\t======================\n");
		printf("\t\t������ţ�");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("��������ţ�");
			scanf("%d", &book_num);
			while (book_num <= 0)
			{
				printf("�������������������룺");
				scanf("%d", &book_num);
			}
			break;
		}
		else if (n == 2)
		{
			printf("������������");
			scanf("\n%[^\n]", name);
			break;
		}
		else if (n == 3)
		{
			printf("������ISBN��");
			scanf("%s", &ISBN);
			break;
		}
		else if (n == 4)
		{
			printf("�������������֣�");
			scanf("\n%[^\n]", writter);
			break;
		}
		else if (n == 5)
		{
			printf("���������ͣ�");
			scanf("\n%[^\n]", type);
			break;
		}
		else if (n == 6)
		{
			printf("���˻ء�\n");
			return;
		}
		else
		{
			printf("�����������������:");
			scanf("%d", &n);
		}
	}

	//����ͼ������ļ�����������
	FILE* fp;
	int found = 0;
	int num = 0;
	if (n == 4)     //��ѯ����ʱ�������ʽ
	{
		printf("\n����Ҫ��ѯ����Ϊ�� %s  ��ѯ������£�\n", writter);
	}
	else if (n == 5)   //��ѯ����ʱ�������ʽ
	{
		printf("\n����Ҫ��ѯ����Ϊ�� %s ��ѯ������£�\n", type);
	}
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		printf("ͼ������ļ���ʧ�ܡ�");
		return;
	}
	struct check* pnew, * pend, * phead = NULL;
	pend = pnew = (struct check*)malloc(sizeof(struct check));
	fscanf(fp, "%d\n%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%[^\n]%*c%lf%d%d%d%d%d", &pnew->book_num, &pnew->book_name, &pnew->ISBN, &pnew->book_writter, &pnew->type, &pnew->book_intro, &pnew->book_publisher, &pnew->price, &pnew->book_year, &pnew->book_month, &pnew->book_day, &pnew->exist_now, &pnew->exist_all);
	while (!feof(fp))
	{
		if (n == 1 && book_num == pnew->book_num)
		{
			printf("��ѯ�ɹ���ͼ����Ϣ���£�\n");
			printf("\n��ţ�%05d\n������%s\nISBN��%s\n���ߣ�%s\n���ͣ�%s\n��飺%s\n�����磺%s\n�۸�%.2f\n�������ڣ�%d.%02d.%02d\n�ֿ������%d\n�ܿ������%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;  //��ʾ���ҵ�����ͬ
		}
		else if (n == 2 && strcmp(name, pnew->book_name) == 0)
		{
			printf("��ѯ�ɹ���ͼ����Ϣ���£�\n");
			printf("\n��ţ�%05d\n������%s\nISBN��%s\n���ߣ�%s\n���ͣ�%s\n��飺%s\n�����磺%s\n�۸�%.2f\n�������ڣ�%d.%02d.%02d\n�ֿ������%d\n�ܿ������%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
		}
		else if (n == 3 && strcmp(ISBN, pnew->ISBN) == 0)
		{
			printf("��ѯ�ɹ���ͼ����Ϣ���£�\n");
			printf("\n��ţ�%05d\n������%s\nISBN��%s\n���ߣ�%s\n���ͣ�%s\n��飺%s\n�����磺%s\n�۸�%.2f\n�������ڣ�%d.%02d.%02d\n�ֿ������%d\n�ܿ������%d\n\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_writter, pnew->type, pnew->book_intro, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
		}
		else if (n == 4 && strcmp(writter, pnew->book_writter) == 0)
		{
			printf("��ţ�%05d  ������%s  ISBN��%s  �����磺%s  �۸�%.2f  �������ڣ�%d.%02d.%02d  �ֿ������%d  �ܿ������%d\n", pnew->book_num, pnew->book_name, pnew->ISBN, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);			
			found = 1;
			num++;   //��ʾͬһ���������鼮����
		}
		else if (n == 5 && strcmp(type, pnew->type) == 0)
		{
			printf("��ţ�%05d  ������%s  ���ߣ�%s  ISBN��%s  �����磺%s  �۸�%.2f  �������ڣ�%d.%02d.%02d  �ֿ������%d  �ܿ������%d\n", pnew->book_num, pnew->book_name, pnew->book_writter, pnew->ISBN, pnew->book_publisher, pnew->price, pnew->book_year, pnew->book_month, pnew->book_day, pnew->exist_now, pnew->exist_all);
			found = 1;
			num++;  //��ʾͬһ�����鼮����
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

	//��δ�ҵ�ָ������ʱ
	if (found == 0)
	{
		if (n == 1)
		{
			printf("δ�ҵ�ָ����ţ�\n");
		}
		else if (n == 2)
		{
			printf("δ�ҵ����鼮��\n");
		}
		else if (n == 3)
		{
			printf("δ�ҵ�������ISBN��ص��鼮��\n");
		}
		else if (n == 4)
		{
			printf("δ�ҵ������������鼮��\n");
		}
		else if (n == 5)
		{
			printf("δ�ҵ���������鼮��\n");
		}
	}

	//��ѯ���߻�����ʱ��β���������ʽ�����ҵ���
	if (n == 4 && found == 1)
	{
		printf("��ѯ���������ҵ������������鼮%d����\n", num);
	}
	else if (n == 5 && found == 1)
	{
		printf("��ѯ���������ҵ�%d���������鼮��\n", num);
	}

	int n1 = 0;
	printf("\n\t\t       ������ʾ       ");
	printf("\n\t\t----------------------\n");
	printf("\t\t1)���ؽ��Ĳ�ѯϵͳ\n");
	printf("\t\t2)�����鼮��ѯϵͳ\n");
	printf("\t\t3)���ز�ѯϵͳ\n");
	printf("\t\t4)�������˵�\n");
	printf("\t\t----------------------\n");
	printf("\t\t������ţ�");
	scanf("%d", &n1);
	while (n1 <= 0 || n1 > 4)
	{
		printf("�����������������:");
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
		printf("�������\n");
	}
}

void search(int)
{
	int n = 0;
	while (1)
	{
		printf("\n\t\t       ��ѯϵͳ       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)�鼮��ѯ\n");
		printf("\t\t2)���Ĳ�ѯ\n");
		printf("\t\t3)�˻�������\n");
		printf("\t\t======================\n");
		printf("\t\t������ţ�");
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
			printf("\n���˻ء�");
			menu(n);
		default:
			printf("�������\n");
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
		printf("ͼ������ļ���ʧ�ܡ�\n");
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
		printf("ͼ������ļ�д��ʧ��!\n");
		return;
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%05d\n%s\n%s\n%s\n%s\n%s\n%s\n%.2f\n%d %02d %02d\n%d %d\n\n", classify2[i].book_num, classify2[i].book_name, classify2[i].ISBN, classify2[i].book_writter, classify2[i].type, classify2[i].book_intro, classify2[i].book_publisher, classify2[i].price, classify2[i].book_year, classify2[i].book_month, classify2[i].book_day, classify2[i].exist_now, classify2[i].exist_all);
	}
	fclose(fp);
	printf("��������ϡ�ͼ������ %d�����ܿ�� %d�����ֿ��Ϊ %d�����ѽ���鼮Ϊ %d����\n", booknum++, allincluded, nowincluded, allincluded - nowincluded);
}

void menu(int)
{
	int n = 0;
	while (n != 7)
	{
		printf("\n\t\t     ͼ�����ϵͳ       ");
		printf("\n\t\t======================\n");
		printf("\t\t1)�ɱ����\n");
		printf("\t\t2)������\n");
		printf("\t\t3)����\n");
		printf("\t\t4)�黹\n");
		printf("\t\t5)��ѯͼ����Ϣ\n");
		printf("\t\t6)ͳ�Ʋ�����ͼ����Ϣ\n");
		printf("\t\t7)�˳�\n");
		printf("\t\t======================\n");
		printf("\t\t������ţ�");
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
			printf("\n�ѹرա�");
			exit(0);
		default:
			printf("�������\n");
			break;
		}

	}
}

int main()
{
	menu(0);
	return 0;
}