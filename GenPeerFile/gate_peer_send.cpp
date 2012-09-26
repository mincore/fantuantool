#include "gate_peer_send.h"
#include "peer_stream.h"

uint32 GatePeerSend::GateHoldReq(PEER_SERVER pPeerServer, uint32 iSessionId, const TCHAR *strAccountName)
{
	PeerOutputStream stream;
	uint16 iAccountNameLen = (uint16)wcslen(strAccountName);
	stream.Serialize(iSessionId);
	stream.Serialize(iAccountNameLen);
	stream.Serialize(iAccountNameLen, strAccountName);

	stream.SetId(PEER_FILTER_GATE, 0);
	return stream.Send(pPeerServer);
}
