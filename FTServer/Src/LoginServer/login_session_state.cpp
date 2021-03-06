#include "login_session.h"

void LoginSession::InitStateMachine()
{
	FSMState* pState = NULL;

	super::InitStateMachine();

	// when state is onconnection
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_ONCONNECTION);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_LOGGEDIN, SESSION_STATE_LOGGEDIN);

	// when state is loggedin
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_LOGGEDIN);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_DISCONNECT, SESSION_STATE_DISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDISCONNECT, SESSION_STATE_ONDISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDATA, SESSION_STATE_LOGGEDIN);
	pState->AddTransition(SESSION_EVENT_SEND, SESSION_STATE_LOGGEDIN);
	pState->AddTransition(SESSION_EVENT_ONVERSIONREQ, SESSION_STATE_ONVERSIONREQ);

	// when state is version req
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_ONVERSIONREQ);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_DISCONNECT, SESSION_STATE_DISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDISCONNECT, SESSION_STATE_ONDISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONLOGINREQ, SESSION_STATE_ONLOGINREQ);
	pState->AddTransition(SESSION_EVENT_SEND, SESSION_STATE_ONVERSIONREQ);

	// when state is login req
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_ONLOGINREQ);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_DISCONNECT, SESSION_STATE_DISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDISCONNECT, SESSION_STATE_ONDISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDATA, SESSION_STATE_ONLOGINREQ);
	pState->AddTransition(SESSION_EVENT_SEND, SESSION_STATE_ONLOGINREQ);
	pState->AddTransition(SESSION_EVENT_ONLOGINFAILEDACK, SESSION_STATE_ONLOGINFAILEDACK);
	pState->AddTransition(SESSION_EVENT_ONGATEALLOCNTF, SESSION_STATE_ONGATEALLOCNTF);

	// when state is on login ack
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_ONLOGINFAILEDACK);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_DISCONNECT, SESSION_STATE_DISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDISCONNECT, SESSION_STATE_ONDISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDATA, SESSION_STATE_ONLOGINFAILEDACK);
	pState->AddTransition(SESSION_EVENT_SEND, SESSION_STATE_ONLOGINFAILEDACK);

	// when state is gate allocate ntf
	pState = m_StateMachine.ForceGetFSMState(SESSION_STATE_ONGATEALLOCNTF);
	if (!pState)
	{
		LOG_ERR(LOG_SERVER, _T("Can't get fsm state"));
		return;
	}

	pState->AddTransition(SESSION_EVENT_DISCONNECT, SESSION_STATE_DISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDISCONNECT, SESSION_STATE_ONDISCONNECT);
	pState->AddTransition(SESSION_EVENT_ONDATA, SESSION_STATE_ONGATEALLOCNTF);
	pState->AddTransition(SESSION_EVENT_SEND, SESSION_STATE_ONGATEALLOCNTF);
}