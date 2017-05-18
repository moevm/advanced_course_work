#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MatrixList
{
	int** matrix;   					// матрица
	int size;							// размер
	int state; 							// корректна или нет
	struct MatrixList* next; 		// указатель на следующую
	int number;							// номер матрицы
} MatrixList;

void MakeList(MatrixList** list);
int** ReadMatrix(char* buf, int* sizarr);
int* ReadLine(int n);

double** MakeCopy(int **arr,int n);
double MethodGauss(int n, int** matrix,int index);
void StringSubtractor(double** matrix, int a,int b,int number,int n,double* determinand);
void ZeroUpperElements(double** arr, int number,int n);
void LineSwapDoub(double** arr, int a, int b);

void MatrixSort(int **arr,int n);
void LineSwapInt(int** arr, int a, int b);
int LineCmp(int* a, int* b, int n);
void quickSort(int** arr,int l, int r,int n);

void SaveResult(MatrixList** list);
int Check();

int main()
{
	MatrixList* list = (MatrixList*)malloc(sizeof(MatrixList));
	MatrixList* head = list;				// запоминаем голову списка
	MakeList(&list);	// создаём список для файла
	list =head;
	int total_state = 1;
	while(list->next)
	{
		if (!list->state)
			total_state =0;
		list=list->next;
	}
	list =head;
	if(total_state)
	{
		int operation_number;
		scanf("%d",&operation_number);
		while (operation_number)
		{
			switch (operation_number)
			{
				case 1: 
				while (list->next)
				{
					MatrixSort(list->matrix,list->size);
					list=list->next;
				}
				list =head;
				break;  
				case 3: 
				while(list->next)
				{

					printf("%d %-10.0lf\n",list->number,MethodGauss(list->size,list->matrix,operation_number));
					list=list->next;
				}
				list = head;
				break;
				case 2:
				while(list->next)
				{

					 printf("%d %-10.0lf\n",list->number,MethodGauss(list->size,list->matrix,operation_number));
					 list=list->next;
				}
				list = head;
				break;
				default : 
				operation_number=0;
				SaveResult(&list);
			}
			if(operation_number)
		scanf("%d",&operation_number);
		}
	}	
	else
	{
		while(list->next)
		{
			if(!list->state)
				printf("Fail with %d\n",list->number);
			list=list->next;
		}
		return -1;
	}
	list = head;
	while (list->next)
	{
		MatrixList* ptr = list;
		list=list->next;
		free(ptr);
	}
	return 0;

}

double MethodGauss(int n, int** matrix, int index)
{
	double** arr = MakeCopy(matrix, n);
	int i,j;		
	double determinand=1;
	for(i=0;i<n;++i)
	{
		for(j=0;j<i;++j)
		{
			StringSubtractor(arr,j,i,j,n,&determinand);				
		}
	}

	// На этом шаге имеем матрицу треугольного вида
	if (index == 3)
		{
			for(i=0;i<n;++i)
			{
				determinand*=arr[i][i];
			}
			return determinand;
		}
	else
		{
			double rg = (double)n;
			for(i=n-1;i>=0;--i)
			{	
				int not_zero_element = 0;
				for(j=n-1;j>=i;--j)
				{
					if (arr[i][j]!=0.0)
					{
						ZeroUpperElements(arr, j, i);
						not_zero_element = arr[i][j];
					}
					else
					{
						arr[i][j] = not_zero_element;
					}
				}

				if (arr[i][i] == 0) 
					--rg;
			}
			return rg;
		}
}

void StringSubtractor(double** matrix, int a,int b,int number,int n,double* determinand)
{
	if ((matrix[a][number])&&(matrix[b][number]))
	{	
		double stack1 = matrix[a][number];
		double stack2 = matrix[b][number];
		for(int i=0;i<n;++i)
		{
			matrix[a][i]*=stack2;							// алгоритм обнуления элемента 
			matrix[b][i]*=stack1;							// под номером number
			matrix[b][i]-=matrix[a][i];
			matrix[a][i]/=stack2;
			matrix[b][i]/=stack1;
		}
	}
	else if (matrix[b][number]!=0)
	{
		LineSwapDoub(matrix,a,b);
		*determinand*=-1;
	}
}
// магия
void ZeroUpperElements(double** arr, int number,int n)
{
	for(int i = 0;i<n;++i)
	{
		arr[i][number] = 0.0;
	} 

}
// создание копии матрицы для работы с методом Гаусса
double** MakeCopy(int **arr,int n)
{
	double** matrix_copy =(double**)malloc(sizeof(double*)*n);
		for(int i =0; i<n;++i)
		{
			matrix_copy[i] = (double*)malloc(sizeof(double)*n);
			for(int j =0;j<n;++j)
			{
				matrix_copy[i][j]=arr[i][j];
			}
		}
	return matrix_copy;
}

