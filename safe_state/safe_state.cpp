#include <iostream>
#include<string>
using namespace std;


bool Check_safety(int n, int m, int allocation[][100], int need[][100], int work[], bool finish[], string arr[]) {

	//bool flag_safety = false;
	bool flag = false;
	int i = 0;
	int j, k;
	int index = 0;
	int count = 0;

	while (i < n) { //i=0

		if (finish[i] == false) {
			for (j = 0; j < m; j++) {
				if (need[i][j] <= work[j])
					flag = true;
				else {
					flag = false;
					i = (i + 1) % n; //go to the following process immediately
					count++;
					break;
				}
			}
		}
		else
		{
			i = (i + 1) % n;
			count++;
		}
		if (flag) {
			for (j = 0; j < m; j++) {
				work[j] = work[j] + allocation[i][j];
			}
			finish[i] = true;
			//cout<<"P"<<i<<endl;
			arr[index] = "P" + to_string(i);
			index++;
			count = 0;
			i = (i + 1) % n;
			flag = false;
		}

		if (count == n) {
			for (int i = 0; i < n; i++) {

				if (finish[i] == false) 
					return false;
				
			}
			return true;
		}
		

	}//while
}//function

bool Check_request(int n, int m, int available[], int allocation[][100], int request[], int need[][100], int request_p_no, int work[], string arr[])
{
	bool flag = false;
	bool finish[100] ;

	for (int i = 0; i < n; i++)
	{
		finish[i] = false;
	}
	bool X;
	for (int j = 0; j < m; j++) {
		if (request[j] <= need[request_p_no][j] && request[j] <= available[j])
			flag = true;
		else
			return false;
	}

	if (flag) {
		for (int j = 0; j < m; j++) {
			available[j] = available[j] - request[j];
			allocation[request_p_no][j] += request[j];
			need[request_p_no][j] -= request[j];

		}

		X = Check_safety(n, m, allocation, need, available, finish, arr);
		return X;
	}
		
	}

int main() {

	int n, m;
	int allocation[100][100];
	int max[100][100];
	int need[100][100];
	int available[100];
	int work[100];
	bool finish[100];
	string arr[100];
	int request[100];
	int Request_P_no;
	char enquiry1;
	char enquiry2;
	int NEW_PROCESS = 1;

	while (NEW_PROCESS) {
	
	cout << "Please enter number of processes: " << endl;
	cin >> n;
	cout << "Please enter number of resource types: " << endl;
	cin>> m;
	
	

	
		for (int i = 0; i < n; i++)
		{
			finish[i] = false;
		}

		//Allocation matrix entry
		cout << "Please enter the allocation matrix: " << endl;
		cout << " " << " ";
		for (int i = 0; i < m; i++)
		{
			cout << "R" << i;
		}
		cout << endl;

		for (int i = 0; i < n; i++) {
			cout << "P" << i << ":";
			for (int j = 0; j < m; j++)
			{
				cin >> allocation[i][j];

			}
		}

		//Max matrix entry
		cout << "Please enter the max matrix: " << endl;
		cout << " " << " ";
		for (int i = 0; i < m; i++)
		{
			cout << "R" << i;
		}
		cout << endl;

		for (int i = 0; i < n; i++) {
			cout << "P" << i << ":";
			for (int j = 0; j < m; j++)

			{
				cin >> max[i][j];

			}
		}

		//Available matrix
		cout << "Please enter the available matrix: " << endl;

		for (int i = 0; i < m; i++)
		{
			cout << "R" << i;
		}
		cout << endl;

		for (int i = 0; i < m; i++)
		{

			cin >> available[i];
			work[i] = available[i];
		}



		//calculation for need matrix

		cout << "The need matrix: " << endl;
		cout << " " << " ";
		for (int i = 0; i < m; i++)
		{
			cout << "R" << i;
		}
		cout << endl;

		for (int i = 0; i < n; i++) {
			cout << "P" << i << ":";
			for (int j = 0; j < m; j++)

			{
				need[i][j] = max[i][j] - allocation[i][j];
				cout << need[i][j] << " ";

			}
			cout << endl;
		}
		

		//Check Safe State
		cout << "If you want to check Safe State just Choose \"S\" else select \"0\":" << endl;
		cin >> enquiry1;
		if (enquiry1 == 'S') {
			bool X = Check_safety(n, m, allocation, need, work, finish, arr);
			if (X == true) {

				cout << "Yes, Safe state " << "<";
				for (int i = 0; i < n; i++)
				{
					if (i == n - 1)
						cout << arr[i];
					else
						cout << arr[i] << ",";
				}
				cout << ">";
				cout << endl;
			}

			else //if (X == false)
			{
				cout << "NO, Unsafe state" << endl;
			}

		}

		//Check immediate requests
		cout << "if you want to check the grant for an immediate request just Select \"G\" else Select \"0\" "<< endl;
		cin >> enquiry2;

		if (enquiry2 == 'G') {
			cout << "Enter its process number: " << endl;
			cin >> Request_P_no;
			cout << " " << " ";
			for (int i = 0; i < m; i++)
			{
				cout << "R" << i;
			}
			cout << endl;


			cout << "P" << Request_P_no << ":";
			for (int j = 0; j < m; j++)

			{
				cin >> request[j];

			}

			bool Y = Check_request(n, m, available, allocation, request, need, Request_P_no, work ,arr);

			if (Y)
			{
				cout << "Yes request can be granted with safe state, Safe state " << "<" << "P" << Request_P_no << "req,";
				for (int i = 0; i < n; i++)
				{
					if (i == n - 1)
						cout << arr[i];
					else
						cout << arr[i] << ",";
				}
				cout << ">";
				cout << endl;
			}
			else
				cout << "No, the request can not be granted" << endl;
		}

		cout <<" \"\" ENTER THE INFORMATION OF PROCESSES OF ANOTHER SYSTEM: \"\"" << endl;



	}

	return 0;
}




