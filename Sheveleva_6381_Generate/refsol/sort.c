/*
 * Функции быстрой сортировки в одну (слов) и другую (индексов) сторону.
 * Входные данные: массив структур типа (Index *), номера первой и последней структуры типа (int), которые нужно сортировать.
 * Выходные данные: нет.
 */

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void Swap(Index *a, Index *b)
{
	Index c;
	c = *a;
	*a = *b;
	*b = c;
}

void QuickSortForLength(Index *arr, int first, int last)
{ 
		int cnt, i, j;
        if (last > first)
        { 
			 i = first;
             j = last;
             cnt = arr[i].length;
             while (i < j)
             {  
				 if (arr[i+1].length >= cnt)
                 {  
					Swap (& arr[i], & arr[i+1]);
                    i++;
                 }
                else
                {  if (arr[j].length >= cnt)
                   {  
                      Swap (& arr[j], & arr[i+1]);
                   }
                   j--;
                }
             }
             QuickSortForLength (arr, first, i-1);
             QuickSortForLength (arr, i+1, last);
        }
}

void QuickSortForOffset (Index *arr, int first, int last)
{ 
		int cnt, i, j;
        if (last > first)
        { 
			i = first;
            j = last;
            cnt = arr[i].offset;
            while (i < j)
            {  
				if (arr[i+1].offset <= cnt)
                {  
                   Swap (& arr[i], & arr[i+1]);
                   i++;
                }
                else
                {  
					if (arr[j].offset <= cnt)
                    {  
                       Swap (& arr[j], & arr[i+1]);
                    }
                    j--;
                }
             }
             QuickSortForOffset (arr, first, i-1);
             QuickSortForOffset (arr, i+1, last);
         }
}
