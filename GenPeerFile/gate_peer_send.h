#ifndef _H_GATE_PEER_SEND
#define _H_GATE_PEER_SEND

#include "server_common.h"

struct GatePeerSend
{
	static int32 GateHoldReq(PEER_SERVER pPeerServer, uint32 iLoginSessionId, const TCHAR* strAccountName);
};

#endif