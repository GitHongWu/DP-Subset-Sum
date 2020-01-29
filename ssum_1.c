#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE(a) (sizeof(a))/(sizeof(a[0]))

static long  total_nodes,total_subset,cardinality=51,count=0;

typedef struct subSumStruct{
	int votes;
	char *state;
} subSumStruct;

// prints subset found
void printSubset(int A[], int T[],int size)
{
	int i;
    printf("%c",'{');
	for( i = 0; i < size; i++)
	{
		//print index and value of the array , the index is from the array before sorting
		printf("%d  %d ,", A[i],T[i]);
//		printf("%d  ", T[i]);
	}
    printf("%c",'}');
	printf("\n");
}
/* C implementation QuickSort */
#include<stdio.h> 

// A utility function to swap two elements 
void swap(int* a, int* b,int* c, int* d) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
	int temp = *c; 
	*c = *d; 
	*d = temp; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
	array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[],int index[], int low, int high) 
{ 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 
	int j;

	for ( j = low; j <= high- 1; j++) 
	{ 
		// If current element is smaller than the pivot 
		if (arr[j] > pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j],&index[i],&index[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high],&index[i+1],&index[high]); 
	return (i + 1); 
} 

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int index[], int low, int high) 
{ 
	if (low < high) 
	{ 
		/* pi is partitioning index, arr[p] is now 
		at right place */
		int pi = partition(arr,index, low, high); 

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr,index, low, pi - 1); 
		quickSort(arr,index, pi + 1, high); 
	} 
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

// Driver program to test above functions 

//int range(level,t_size,t,s,size)
//{
//	int check=0,i,tag=size;
//	if(t_size==0)
//		check=0;
//	else
//	{
//		for(i=0;i<t_size;i++)
//			check+=t[t_size];
//	}
//		for(  i = 0; i < size; i++ )
//	{
//		
//		check+=s[size-i-1];
//		if(check>=target_sum)
//		{
//			tag=i+1;
//			break;
//		}
//	}
//	printf("tag %d\n",tag);
//	return tag;
//
//	
//}



// inputs
// s		 - set vector
// t		 - tuplet vector
// s_size	 - set size
// t_size	 - tuplet size so far
// sum		 - sum so far
// ite		 - nodes count
// target_sum - sum to be found
int  subset_sum(int s[], int t[],int index[],int t_index[],
				int s_size, int t_size,int level,
				int sum, int ite,
				int const target_sum,int tag)
{
	total_nodes++;
	if( target_sum < sum )
	{
	//	printf("sum1 sum2 %d %d\n",sum,sum-s[ite-1] );
		
	//	result[0]=sum;
	//	result[1]=ite;
		return sum-s[ite-1] ;
	//	return sum;
	}	

	else if( target_sum == sum )
	{
		// We found sum, recording cardinality of the array
		
		if(cardinality>=t_size)
		{
		
			cardinality=t_size;
			count++;
		
		}
			
		total_subset++;
		printSubset(t_index,t, t_size);

		return sum-s[ite-1];
		
	}
	else
	{
		// constraint check

			int i,j;
			// generate nodes along the breadth

			for(i = ite; i < s_size; i++ )
			{
				if(level==0 && i==tag)
					return 0;
			
				t[t_size] = s[i];
				t_index[t_size]=index[i];


					sum=subset_sum(s, t,index,t_index, s_size, t_size + 1,level+1, sum+s[i] , i + 1, target_sum,tag);
					if(i+1==s_size) //checking whether the breadth at the level is finishe,
					// in that case return sum upto the last level
					{
						if(t_size==0)
							return 0;
						else
						{
							sum=0;
							for(j=0;j<t_size-1;j++)
							{
									sum+=t[j];
							}
							
							return sum;
						}
					}
						
						
						
//					sum=value[0]-s[value[1]];
					//printf("back1 ite, t_size, sum, level, s %d %d %d %d %d  \n",ite,t_size,sum,level,s[i]);
//				}
				
			}
//		}
		
	}
}

// Wrapper that prints subsets that sum to target_sum
void generateSubsets(int s[], int size, int target_sum)
{
	int *tuplet_vector = (int *)malloc(size * sizeof(int));
	int *tuplet_index = (int *)malloc(size * sizeof(int));
	int *index = (int *)malloc(size * sizeof(int));
	int total = 0,check=0,tag=size;
	int i;
	
	for(  i = 0; i < size; i++ )
	{
		index[i]=i;
		tuplet_index[i]=-1;
		
	}

	// sort the array

	quickSort(s,index, 0,size-1);
	

	printf("%s\n","qsort");
	printArray(s,size);
	printf("%s\n","qsort index");
	printArray(index,size);


	for(  i = 0; i < size; i++ )
	{
		total += s[i];
	
	}
	
	for(  i = 0; i < size; i++ )
	{
		
		check+=s[size-i-1];
		if(check>=target_sum)
		{
			tag=i+1;
			break;
		}
	}
	printf("tag %d\n",tag);
	if( s[0] <= target_sum || total >= target_sum )
	{
		subset_sum(s, tuplet_vector,index,tuplet_index, size, 0, 0, 0,0, target_sum,tag);
	}

	free(tuplet_vector);
	free(tuplet_index);
	
}

int main()
{
	// FILE *fp;
    // char str[20];
	// char *fm;
	// char* filename = "toy.txt";
 
    // fp = fopen(filename, "r");
    // if (fp == NULL){
    //     printf("Could not open file %s",filename);
    //     return 1;
    // }

	// subSumStruct subSum_struct;
	// fscanf(fp, "%d %s", &subSum_struct.votes, &subSum_struct.state);

	// while (fgets(str, 20, fp) != NULL)
    //     printf("%s", str);
    // fclose(fp);




	int weights[] = {1, 1, 2, 3, 1, 4};
	
	int target = 5;

	int size = ARRAYSIZE(weights);
	
	

	generateSubsets(weights, size, target);
	printf("Total Subset %ld\n", total_subset);
	printf("Minimum_Cardinality of Subset %ld\n", cardinality);
	printf("Total Number of Minimum_Cardinality Subset %ld\n", count);
	printf("Nodes generated %ld\n", total_nodes);
	
	return 0;
}
