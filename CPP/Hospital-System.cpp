#include<iostream>
#include<string>
using namespace std;
string names[100]{};
int staties[100]{};
int specialization[100]{};
int freq[100] = { 0 };
int index = 0;
int sp;
int st;
string name;
int n;
void option()
{
	cout << "ENTER YOUR CHOICE\n"
		<< "1)Add new patient\n"
		<< "2)Print all patients\n"
		<< "3)Get next patients\n"
		<< "4)Exit\n";
}
void system()
{
	while (true)
	{
		option();
		cin >> n;
		if (n == 1)
		{
			cout << "ENTER SPECIALIZATION,NAME,STATIES\n";
			cin >> sp;
			if (!(sp >= 1 && sp <= 20))cout << "SORRY WE DONT HAVE THIS ONE\n";
			else if (freq[sp] > 5)
			{
				cout << "sorry we can't add more patients for this specialization/n";
			}
			else
			{
				specialization[index] += sp;
				cin >> names[index] >> staties[index];
				if (index > 0 && staties[index] == 1 && staties[index - 1] == 0)
				{
					for (int i = 0; i < index; i++)
					{
						if (staties[i] == 0)
						{
							swap(staties[index], staties[i]);
							swap(names[index], names[i]);
							swap(specialization[index], specialization[i]);
							break;
						}
					}
				}
				freq[sp]++;
				index++;
			}
		}
		else if (n == 2)
		{
			for (int j = 1; j <= 20; j++)
				if (freq[j])
				{
					cout << "we have " << freq[j] << " in specialization " << j << endl;
					for (int i = 0; i < index; i++)
					{
						if (j == specialization[i] && staties[i] != -1)
						{
							cout << names[i] << " ";
							if (staties[i] == 1)
								cout << "urgent\n";
							else cout << "regular\n";
						}
					}
				}
		}
		else if (n == 3)
		{
			cin >> sp;
			if (freq[sp] > 0)
				for (int i = 0; i < index; i++)
				{
					if (specialization[i] == sp)
					{
						cout << names[i] << " please go with the dr\n ";
						staties[i] = -1;
						freq[specialization[i]]--;
						break;
					}
				}
			else
				cout << "NO PATIENT AT THE MOMENT.HAVE A REST,DR\n";
		}
		else if (n == 4)
			break;
	}
}
int main()
{
	system();
}