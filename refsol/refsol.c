#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SORT_CMND 1
#define RANG_CMND 2
#define DETERMINAND_CMND 3
#define END_CMND 4
#define ZERO_DIGIT 0.0000000000001
typedef struct Matrix
{
	double** data;
	int size;
}Matrix;

typedef struct MatrixList
{		
	Matrix* matrix;			
	int state; 							// корректна или нет
	struct MatrixList* next; 		// указатель на следующую
	int number;							// номер матрицы
} MatrixList;

void MakeList(MatrixList** list);
double** ReadMatrix(char* buf, int* sizarr);
double* ReadLine(int n);

Matrix* MakeCopy(Matrix* matrix);
long double MethodGauss(Matrix* matrix,int index);
void StringSubtractor(Matrix* matrix,int i,int j,long double* determinand);
void ZeroUpperElements(double** arr, int number,int n);
void LineSwapDoub(double** arr, int a, int b);

void MatrixSort(Matrix* matrix);
double LineCmp(double* a, double* b, int n);
void quickSort(double** arr,int l, int r,int n);

void SaveResult(MatrixList** list);
int Check();

int main()
{
	MatrixList* list = (MatrixList*)malloc(sizeof(MatrixList));
	list->matrix = (Matrix*)malloc(sizeof(Matrix));
	MatrixList* head = list;				// запоминаем голову списка
	MakeList(&list);	// создаём список для файла
	list =head;
	int total_state = 1;
	list=head;
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
				case SORT_CMND: 
				while(list->next)
				{
					MatrixSort(list->matrix);
					list=list->next;
				}
				list = head;
				break;  
				case DETERMINAND_CMND: 
				while(list->next)
				{
					printf("%d %6.2Lf\n",list->number,MethodGauss(list->matrix,operation_number));	// делает интом
					list=list->next;
				}
				list = head;
				break;
				case RANG_CMND:
				while(list->next)
				{

					 printf("%d %6.0Lf\n",list->number,MethodGauss(list->matrix,operation_number));
					 list=list->next;
				}
				list = head;
				break;
				case END_CMND : 
				operation_number=0;
				SaveResult(&list);
				break;
				default: printf("Неизвестная команда\n");
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
	while (list)
	{
		MatrixList* ptr = list;
		Matrix* pmatrix =list->matrix;
		double** pdata = list->matrix->data;
		for(int i =0;i<list->matrix->size;++i)
			free(list->matrix->data[i]);
		list=list->next;
		free(ptr);
		free(pmatrix);
		free(pdata);
	}
	return 0;

}

long double MethodGauss(Matrix* matrix, int index)
{
	Matrix* matrix_copy = MakeCopy(matrix);
	int i,j;		
	long double determinand=1.0;
	if(matrix_copy->data)
	for(i=0;i<matrix->size;++i)
	{
		for(j=0;j<i;++j)
		{
			StringSubtractor(matrix_copy,i,j,&determinand);		
		}
	}	

	// На этом шаге имеем матрицу треугольного вида
	if (index == DETERMINAND_CMND)
		{
			for(i=0;i<matrix->size;++i)
			{
				determinand*=matrix_copy->data[i][i];
			}
			return determinand;
		}
	else
		{
		long	double rg = (double)(matrix_copy->size);
			for(i=matrix->size-1;i>=0;--i)
			{	
				double not_zero_element = 0.0;
				for(j=matrix->size-1;j>=i;--j)
				{
					if (matrix_copy->data[i][j]!=0.0)
					{
						ZeroUpperElements(matrix_copy->data, j, i);
						not_zero_element = matrix_copy->data[i][j];
					}
					else
					{
						matrix_copy->data[i][j] = not_zero_element;
					}
				}

				if (fabs(matrix_copy->data[i][i])<=ZERO_DIGIT) 
					--rg;
			}
			return rg;
		}
}

