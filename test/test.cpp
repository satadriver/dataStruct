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
	//���������ò��ų�C��
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

			//�ȱ�����������豸֮��Ĺ�ϵ
			NtDevices.push_back(Context);

			cout << Context.strDosDevice << "<--->" << Context.strNtPath << endl;

			//����C:�����������̷���һ��һ���Ĳ�����
			//DefineDosDeviceA(DDD_REMOVE_DEFINITION, Context.strDosDevice.c_str(), NULL);
		}
	}

	//���ڴ�"�ҵĵ���"����
	system("pause");

	//�������ص��̷��ֳ�����,�Ǻ�
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
	//���ж��Ƿ�Ϊwin8.1��win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibraryA("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
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
		printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
		//return;
	}
	//�����жϲ���Win Server����Ϊ���˻�δ������ϵͳ�Ļ��ӣ���ʱ������



	//�ж�win8.1���µİ汾
	SYSTEM_INFO info;                //��SYSTEM_INFO�ṹ�ж�64λAMD������  
	GetSystemInfo(&info);            //����GetSystemInfo�������ṹ  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable:4996)
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{

		//������ݰ汾��Ϣ�жϲ���ϵͳ����  
		switch (os.dwMajorVersion)
		{                        //�ж����汾��  
		case 4:
			switch (os.dwMinorVersion)
			{                //�жϴΰ汾��  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996��7�·���  
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
			{               //�ٱȽ�dwMinorVersion��ֵ  
			case 0:
				vname = "Microsoft Windows 2000";    //1999��12�·���  
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001��8�·���  
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003��3�·���  
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
					vname = "Microsoft Windows Server 2008";   //�������汾  
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
			vname = "δ֪����ϵͳ";
		}
		printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
	}
	else
		printf_s("�汾��ȡʧ��\n");
}

void main()
{
	mymain();

	WCHAR strpath[MAX_PATH];
	QueryDosDeviceW(L"c:", strpath, MAX_PATH);
	getSystemName();
	system("pause");
}