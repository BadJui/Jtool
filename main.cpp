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
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string base64_encode(char const* bytes_to_encode, int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}
void exe2bat(string path){
	string cmd="exe2bat "+path+" exe.bat";
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
	cout<<"1.exe2bat(FILE<64KB  Old)\n2.bat2exe\n3.Mixed Mode(FILE<64KB New)\n4.exe2vbs\n5.exe2bat(New    It has some problems at present!)\n6.exe2js\n7.exe2ps1\n";
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
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "bat.exe".)"<<endl;
		system("pause");
	}
	if(xz==3){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		Mixed(path);
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "Mixed.exe".)"<<endl;
		system("pause");
	}
	if(xz==4){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		ifstream ifile;
		ifile.open(path, ios_base::binary);
		while(getline(ifile,str)){
			allstr=allstr+str+"\n";
		}
		ifile.close();
		ofstream ofile;
		ofile.open("exe.vbs");
		ofile<<R"(Option Explicit
dim D,E,b,p
Set D=CreateObject("Microsoft.XMLDOM")
Set E=D.createElement("t")
E.DataType="bin.base64"
E.Text=")"<<base64_encode(allstr.data(),allstr.size())<<R"("
Set b=CreateObject("ADODB.Stream")
Set p=CreateObject("Scripting.FileSystemObject").GetSpecialFolder(2)
b.Type=1
b.Open
b.Write E.NodeTypedValue
b.SaveToFile p+"\x.exe",2
CreateObject("WScript.Shell").Run p+"\x.exe")";
		ofile.close();
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "exe.vbs".)"<<endl;
		system("pause");
	}
	if(xz==5){
		string basestr;
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		ifstream ifile;
		ifile.open(path, ios_base::binary);
		while(getline(ifile,str)){
			allstr=allstr+str+"\n";
		}
		basestr=base64_encode(allstr.data(),allstr.size());
		ifile.close();
		ofstream ofile;
		ofile.open("newexe.bat");
		ofile<<R"(@Echo off
echo Don't care about the displayed information! Please wait for a moment!
del %tmp%\x
)";
		for(int i=0;i<basestr.size();i+=69){
			ofile<<"echo "<<basestr.substr(i,70)<<R"(>>%tmp%\x)"<<endl;
		}
		ofile<<R"(findstr /e "'v" "%~f0">%tmp%\x.vbs
cscript //nologo %tmp%\x.vbs
del %tmp%\x
del %tmp%\x.vbs
start "" %tmp%\x.exe
exit
Set f=CreateObject("Scripting.FileSystemObject")'v
Set p=f.GetSpecialFolder(2)'v
Set i=f.OpenTextFile(p+"\x",1)'v
c=i.ReadAll()'v
i.Close'v
Set x=CreateObject("Msxml2.DOMDocument")'v
Set o=x.CreateElement("base64")'v
o.dataType="bin.base64"'v
o.text=c'v
Set b=CreateObject("ADODB.Stream")'v
b.Type=1'v
b.Open'v
b.Write o.NodeTypedValue'v
b.SaveToFile p+"\x.exe",2'v
)";
		ofile.close();
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "newexe.bat".)"<<endl;
		system("pause");
	}
	if(xz==6){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		ifstream ifile;
		ifile.open(path, ios_base::binary);
		while(getline(ifile,str)){
			allstr=allstr+str+"\n";
		}
		ifile.close();
		ofstream ofile;
		ofile.open("exe.js");
		ofile<<R"(var D=new ActiveXObject("Microsoft.XMLDOM")
var E=D.createElement("t")
E.dataType="bin.base64"
E.text=")"<<base64_encode(allstr.data(),allstr.size())<<R"("
var b=new ActiveXObject("ADODB.Stream")
var p=new ActiveXObject("Scripting.FileSystemObject").GetSpecialFolder(2)
b.Type=1
b.Open()
b.Write(E.nodeTypedValue)
b.SaveToFile(p+"\\x.exe",2)
new ActiveXObject("WScript.Shell").Run(p+"\\x.exe"))";
		ofile.close();
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "exe.js".)"<<endl;
		system("pause");
	}
	if(xz==7){
		cout<<"Enter Your Exe Path:";
		cin>>path;
		system("cls");
		cout<<"Processing...";
		ifstream ifile;
		ifile.open(path, ios_base::binary);
		while(getline(ifile,str)){
			allstr=allstr+str+"\n";
		}
		ifile.close();
		ofstream ofile;
		ofile.open("exe.ps1");
		ofile<<R"($p=[IO.Path]::Combine($env:TEMP,"x.exe")
[IO.File]::WriteAllBytes($p,[Convert]::FromBase64String(")"<<base64_encode(allstr.data(),allstr.size())<<R"("))
Start-Process $p)";
		ofile.close();
		system("cls");
		cout<<R"(It has been output in the current directory, and the file name is "exe.ps1".)"<<endl;
		system("pause");
	}
	MessageBox(0,"Hello, if you like my software, welcome to my homepage to follow me!","Author(BadJui)",MB_OK);
	system("start https://space.bilibili.com/514225993");
	return 0;
}
