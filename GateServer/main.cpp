#include <cstdio>
#include "starnet.h"
#include "gate_server.h"

int __cdecl main(int argc, char **argv)
{
	g_pServer = GateServer::Instance();

	g_pServer->Init();
	LOG_STT(LOG_SERVER, _T("Listen to port: %d"), 5150);

	while (true)
	{
		Sleep(1);
	}
	
	g_pServer->Shutdown();
	g_pServer->Destroy();

	return 0;
}