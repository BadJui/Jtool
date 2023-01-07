#include<windows.h>
#include<fstream>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BEFORE "echo "   // piece before buffer
#define AFTER " >>123.hex" // piece after buffer
#define AFTER2 " >123.hex" // piece after buffer

char nfilein[128], nfileout[128],buffer[1];
FILE *filein, *fileout, *file;
int i;
unsigned char cbyte;
unsigned long cx, offset;
using namespace std;
string str,allstr;
void exe2bat(string path){
	string cmd="exe2bat "+cmd+" exe.bat";
	system(cmd.c_str());
}
void bat2exe(string path){
	ifstream ifile;
	ifile.open(path);
	while(getline(ifile,str)){
		char abc=34;
		allstr=allstr+"ofile<<"+"R"+abc+"("+str+")"+abc+"<<"+"endl;\n";
	}
	ofstream ofile;
	ofile.open("bat.cpp");
	ofile<<R"(#include<windows.h>
#include<fstream>
using namespace std;
int main(){
ofstream ofile;
ofile.open("Run.bat");)"<<endl;
	ofile<<allstr<<R"(ofile.close();
system("Run.bat");
	return 0;
	})";
	ofile.close();
	system("g++.exe bat.cpp -o bat.exe -std=c++11 -static-libgcc");
}
void Mixed(string path){
	exe2bat(path);
	Sleep(1000);
	ifstream ifile;
	ifile.open(path);
	while(getline(ifile,str)){
		char abc=34;
		allstr=allstr+"ofile<<"+"R"+abc+"("+str+")"+abc+"<<"+"endl;\n";
	}
	ofstream ofile;
	ofile.open("Mixed.cpp");
	ofile<<R"(#include<windows.h>
#include<fstream>
using namespace std;
int main(){
ofstream ofile;
ofile.open("Run.bat");)"<<endl;
	ofile<<allstr<<R"(ofile.close();
system("Run.bat");
	return 0;
	})";
	ofile.close();
	system("g++.exe Mixed.cpp -o Mixed.exe -std=c++11 -static-libgcc");
}

int main(){
	cout<<"1.exe2bat(FILE < 64KB)\n2.bat2exe\n3.Mixed Mode(FILE < 64KB)\n";
	int xz;
	string path;
	cin>>xz;
	if(xz==1){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		exe2bat(path);
		Sleep(1000);
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "exe.bat".)"<<endl;
		system("pause");
	}
	if(xz==2){
		cout<<"Enter Your Bat Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		bat2exe(path);
		cout<<R"(It has been output in the current directory, and the file name is "bat.exe".)"<<endl;
		system("pause");
	}
	if(xz==3){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		Mixed(path);
		cout<<R"(It has been output in the current directory, and the file name is "Mixed.exe".)"<<endl;
		system("pause");
	}
	MessageBox(0,"Hello, if you like my software, welcome to my homepage to follow me!","Author(BadJui)",MB_OK);
	system("start https://space.bilibili.com/514225993");
	return 0;
}
