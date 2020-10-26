#include<iostream>
using namespace std;
void Vxid(int pass,char Log[50])
{
	cout << "Login:";
	cin >> Log;
	cout << "Password:";
	cin >> pass;
}
void Singup(char lo[50], int passwor)
{
    int password1;
	cout << "Login:";
	cin >> lo;
	cout << "password:";
	cin >> passwor;
	cout << "password:";
	cin >> password1;
		if (passwor == password1)
		{
			passwor = passwor;
			
		}
		else if (passwor != password1)
		{
			cout << "password";
			cin >> password1;
		}
}
struct Player
{
	char Login[50];
	int password;
	int score;
};
int main() {
	int true1=0;
	int passw=0;
	char Logg[50];
	cout <<"Sing in-1\n";
	cout << "sing up-2\n";
	cin >> true1;
	if (true1 == 1)
	{
		Vxid(passw,Logg);
	}
	else if (true1 == 2)
	{
		Singup(Logg,passw);
	}
	system("pause");
	return 0;
}