#include <Windows.h>
#include <string>
#include <stdio.h>


#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct SaveContext
{
	string strNtPath;
	string strDosDevice;
};

typedef vector<SaveContext> svrVector;

void RestoreDevice(SaveContext& Context);

int mymain(void)
{
	//读磁盘配置并排除C盘
	DWORD dwDisks = GetLogicalDrives() & 0xfffffffb;

	svrVector NtDevices;

	CHAR chDosDevice[8] = { 0 };

	*(WORD*)chDosDevice = ':A';

	CHAR chNtPath[MAX_PATH] = { 0 };

	for (int Mask = 1; Mask; Mask <<= 1, chDosDevice[0]++)
	{
		if (dwDisks & Mask)
		{
			QueryDosDeviceA(chDosDevice, chNtPath, MAX_PATH);

			SaveContext Context;
			Context.strDosDevice = chDosDevice;
			Context.strNtPath = chNtPath;

			//先保存符号名和设备之间的关系
			NtDevices.push_back(Context);

			cout << Context.strDosDevice << "<--->" << Context.strNtPath << endl;

			//除了C:以外其它的盘符正一个一个的不见了
			//DefineDosDeviceA(DDD_REMOVE_DEFINITION, Context.strDosDevice.c_str(), NULL);
		}
	}

	//现在打开"我的电脑"看看
	system("pause");

	//现在隐藏的盘符又出现了,呵呵
	for_each(NtDevices.begin(), NtDevices.end(), RestoreDevice);

	ExitProcess(0);

	return 0;
}

void RestoreDevice(SaveContext& Context)
{
	int result = DefineDosDeviceA(DDD_RAW_TARGET_PATH, Context.strNtPath.c_str(), Context.strDosDevice.c_str());

	result = DefineDosDeviceA(DDD_RAW_TARGET_PATH, Context.strDosDevice.c_str(), Context.strNtPath.c_str());
	return;
}



void getSystemName()
{
	std::string vname;
	//先判断是否为win8.1或win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibraryA("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		printf_s("此电脑的版本为:%s\n", vname.c_str());
		return;
	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		DWORD buildno = dwBuildNumber & 0xffff;
		if (buildno >= 0x55f0)
		{
			vname = "Microsoft Windows 11";
			//return  11;
		}
		vname = "Microsoft Windows 10";
		printf_s("此电脑的版本为:%s\n", vname.c_str());
		//return;
	}
	//下面判断不能Win Server，因为本人还未有这种系统的机子，暂时不给出



	//判断win8.1以下的版本
	SYSTEM_INFO info;                //用SYSTEM_INFO结构判断64位AMD处理器  
	GetSystemInfo(&info);            //调用GetSystemInfo函数填充结构  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable:4996)
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{

		//下面根据版本信息判断操作系统名称  
		switch (os.dwMajorVersion)
		{                        //判断主版本号  
		case 4:
			switch (os.dwMinorVersion)
			{                //判断次版本号  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996年7月发布  
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					vname = "Microsoft Windows 95";
				break;
			case 10:
				vname = "Microsoft Windows 98";
				break;
			case 90:
				vname = "Microsoft Windows Me";
				break;
			}
			break;
		case 5:
			switch (os.dwMinorVersion)
			{               //再比较dwMinorVersion的值  
			case 0:
				vname = "Microsoft Windows 2000";    //1999年12月发布  
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001年8月发布  
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003年3月发布  
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					vname = "Microsoft Windows Server 2003 R2";
				break;
			}
			break;
		case 6:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows Vista";
				else
					vname = "Microsoft Windows Server 2008";   //服务器版本  
				break;
			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 7";
				else
					vname = "Microsoft Windows Server 2008 R2";
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 8";
				else
					vname = "Microsoft Windows Server 2012";
				break;
			}
			break;
		default:
			vname = "未知操作系统";
		}
		printf_s("此电脑的版本为:%s\n", vname.c_str());
	}
	else
		printf_s("版本获取失败\n");
}

void main()
{
	mymain();

	WCHAR strpath[MAX_PATH];
	QueryDosDeviceW(L"c:", strpath, MAX_PATH);
	getSystemName();
	system("pause");
}