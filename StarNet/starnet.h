#ifndef _H_STAR_NET
#define _H_STAR_NET

#include "common.h"
#include "log.h"

class StarNet
{
public:
	static int32 Init();
	static void Destroy();

	static LPFN_ACCEPTEX acceptex_;
	static LPFN_CONNECTEX connectex_;
	static LPFN_DISCONNECTEX disconnectex_;
	static LPFN_GETACCEPTEXSOCKADDRS getacceptexsockaddrs_;
};

#define SN_LOG_DBG(Expression, ...) LOG_DBG(LOG_STARNET, Expression, __VA_ARGS__)
#define SN_LOG_WAR(Expression, ...) LOG_WAR(LOG_STARNET, Expression, __VA_ARGS__)
#define SN_LOG_ERR(Expression, ...) LOG_ERR(LOG_STARNET, Expression, __VA_ARGS__)
#define SN_LOG_STT(Expression, ...) LOG_STT(LOG_STARNET, Expression, __VA_ARGS__)


#endif