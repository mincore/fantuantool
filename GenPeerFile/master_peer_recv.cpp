#include "master_peer_recv.h"
#include "peer_stream.h"
#include "master_peer_dispatch.h"
#include "peer_dispatch.h"
#include <malloc.h>

bool CALLBACK OnLoginReq_Callback(PEER_CLIENT pPeerClient, PeerInputStream& stream)
{
	uint32 iSessionId = 0;
	stream.Serialize(iSessionId);
	uint16 iAccountNameLen = 0;
	stream.Serialize(iAccountNameLen);
	char* accountName = (char*)alloca(iAccountNameLen+1);
	stream.Serialize(iAccountNameLen, accountName);
	accountName[iAccountNameLen] = '\0';

	MasterPeerRecv::OnLoginReq(pPeerClient, iSessionId, accountName);
	return true;
}

static PeerClientDispatchFilter::Func test_func[] = 
{
	OnLoginReq_Callback,
	NULL
};

MasterPeerDispatch::MasterPeerDispatch()
{
	PeerClientDispatchFilterArray::GetFilter(0).m_pFunc = test_func;
}