
#include <string.h>
#include <string>
#include "network.h"
#include "cmd.h"
#include <iostream>

using namespace std;


int main(int argc, char ** argv) {
	if (argc <= 2)
	{
		return FALSE;
	}

	int iret = 0;

	int target = atoi(argv[2]);

	Cmd *cmd = new Cmd(argv[1], target);

	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cmd->mainwork, cmd, 0, 0));

	cout << "input any key to quit..." << endl;

	getchar();

	Network::uninitNetwork();

	return 0;
}