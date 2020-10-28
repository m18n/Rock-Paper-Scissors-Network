#define WIN32_LEAN_AND_MEAN
#include<iostream>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<string>
using namespace std;
void Options() 
{
	
}
void Conectroom() 
{
	string KeyRoom;
	cout << "room Key:";
	cin >> KeyRoom;
}
void MainMenu(int MenuOptions)
{
	if (MenuOptions==0)
	{
		Conectroom();
	}
	else if (MenuOptions == 1)
	{
		Options();
	}
	else if (MenuOptions == 2)
	{
		exit(1);
	}
	else
	{
		cout << "Error 2";
	}
}
struct Player
{
	char login[20]="";
	int password = 0;
	int score = 0;
};
struct Serwerconnect
{
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
	SOCKET Conection;
};
void Inithilization(Serwerconnect& sr) {
	sr.DLLversion = MAKEWORD(2, 2);
	if (WSAStartup(sr.DLLversion, &sr.wsaData) != 0) {
		cout << "Error 1\n";
		exit(1);
	}
	sr.addr.sin_addr.s_addr = inet_addr("77.121.173.140");
	sr.addr.sin_port = htons(8080);
	sr.addr.sin_family = AF_INET;
	
}
void Connect(Serwerconnect& sr)
{
	sr.Conection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(sr.Conection, (SOCKADDR*)&sr.addr, sizeof(sr.addr))!=0)
	{
		closesocket(sr.Conection);
		system("cls");
		int choise;
		cout << "Error:failed conect serwer\n"<<"Please restart you program\n"<<"1-conect\n"<<"0-exit\n";
		cin >> choise;
		if (choise ==0)
			exit(1);
		else if (choise==1)
			Connect(sr);
	}
}
void sendEx(Serwerconnect& sr,SOCKET& Connection,const char* buff,int size) {
	int result= send(Connection, buff, size, NULL);
	if (result == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(Connection);
		system("cls");
		Connect(sr);
		return;
	}
}
void recvEx(Serwerconnect& sr, SOCKET& Connection,char* buff, int size) {
	int result = recv(Connection, buff, size, NULL);
	if (result == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(Connection);
		system("cls");
		Connect(sr);
		return;
	}
}
bool SendLogin(Serwerconnect& sr,const char passwordchar[20],const char login[20]) {
	char temp[20];
	char score[20];
	int size_password = strlen(passwordchar)+1;
	sendEx(sr,sr.Conection, "i", 2);
	sendEx(sr,sr.Conection, login, strlen(login) + 1);
	sendEx(sr,sr.Conection, passwordchar, size_password);
	recvEx(sr,sr.Conection, temp, sizeof(temp));
	recvEx(sr,sr.Conection, score, sizeof(score));
	if (strcmp(temp, "ok") == 0)
		return true;
	else
		return false;
}
void SingIn(Serwerconnect& sr,char login[20],int& password)
{
	cout << "Login:";
	cin >> login;
	cout << "Password:";
	cin >> password;
	string paswordserwer;
	paswordserwer = to_string(password);
	bool res=SendLogin(sr, paswordserwer.c_str(),login);
	if(res==false)
		cout << "Error:you computer alahatbar\n";
	else
		cout << "Sucsesful";
}
void SingUp(Serwerconnect& sr,char login[20], int& password)
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
	sendEx(sr,sr.Conection, "u", 1);
	sendEx(sr,sr.Conection, login,strlen(login));
	sendEx(sr,sr.Conection, paswordserwer.c_str(), paswordserwer.length());
}
void Login(Player& pl, Serwerconnect& sr) {
	int choice = 0;
	cout << "Sing in-1\n";
	cout << "Sing up-2\n";
	cin >> choice;
	if (choice == 1)
		SingIn(sr,pl.login, pl.password);
	else if (choice == 2)
		SingUp(sr,pl.login, pl.password);
}
int main() {
	Serwerconnect con;
	Player pl;
	int mainop;
	cout << "MainMenu\n";
	cout << "ConectRoom-0\n";
	cout << "Options-1\n";
	cout << "exit-2\n";
	cin >>mainop;
	MainMenu(mainop);
	Inithilization(con);
	Connect(con);
	Login(pl,con);
	system("pause");
	return 0;
}