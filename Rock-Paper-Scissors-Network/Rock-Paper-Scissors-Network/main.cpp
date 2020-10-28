#include<iostream>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<string>
using namespace std;
SOCKET Conection;
void MainMenu(int MenuOptions)
{

}
struct Player
{
	char login[20]="";
	int password = 0;
	int score = 0;
};
void Conect()
{
	SOCKADDR_IN addr;
	int sizeford = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("77.121.173.140");
	addr.sin_port = htons(8080);
	addr.sin_family = AF_INET;
	Conection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Conection, (SOCKADDR*)&addr, sizeof(addr))!=0) 
	{
		system("cls");
		int true2;
		cout << "Error:failed conect serwer\n"<<"Please restart you program\n"<<"1-conect\n"<<"0-exit\n";
		cin >> true2;
		if (true2==0)
		{
			exit(1);
		}
		else if (true2==1)
		{
			Conect();
		}
	}
}
struct Serwerconect
{
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
};
void SingIn(char login[20],int& password)
{
	char temp[10]; 
	char score[10];
	char passwordchar[20];
	cout << "Login:";
	cin >> login;
	cout << "Password:";
	cin >> password;
	string paswordserwer;
	paswordserwer = to_string(password);
	strcpy_s(passwordchar, paswordserwer.c_str());
	int size_passwoed = paswordserwer.length() + 1;
	send(Conection, "i", 2, NULL);
	send(Conection, login, strlen(login)+1, NULL);
	send(Conection, passwordchar,size_passwoed , NULL);
	recv(Conection, temp, sizeof(temp), NULL); 
	recv(Conection, score, sizeof(score), NULL);
	if (strcmp(temp,"ok")==0)
	{
		cout << "Sucsesful";
	}
	else 
	{
		cout << "Error:you computer alahatbar\n";
	}
}
void SingUp(char login[20], int& password)
{
	int password1=0;
	string paswordserwer;
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
	paswordserwer = to_string(password);
	send(Conection, "u", 1, NULL);
	send(Conection, login,strlen(login), NULL);
	send(Conection, paswordserwer.c_str(), paswordserwer.length(), NULL);
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
	Serwerconect con;
	con.DLLversion = MAKEWORD(2, 1);
	if (WSAStartup(con.DLLversion, &con.wsaData) != 0) {
		cout << "Error 1\n";
		exit(1);
	}
	Conect();
	Player pl;
	Login(pl);
	cout << "MainMenu\n";
	cout << "ConectRoom-0\n";
	cout << "Ontions-1\n";
	cout << "exit-2\n";
	system("pause");
	return 0;
}