#include<iostream>
using namespace std;
struct Player
{
	char login[20]="";
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
void SingUp(char login[20], int& password)
{
	int password1=0;
	system("cls");
	cout << "Login:";
	cin >> login;
	system("cls");
	do
	{
		
		cout << "Password:";
		cin >> password;
		cout << "Password:";
		cin >> password1;
		system("cls");
	} while (password != password1);
}
void Login(Player& pl) {
	int choice = 0;
	cout << "Sing in-1\n";
	cout << "Sing up-2\n";
	cin >> choice;
	if (choice == 1)
		SingIn(pl.login, pl.password);
	else if (choice == 2)
		SingUp(pl.login, pl.password);
}
int main() {
	Player pl;
	Login(pl);
	system("pause");
	return 0;
}