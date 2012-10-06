/*****************************************************************************************
	filename:	handler.h
	created:	10/04/2012
	author:		chen
	purpose:	io request handler

*****************************************************************************************/

#ifndef _H_HANDLER
#define _H_HANDLER

#include "simplenet_common.h"

typedef bool (CALLBACK* ON_CONNECTION)(ConnID);
typedef void (CALLBACK* ON_DISCONNECT)(ConnID);
typedef void (CALLBACK* ON_DATA)(ConnID, uint32, char*);
typedef void (CALLBACK* ON_CONNECT_FAILED)(void*);

struct Handler
{
	ON_CONNECTION OnConnection;
	ON_DISCONNECT OnDisconnect;
	ON_DATA OnData;
	ON_CONNECT_FAILED OnConnectFailed;
};

#endif