void StringSubtractor(Matrix* matrix,int i,int j,long double* determinand)
{
	if ((matrix->data[j][j])&&(matrix->data[i][j]))
	{	
		double stack1 = matrix->data[j][j];			// элемент, которым занулим следующий
		double stack2 = matrix->data[i][j];			// элемент, который будет занулён
		for(int k=0;k<matrix->size;++k)
		{
			matrix->data[j][k]*=stack2;							
			matrix->data[i][k]*=stack1;						
			matrix->data[i][k]-=matrix->data[j][k];
			matrix->data[j][k]/=stack2;
			matrix->data[i][k]/=stack1;
		}
	}
	else if (matrix->data[i][j]!=0)
	{
		LineSwapDoub(matrix->data,i,j);
		*determinand*=-1;
	}
}
// магия
void ZeroUpperElements(double** arr, int number,int n)
{
	for(int i = 0;i<n;++i)
	{
		arr[i][number] = ZERO_DIGIT;
	} 

}
// создание копии матрицы для работы с методом Гаусса
Matrix* MakeCopy(Matrix* matrix)
{
	Matrix* return_matrix = (Matrix*)malloc(sizeof(Matrix));
	return_matrix->size = matrix->size;
	return_matrix->data =(double**)malloc(sizeof(double*)*return_matrix->size);
		for(int i =0; i<return_matrix->size;++i)
		{
			return_matrix->data[i] = (double*)malloc(sizeof(double)*return_matrix->size);
			memcpy(return_matrix->data[i],matrix->data[i],sizeof(double)*matrix->size);
		}
	return return_matrix;
}


void MatrixSort(Matrix* matrix)
{
	quickSort(matrix->data,0,matrix->size-1,matrix->size);
}

// чтение матрицы и проверка на корректнность 

double** ReadMatrix(char* buf, int* sizarr)
{
	double arr[BUFSIZ];
	double** matrix;
	int i =0;
	char c, check;
	char* bufcheck;
	bufcheck = strtok(buf," \n");		// чтение из ранее прочитанного буфера
	while(bufcheck)
	{
		sscanf(bufcheck,"%lf",&arr[i]);
		++i;
		bufcheck = strtok(NULL," \n");
	}
	*sizarr = i;
	matrix = (double**)malloc(sizeof(double*)*i);
	matrix[0] = (double*)malloc(sizeof(double)*i);
	for (int j=0;j<i;++j)
		matrix[0][j] = arr[j];        			// копируем 1-ую строку
	for(int j =1;j<i;++j)
	{
		double* line = ReadLine(i);
		if (line!=NULL)
		{
			matrix[j] = (double*)malloc(sizeof(double)*i);
			matrix[j] = line;
		}
		else 
		{	
			return NULL;					// тут удалил scanf 
		}
	}
		return matrix;
}

double* ReadLine(int n)
{
	double* result = (double*)malloc(sizeof(double)*n);
	char* c;
	char s[BUFSIZ];
	int i =0;
	fgets(s,BUFSIZ-1,stdin);
	if (s[0]!='\n')
	{
	c = strtok(s," \n");
	for(i;i<n;++i)
	{	
		sscanf(c,"%lf ",&result[i]);			// Чтобы данные не затирались
		c = strtok(NULL," \n");
	}
	return result;
	}
	else return NULL;
}
void quickSort(double** arr,int l, int r,int n)
{
    double* x = arr[l + (r - l) / 2];
    int i = l;
    int j = r;
    while(i <= j)
    {
        while(LineCmp(arr[i],x,n) < 0) i++;
        while(LineCmp(arr[j],x,n) > 0) j--;
        if(i <= j)
        {
            LineSwapDoub(arr,i,j);
            i++;
            j--;
        }
    }
    if (i<r)
                quickSort(arr,i, r,n);
   
    if (l<j)   
        quickSort(arr,l, j,n);    
}
double LineCmp(double* a, double* b, int n)
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
		char buf[BUFSIZ];
		fgets(buf,BUFSIZ-1,stdin);
		if ((buf[0]!=EOF)&&(buf[0]!='\n'))
		{
			(*list)->matrix->data = ReadMatrix(buf,&((*list)->matrix->size));
			if ((*list)->matrix->data)
			{
				int k =Check();
				if(k==1)					// осталось 1 \n 
				(*list)->state = 1;
				else if (k == -1)
					right =0;
				else
				(*list)->state = 0;
				fgets(buf,BUFSIZ-1,stdin);     // дочитываем \n
			}
			else
			{									// осталось 1 \n
				(*list)->state = 0;
				fgets(buf,BUFSIZ-1,stdin);
			}
			(*list)->next = (MatrixList*)malloc(sizeof(MatrixList));
			(*list)->number = right;
			(*list)->next->matrix =(Matrix*)malloc(sizeof(Matrix));
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
		for(int i=0;i<(*list)->matrix->size;++i)
		{
			for(int j=0;j<(*list)->matrix->size;++j)
				fprintf(fo,"%6.2lf ",(*list)->matrix->data[i][j]);
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
	char buf[BUFSIZ];
	fgets(buf,BUFSIZ-1,stdin);
	if (buf[0] =='\n')
		return 1;
	else
	{
		while(buf[0]!='\n')
			fgets(buf,BUFSIZ-1,stdin);
		return 0;
	}
}