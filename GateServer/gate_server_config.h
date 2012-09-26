#ifndef _H_GATE_SERVER_CONFIG
#define _H_GATE_SERVER_CONFIG

#include "server_config.h"

class GateServerConfig : public ServerConfig
{
public:
	GateServerConfig(const TCHAR* strServerName);
	~GateServerConfig();

private:
	bool _LoadConfig();

public:
	uint32 m_iServerIP;
	uint16 m_iServerPort;
	uint32 m_iThreadCount;
	uint16 m_iSessionMax;
};

#endif
