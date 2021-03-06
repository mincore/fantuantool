/*****************************************************************************************
	filename:	region_player_context.h
	created:	10/14/2012
	author:		chen
	purpose:	record player context on region server

*****************************************************************************************/

#ifndef _H_REGION_PLAYER_CONTEXT
#define _H_REGION_PLAYER_CONTEXT

#include "server_common.h"
#include "state_machine.h"

enum
{
	PLAYER_STATE_NONE,
	PLAYER_STATE_ONREGIONALLOCREQ, // receive alloc req
	PLAYER_STATE_REGIONALLOCACK, // send alloc ack to master server
	PLAYER_STATE_ONREGIONRELEASEREQ, // receive release req
	PLAYER_STATE_ONREGIONENTERREQ, // receive enter req
	PLAYER_STATE_REGIONENTERREQ, // send enter req
	PLAYER_STATE_ONREGIONENTERACK, // receive enter ack
	PLAYER_STATE_ONREGIONLEAVEREQ, // receive leave req
	PLAYER_STATE_SERVERTIMENTF, // send server time to client
	PLAYER_STATE_ONCLIENTTIMEREQ, // receive client time
	PLAYER_STATE_SERVERTIME2NTF, // send server time 2nd time to client
	PLAYER_STATE_INITAVATARNTF, // send initial avatardata to client
};

enum
{
	PLAYER_EVENT_ONREGIONALLOCREQ,
	PLAYER_EVENT_REGIONALLOCACK,
	PLAYER_EVENT_ONREGIONRELEASEREQ,
	PLAYER_EVENT_ONREGIONENTERREQ,
	PLAYER_EVENT_REGIONENTERREQ,
	PLAYER_EVENT_ONREGIONENTERACK,
	PLAYER_EVENT_ONREGIONLEAVEREQ,
	PLAYER_EVENT_SERVERTIMENTF,
	PLAYER_EVENT_ONCLIENTTIMEREQ,
	PLAYER_EVENT_SERVERTIME2NTF,
	PLAYER_EVENT_INITAVATARNTF,
};

class RegionServerLoop;
class RegionLogicLoop;
class Map;
class Avatar;
class RegionPlayerContext
{
public:
	// cstr and dstr
	RegionPlayerContext();
	~RegionPlayerContext();

	// clear all variables
	void Clear();
	// send fail request to master
	void SendPlayerFailToMaster();
	
	void OnRegionAllocReq(uint32 iSessionId, uint64 iAvatarId, const TCHAR* strAvatarName);
	void OnRegionReleaseReq();
	void OnRegionEnterReq();
	void OnRegionEnterAck();
	void OnRegionLeaveReq();
	void OnClientTimeReq(uint32 iClientTime);

	void SendAvatarEnterNtf(RegionPlayerContext*);
	void OnRegionChatReq(const char* strMessage);

private:
	// initialize state machine
	void _InitStateMachine();

	// send initial data to client
	void _SendInitialAvatarData();

	// first time enter map
	void _InitialMapEnter();
	
	
	// broadcast avatar enter
	void _BroadcastAvatarEnterNtf();
	// send others to client
	void _SendRegionAvatars();
	// broadcast avatar leave
	void _BroadcastAvatarLeaveNtf();
	
public:
	uint32 m_iSessionId;
	uint64 m_iAvatarId;
	TCHAR m_strAvatarName[AVATARNAME_MAX+1];
	bool m_bFinalizing; // almost leave or not
	StateMachine m_StateMachine;
	PEER_SERVER m_pGateServer;	// related gate server
	CRITICAL_SECTION m_csContext;

	// map info, need thread control
	uint16 m_iMapId;
	Map* m_pMap;
	RegionLogicLoop* m_pLogicLoop;
	Avatar* m_pAvatar;

	static RegionServerLoop* m_pMainLoop;
};

#endif 