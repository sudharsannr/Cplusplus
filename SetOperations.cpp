#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Implementation of set operations considering duplicate elements. Sort initially to obtain inputs that are in sync and then iterate through each element.
Duplicates have to be considered only for union operation otherwise the algorithm works fine for the remaining operations.
1. Union
   If both the elements are same and duplicates are allowed, then print both the elements and move to next element.
   If both the elements are same and duplicates are not allowed, then print either element.
   Print otherwise and move to next element.
   If one of the set exhausts, print the remaining elements. 
2. Intersection
	If both the elements are same, then print either the element and move to the next record of each set.
	If the elements are not same, then do not print and move to the next records.
	If either set exhausts, then stop the operation.
3. Difference
	Sorting pays off in this operation.
	If both the elements are same, move to next element.
	Print only if the element of the first set is lesser than that of the second element.
*/

vector<int> removeDuplicates(vector<int>);
void Union(vector<int>, vector<int>, bool);
void Intersection(vector<int>, vector<int>, bool);
void Difference(vector<int>, vector<int>, bool);
void printVector(vector<int>);

int main() {

	static const int arr[] = {5, 1, 7, 1, 5, 7, 1, 9, 9, 8, 6};
	static const int arr2[] = {6, 5, 8, 9, 10};
	vector<int> a1 (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	vector<int> b1 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
	int dupCh = 0, choice = 0;
	bool dup = false;
	vector<int> a, b;
	void (*runFn) ();
	void (*fnPtr[]) (vector<int>, vector<int>, bool) = {&Union, &Intersection, &Difference};
	
	while(1)
	{
		choice = 0;
		dupCh = 0;
		dup = false;
		a.clear();
		b.clear();
		cout << "Enter your choice: \n1. Union\n2. Intersection\n3. Difference\n4. Exit\n";
		cin >> choice;
		if(choice == 4)
			break;
		if(choice != 2)
		{
			cout << "Carry on \n1. With duplicates?\n2. Without duplicates?\n";
			cin >> dupCh;
		}
		
		if(dupCh == 1)
			dup = true;
		
		sort(a1.begin(), a1.end());
		sort(b1.begin(), b1.end());
		
		cout << "\n";
		if(!dup)
		{
			a = removeDuplicates(a1);
			b = removeDuplicates(b1);
		}
		else
		{
			a = a1;
			b = b1;
		}
		
		/*cout << "Array a contains " << endl;
		printVector(a);
		cout << "Array b contains " << endl;
		printVector(b);*/
		
		fnPtr[choice-1](a, b, dup);
		fnPtr[choice-1](b, a, dup);
	}
	return 0;
}

vector<int> removeDuplicates(vector<int> a1)
{
	int temp = NULL;
	vector<int> a;
	for(int i = 0; i < a1.size(); i++)
	{
		if(a1[i] != temp) {
			temp = a1[i];
			a.push_back(temp);
		}
	}
	return a;
}

//Union operator
void Union(vector<int> a, vector<int> b, bool dup)
{
	cout << "A U B is " << endl;
	for(int i = 0, j = 0; i < a.size() && j < b.size(); )
	{
		if(a[i] == b[j])
		{
			//Print additional element only if duplicate else print either
			cout << a[i] << "\t";
			if(dup)
				cout << b[j] << "\t";
			i++;
			j++;
		}
		else if(a[i] < b[j])
		{
			//Print the lesser element
			cout << a[i] << "\t";
			i++;
		}
		else if(a[i] > b[j])
		{
			//Print the lesser element
			cout << b[j] << "\t";
			j++;
		}
		//Print the remaining elements
		if(i == a.size())
		{
			while(j < b.size())
			{
				cout << b[j] << "\t";
				j++;
			}
		}
		if(j == b.size())
		{
			while(i < a.size())
			{
				cout << a[i] << "\t";
				i++;
			}
		}
	}
	cout << "\n";
}

//Intersection operator
void Intersection(vector<int> a, vector<int> b, bool dup)
{
	cout << "A ^ B is " << endl;
	//Note the condition 'or' instead of 'and'
	for(int i = 0, j = 0; i < a.size() || j < b.size(); )
	{
		//Print only if either of the elements are same else ignore
		if(a[i] == b[j])
		{
			cout << a[i] << "\t";
			i++;
			j++;
		}
		else if(a[i] < b[j])
			i++;
		else if(a[i] > b[j])
			j++;
	}
	cout << "\n";
}

//Difference operator
void Difference(vector<int> a, vector<int> b, bool dup)
{
	cout << "A-B is " << endl;
	for(int i = 0, j = 0; i < a.size() && j < b.size(); )
	{
		if(a[i] == b[j])
		{
			//Ignore printing the element
			i++;
			j++;
		}
		else if(a[i] < b[j])
		{
			//Print the element
			cout << a[i] << "\t";
			i++;
		}
		else if(a[i] > b[j])
			j++;
		//Handle count
		if(i == a.size())
			break;
		if(j == b.size())
		{
			while(i < a.size())
			{
				cout << a[i] << "\t";
				i++;
			}
		}
	}
	cout << "\n";
}

//Print vector routine - debug purposes only
void printVector(vector<int> a)
{
	for(unsigned int i =  0; i < a.size(); i++)
				cout << a[i] << "\t";
	cout << "\n";	
}