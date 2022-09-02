#include <windows.h>


void mainproc() {
	HANDLE h = CreateFileA("AutoThink.exe", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (h == INVALID_HANDLE_VALUE)
	{
		return;

	}

	char data[4096] = { 0 };
	int ret = 0;
	DWORD cnt = 0;
	ret = ReadFile(h, data, 1024, &cnt, 0);
	
	IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER*)data;
	IMAGE_NT_HEADERS32 * nt = (IMAGE_NT_HEADERS32*)(data + dos->e_lfanew);
	IMAGE_OPTIONAL_HEADER * opt = (IMAGE_OPTIONAL_HEADER*)&(nt->OptionalHeader);

	if (opt->DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE)
	{
		opt->DllCharacteristics = opt->DllCharacteristics & 0xffbf;
		ret = SetFilePointer(h, 0, 0, FILE_BEGIN);
		ret = WriteFile(h, data, 1024, &cnt, 0);
	}


	CloseHandle(h);
}

int main() {
	mainproc();
	return 0;
}