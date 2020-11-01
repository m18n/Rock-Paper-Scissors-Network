#define WIN32_LEAN_AND_MEAN
#include<iostream>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")
#include<WinSock2.h>
#include<string>
using namespace std;
struct Serwerconnect
{
	WSAData wsaData;
	WORD DLLversion;
	SOCKADDR_IN addr;
	SOCKET Conection;
};
struct Player
{
	char login[20] = "";
	int password = 0;
	int score = 0;
	bool ready=false;
};
void sendEx(Serwerconnect& sr, SOCKET& Connection, const char* buff, int size);
void recvEx(Serwerconnect& sr, SOCKET& Connection, char* buff, int size);
void Login(Player& pl, Serwerconnect& sr);
void GetNotification(Serwerconnect& sr)
{
	cout << "Notifaction\n";
	char bufer[30];
	char maxPlayer[4];
	recvEx(sr, sr.Conection, maxPlayer, sizeof(maxPlayer));
	int Player = atoi(maxPlayer);
	for (int i = 0; i < Player; i++)
	{
		recvEx(sr, sr.Conection, bufer, sizeof(bufer));
		cout << bufer<<"\n";
	}
}
void RoomSesions(char NameR[10],char KeyR[6], Serwerconnect& sr)
{
	system("cls");
	cout << "Name Room: " << NameR <<"\n"<< " Key: " << KeyR << "\n";
	GetNotification(sr);
}
void Options() 
{
	
}
void CreateRoom(Serwerconnect& sr) {
	char key[2];
	char playermax[4];
	char nameroom[10];
	char keyroom[6];
	key[0] = 'r';
	key[1] = '\0';
	cout << "Room Name:";
	cin >> nameroom;
	cout << "Max Player:";
	cin >> playermax;
	sendEx(sr, sr.Conection, key, 2);
	sendEx(sr, sr.Conection, nameroom, strlen(nameroom)+1);
	Sleep(100);
	sendEx(sr, sr.Conection, playermax, strlen(playermax) + 1);
	recvEx(sr, sr.Conection, keyroom, sizeof(keyroom));
	RoomSesions( nameroom,keyroom,sr);
}
void ConnectRoom(Serwerconnect& sr) {
	char NR[10];
	char key[2];
	char keyroom[6];
	key[0] = 'c';
	cout << "Room key:";
	cin >> keyroom;
	sendEx(sr, sr.Conection, key, 2);
	sendEx(sr, sr.Conection,keyroom, strlen(keyroom)+1);
	recvEx(sr, sr.Conection, NR , 10);
	RoomSesions(NR,keyroom,sr);

}
void SearchRoom(Serwerconnect& sr) {
	char key[2];
	key[0] = 's';
	sendEx(sr, sr.Conection, key, 2);
}
void MenuRoom(Serwerconnect& sr)
{
	int main_ConectRoom1;
	string Nameroom;
	char key[2];
	int PlayerMax;
	char KeyRoom[6];
	cout << "Create Room-0\n";
	cout <<"Search room-1\n" ;
	cout << "ConectRoom-2\n";
	cin >> main_ConectRoom1;
	switch (main_ConectRoom1)
	{
	case 0://Create rooms
		CreateRoom(sr);
		break;
	case 1://Search Room
		SearchRoom(sr);
		break;
	case 2://Connect Room
		ConnectRoom(sr);
		break;
	default:
		cout << "Error 2";
		break;
	}

}
void MainMenu( Serwerconnect& sr)
{
	int MenuOptions;
	cout << "MainMenu\n";
	cout << "PlayGame-0\n";
	cout << "Options-1\n";
	cout << "exit-2\n";
	cin >> MenuOptions;
	system("cls");
	switch (MenuOptions)
	{
	case 0:
		MenuRoom(sr);
		break;
	case 1:
		Options();
		break;
	case 2:
		exit(1);
		break;
	default:
		cout << "Error 2";
		break;
	}
}
void Inithilization(Serwerconnect& sr,string ip,int port) {
	sr.DLLversion = MAKEWORD(2, 2);
	if (WSAStartup(sr.DLLversion, &sr.wsaData) != 0) {
		cout << "Error 1\n";
		exit(1);
	}
	sr.addr.sin_addr.s_addr = inet_addr(ip.c_str());
	sr.addr.sin_port = htons(port);
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
		cout << "Error:failed conect serwer\nPlease restart you program\n1-conect\n0-exit\n";
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
bool SendIn(Serwerconnect& sr,const char passwordchar[20],const char login[20]) {
	char temp[20];
	char score[20];
	int size_password = strlen(passwordchar)+1;
	sendEx(sr,sr.Conection, "i", 2);
	sendEx(sr,sr.Conection, login,strlen(login) + 1);
	Sleep(100);
	sendEx(sr,sr.Conection, passwordchar, size_password);
	recvEx(sr,sr.Conection, temp, sizeof(temp));
	recvEx(sr,sr.Conection, score, sizeof(score));
	if (strcmp(temp, "ok") == 0)
		return true;
	else
		return false;
}
bool SendUp(Serwerconnect& sr, string password, const char login[20]) {
	char temp[10];
	sendEx(sr, sr.Conection, "u", 2);
	sendEx(sr, sr.Conection, login, strlen(login)+1);
	Sleep(100);
	sendEx(sr, sr.Conection, password.c_str(), password.length()+1);
	recvEx(sr, sr.Conection, temp, sizeof(temp));
	if (strcmp(temp, "ok") == 0)
		return true;
	else
		return false;
}
void SingIn(Serwerconnect& sr,Player& pl)
{
	cout << "Login:";
	cin >> pl.login;
	cout << "Password:";
	cin >> pl.password;
	string paswordserwer;
	paswordserwer = to_string(pl.password);
	bool res = SendIn(sr, paswordserwer.c_str(), pl.login);
	if (res == false)
	{
		cout << "Error:you computer alahatbar\n";
		Sleep(550);
		system("cls");
		Login(pl,sr);
	}
	else
		cout << "Sucsesful\n";
	Sleep(500);
}
void SingUp(Serwerconnect& sr,Player& pl)
{
	int password1=0;
	string paswordserwer;
	system("cls");
	cout << "Login:";
	cin >> pl.login;
	system("cls");
	do
	{
		
		cout << "Password:";
		cin >> pl.password;
		cout << "Password:";
		cin >> password1;
		system("cls");
	} while (pl.password != password1);
	paswordserwer = to_string(pl.password);
	bool res=SendUp(sr, paswordserwer, pl.login);
	if (res == false)
	{
		cout << "Error:you computer alahatbar\n";
		Sleep(550);
		system("cls");
		Login(pl, sr);
	}
	else
		cout << "Sucsesful\n";
}
void Login(Player& pl, Serwerconnect& sr) {
	int choice = 0;
	cout << "Sing in-1\n";
	cout << "Sing up-2\n";
	cin >> choice;
	if (choice == 1)
		SingIn(sr, pl);
	else if (choice == 2)
		SingUp(sr, pl);
}
int main() {
	Serwerconnect con;
	Player pl;
	int mainop;
	Inithilization(con, "77.121.173.140",8080);
	Connect(con);
	Login(pl,con);
	system("cls");
	MainMenu(con);
	system("pause");
	return 0;
}