//сортировка строк методом пузырька

void MatrixSort(int **arr,int n)
{
	quickSort(arr,0,n-1,n);
}

// чтение матрицы и проверка на корректнность 

int** ReadMatrix(char* buf, int* sizarr)
{
	int arr[100];
	int** matrix;
	int i =0;
	char c, check;
	char* bufcheck;
	bufcheck = strtok(buf," \n");		// чтение из ранее прочитанного буфера
	while(bufcheck)
	{
		sscanf(bufcheck,"%d",&arr[i]);
		++i;
		bufcheck = strtok(NULL," \n");
	}
	*sizarr = i;
	matrix = (int**)malloc(sizeof(int*)*i);
	matrix[0] = (int*)malloc(sizeof(int)*i);
	for (int j=0;j<i;++j)
		matrix[0][j] = arr[j];        			// копируем 1-ую строку
	for(int j =1;j<i;++j)
	{
		int* line = ReadLine(i);
		if (line!=NULL)
		{
			matrix[j] = (int*)malloc(sizeof(int)*i);
			matrix[j] = line;
		}
		else 
		{	
			return NULL;					// тут удалил scanf 
		}
	}
		return matrix;
}

// чтение строки матрицы

int* ReadLine(int n)
{
	int* result = (int*)malloc(sizeof(int)*n);
	char* c;
	char s[200];
	int i =0;
	fgets(s,199,stdin);
	if (s[0]!='\n')
	{
	c = strtok(s," \n");
	for(i;i<n;++i)
	{	
		sscanf(c,"%d ",&result[i]);			// Чтобы данные не затирались
		c = strtok(NULL," \n");
	}
	return result;
	}
	else return NULL;
}

void LineSwapInt(int** arr, int a, int b)
{
	int* c;
	c = arr[a];		
	arr[a] = arr[b];
	arr[b] = c;
}
void quickSort(int** arr,int l, int r,int n)
{
    int* x = arr[l + (r - l) / 2];
    int i = l;
    int j = r;
    while(i <= j)
    {
        while(LineCmp(arr[i],x,n) < 0) i++;
        while(LineCmp(arr[j],x,n) > 0) j--;
        if(i <= j)
        {
            LineSwapInt(arr,i,j);
            i++;
            j--;
        }
    }
    if (i<r)
                quickSort(arr,i, r,n);
   
    if (l<j)   
        quickSort(arr,l, j,n);    
}
int LineCmp(int* a, int* b, int n)
{
	for(int i=0;i<n;++i)
	{
		if (a[i]!=b[i])
			return a[i]-b[i];
	}
	return 0;
}
void LineSwapDoub(double** arr, int a, int b)
{
	double* c;
	c = arr[a];		
	arr[a] = arr[b];
	arr[b] = c;

}
void MakeList(MatrixList** list)
{
	int right =1;
	while(right)
	{	
		// проверка на конец файла
		char buf[200];
		fgets(buf,199,stdin);
		if ((buf[0]!=EOF)&&(buf[0]!='\n'))
		{
			(*list)->matrix = ReadMatrix(buf,&((*list)->size));
			if ((*list)->matrix)
			{
				int k =Check();
				if(k==1)					// осталось 1 \n 
				(*list)->state = 1;
				else if (k == -1)
					right =0;
				else
				(*list)->state = 0;
				fgets(buf,19,stdin);     // дочитываем \n
			}
			else
			{									// осталось 1 \n
				(*list)->state = 0;
				fgets(buf,199,stdin);
			}
			(*list)->next = (MatrixList*)malloc(sizeof(MatrixList));
			(*list)->number = right;
			*list = (*list)->next;
			++right;
		}
		else right =0;
	}
}
void SaveResult(MatrixList** list)
{
	FILE* fo = fopen("MasterAfterSort.txt","wt");
	while((*list)->next)
	{
		for(int i=0;i<(*list)->size;++i)
		{
			for(int j=0;j<(*list)->size;++j)
				fprintf(fo,"%d ",(*list)->matrix[i][j]);
			fprintf(fo,"\n");
		}
		fprintf(fo,"\n");
		fprintf(fo,"\n");
		*list = (*list)->next;
	}
	fclose(fo);
}
int Check()
{
	char buf[200];
	fgets(buf,199,stdin);
	if (buf[0] =='\n')
		return 1;
	else
	{
		while(buf[0]!='\n')
			fgets(buf,199,stdin);
		return 0;
	}
}