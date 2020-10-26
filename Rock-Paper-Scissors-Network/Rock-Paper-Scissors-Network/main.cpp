#include<iostream>
using namespace std;
struct Player
{
	char login[20];
	int password = 0;
	int score = 0;
};
void SingIn(char login[20],int& password)
{
	cout << "Login:";
	cin >> login;
	cout << "Password:";
	cin >> password;
}
void SingUp(char login[50], int& password)
{
	int password1;
	cout << "Login:";
	cin >> login;
	int i = 0;
	while (i == 0)
	{
		cout << "password:";
		cin >> password;
		cout << "password:";
		cin >> password1;
		if (password == password1)
		{
			password = password;
			i = 1;
		}
		else if (password != password1)
		{
			cout << "please(pasword=pasword)\n";

		}
	}


}

int main() {
	Player pl;
	int choice = 0;
	cout << "Sing in-1\n";
	cout << "Sing up-2\n";
	cin >> choice;
	if (choice == 1)
		SingIn(pl.login, pl.password);
	else if (choice == 2)
		SingUp(pl.login,pl.password);
	system("pause");
	return 0;
}