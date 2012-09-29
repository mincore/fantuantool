#include "login_server_loop.h"
#include "logic_command.h"
#include "login_server.h"
#include "login_server_config.h"

LoginServerLoop::LoginServerLoop() :
SessionServerLoop<LoginSession>(g_pServerConfig->m_iSessionMax)
{
}

LoginServerLoop::~LoginServerLoop()
{
}

int32 LoginServerLoop::Init()
{
	int32 iRet = 0;

	iRet = super::Init(g_pServer);
	if (iRet != 0)
	{
		return iRet;
	}

	return 0;
}

void LoginServerLoop::Destroy()
{
	super::Destroy();
}

int32 LoginServerLoop::Start()
{
	int32 iRet = 0;

	iRet = super::Start();
	if (iRet != 0)
	{
		return iRet;
	}

	return 0;
}

uint32 LoginServerLoop::_Loop()
{
	// check if ready for shutdown
	if (m_iShutdownStatus == START_SHUTDOWN)
	{
		_ReadyForShutdown();
	}

	return 100;
}

bool LoginServerLoop::_OnCommand(LogicCommand* pCommand)
{
	switch (pCommand->m_iCmdId)
	{
	case 11:
		break;

	default:
		return super::_OnCommand(pCommand);
		break;
	}

	return true;
}