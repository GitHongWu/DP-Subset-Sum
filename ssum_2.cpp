#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

static long total_nodes, total_subset, count = 0, cardinality = 51;
static bool runOnce = true;

struct elementStruct{
    int vote;
    std::string state;
    int index;
};

int partition(std::vector<elementStruct> &v, int low, int high){
    int pivot = v.at(high).vote; // pivot
    int i = low - 1;  // Index of smaller element
    elementStruct temp;

    for (int j = low; j <= high- 1; j++){
        // If current element is smaller than the pivot 
		if (v[j].vote > pivot) 
		{ 
			i++; // increment index of smaller element
            //swap v[i] and v[j]
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
		} 
	}
    //swap v[i+1] and v[high]
    temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;
    return (i + 1); 
}

void quickSort(std::vector<elementStruct> &v, int low, int high){
    if(low < high){
        /* pi is partitioning index, arr[p] is now 
		at right place */
        int pivotIndex = partition(v, low, high);
        // Separately sort elements before 
		// partition and after partition 
		quickSort(v, low, pivotIndex - 1);
		quickSort(v, pivotIndex + 1, high);
    }
}

//print vector of struct
void printVectorStruct(std::vector<elementStruct> v){
    for(auto a : v){
        std::cout << " " << a.state << " (id:" << a.index << "; val:" << a.vote << ")," << std::endl;
        //printf("%d, %s", a.vote, a.state);
    }
}

// prints subset found
void printSubset(int A[], int T[], int size, std::string B[])
{
	int i;
    std::vector<elementStruct> v;
    elementStruct temp;
    for (int j = 0; j < size; j++){
        temp.vote = T[j];
        temp.index = A[j];
        temp.state = B[j];
        v.push_back(temp);
    }

    if(v.size() > 1){
        std::sort(v.begin(), v.end(),
        [](const elementStruct& c1, const elementStruct& c2)
        {
        if (c1.state < c2.state)
            return true;
        // else if (c1.state < c2.state)
        //     return false;
        else
            return false;
        });
    }

    printf("lex-first min-sized solution: \n\n%c\n", '{');
	// for( i = 0; i < size; i++)
	// {
	// 	//print index and value of the array , the index is from the array before sorting
    //     std::cout << "index: " << A[i] << ", value: " << T[i] << ", string: " << B[i] << "| ";
    //     //printf("%d  %d  %s, ", A[i], T[i], B[i]);
	// }
    printVectorStruct(v);
    printf("%c",'}');
	printf("\n\n");
}

// inputs
// s		 - set vector
// t		 - tuplet vector
// s_size	 - set size
// t_size	 - tuplet size so far
// sum		 - sum so far
// ite		 - nodes count
// target_sum - sum to be found
// t_string  - tuplet string
// runOnce   - print the samllest subset
int  subset_sum(std::vector<elementStruct> v, int t[],int index[],int t_index[],
				int s_size, int t_size,int level,
				int sum, int ite,
				int const target_sum,int tag, std::string t_string[])
{
	total_nodes++;
	if( target_sum < sum )
	{
	//	printf("sum1 sum2 %d %d\n",sum,sum-s[ite-1] );
		
	//	result[0]=sum;
	//	result[1]=ite;
		return sum-v[ite-1].vote ;
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

        if(runOnce == true){
		    printSubset(t_index, t, t_size, t_string);
            runOnce = false;
        }

		return sum-v[ite-1].vote;
		
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
			
				t[t_size] = v[i].vote;
				t_index[t_size]=index[i];
                t_string[t_size] = v[i].state;

                sum = subset_sum(v, t, index, t_index, s_size, t_size + 1, level + 1, sum + v[i].vote, i + 1, target_sum, tag, t_string);
                if (i + 1 == s_size) //checking whether the breadth at the level is finishe,
                // in that case return sum upto the last level
                {
                    if (t_size == 0)
                        return 0;
                    else
                    {
                        sum = 0;
                        for (j = 0; j < t_size - 1; j++)
                        {
                            sum += t[j];
                        }

                        return sum;
                    }
				}
				
			}
		
	}
}

void generateSubsets(std::vector<elementStruct> &v, int target_sum)
{

    int size = v.size();

    int *tuplet_vector = (int *)malloc(size * sizeof(int));
	int *tuplet_index = (int *)malloc(size * sizeof(int));
    std::string tuplet_string[51];
    for (int s = 0; s < 51; s++)
    {
        tuplet_string[s] = "none";
    }
    int *index = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++ )
	{
		index[i]=i;
		tuplet_index[i]=-1;
		
	}

    // sort the array
    quickSort(v, 0, size - 1);

    int total = 0, check = 0, tag = 0;
    for(int i = 0; i < size; i++){
		total += v[i].vote;
	}

    for(int i = 0; i < size; i++){	
		check += v[size-i-1].vote;
		if(check >= target_sum){
			tag=i+1;
			break;
		}
	}

    if( v[0].vote <= target_sum || total >= target_sum )
	{
        subset_sum(v, tuplet_vector, index, tuplet_index, size, 0, 0, 0, 0, target_sum, tag, tuplet_string);
	}
    free(tuplet_vector);
	free(tuplet_index);
}

int main(){

    std::string filename;
    std::cout << "Filename > ";
    std::cin >> filename;
    std::vector<elementStruct> vectorStruct;
    std::ifstream file(filename);

    while(!file.good()){
        std::cout << "**Error: unable to open input file '" << filename << "'." << std::endl;
        std::cin >> filename;
    }

    int target;
    std::cout << "Target > ";
    std::cin >> target;

    int vote;
    std::string state, line, temp;

    //read input file
    for (int i = 0; getline(file, line); i++){
        std::stringstream ss(line);
        getline(ss, temp, ' ');
        vote = stoi(temp);
        getline(ss, temp);
        state = temp;
        elementStruct tempStruct;
        tempStruct.vote = vote;
        tempStruct.state = state;
        tempStruct.index = i;
        vectorStruct.push_back(tempStruct);
    }

    //debug
    //printVectorStruct(vectorStruct);

    generateSubsets(vectorStruct, target);

    //debug
    //std::cout << "after sort: " << std::endl;
    //printVectorStruct(vectorStruct);

    printf("Total Subset %ld\n", total_subset);
	printf("Minimum_Cardinality of Subset %ld\n", cardinality);
	printf("Total Number of Minimum_Cardinality Subset %ld\n", count);
	printf("Nodes generated %ld\n", total_nodes);
}