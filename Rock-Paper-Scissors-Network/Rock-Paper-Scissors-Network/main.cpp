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
void sendEx(Serwerconnect& sr, SOCKET& Connection, const char* buff, int size);
void recvEx(Serwerconnect& sr, SOCKET& Connection, char* buff, int size);
void Options() 
{
	
}
void Conectroom(Serwerconnect& sr)
{
	int main_ConectRoom1;
	string Nameroom;
	char key[2];
	int PlayerMax;
	char KeyRoom[6];
	cout << "Create Room-2\n";
	cout <<"Search room-0\n" ;
	cout << "ConectRoom-1\n";
	cin >> main_ConectRoom1;
	if (main_ConectRoom1==0)//Search room
	{
		key[0] = 's';
		sendEx(sr, sr.Conection, key, 2);
	}
	else if (main_ConectRoom1==1)//Connect room
	{
		key[0] = 'c';
		cout << "Room key:";
		cin >> KeyRoom;
		sendEx(sr, sr.Conection, key, 2);
	}
	else if (main_ConectRoom1==2)//create rooms
	{
		key[0] = 'r';
		key[1] = '\0';
		cout << "Room Name:";
		cin >> Nameroom;
		cout << "Max Player:";
		cin >> PlayerMax;
		sendEx(sr, sr.Conection, key, 2);
		sendEx(sr,sr.Conection, Nameroom.c_str(), Nameroom.length()+1);
		Sleep(100);
		sendEx(sr, sr.Conection, to_string(PlayerMax).c_str(), to_string(PlayerMax).length() + 1);
		Sleep(100);
		recvEx(sr, sr.Conection,KeyRoom,sizeof(KeyRoom));
		system("cls");
		cout << Nameroom<<"\n";
		cout << KeyRoom << "\n";
	}
	else 
	{
		cout << "Error 2";
	}
}
void MainMenu(int MenuOptions, Serwerconnect& sr)
{
	switch (MenuOptions)
	{
	case 0:
		Conectroom(sr);
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
struct Player
{
	char login[20]="";
	int password = 0;
	int score = 0;
};
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
void SingIn(Serwerconnect& sr, char login[20], int& password)
{
	cout << "Login:";
	cin >> login;
	cout << "Password:";
	cin >> password;
	string paswordserwer;
	paswordserwer = to_string(password);
	bool res = SendIn(sr, paswordserwer.c_str(), login);
	if (res == false){
		cout << "Error:you computer alahatbar\n";
	cout << "restart Sing In";
	Sleep(550);
	SingIn(sr,login,password);
	}
	else
		cout << "Sucsesful\n";
	Sleep(500);
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
	bool res=SendUp(sr, paswordserwer, login);
	if (res == false)
		cout << "Error:you computer alahatbar\n";
	else
		cout << "Sucsesful\n";
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
	Inithilization(con, "77.121.173.140",8080);
	Connect(con);
	Login(pl,con);
	system("cls");
	cout << "MainMenu\n";
	cout << "PlayGame-0\n";
	cout << "Options-1\n";
	cout << "exit-2\n";
	cin >> mainop;
	MainMenu(mainop, con);
	system("pause");
	return 0;
}