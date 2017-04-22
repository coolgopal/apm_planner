
/******************************************************************************
 * File name: myCall.cpp
 * Created on: 05-Apr-2017
 * Description: This is a C++ class member function definition file, contain
 *              member function definition of CCall class
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#include "myCall.h"

/* Definition of static data member, initialize with
 * some default value */
LinphoneCallState CCall::m_sStatus = LinphoneCallIdle;

/******************************************************************************
 * Name: CCall
 * Type: Constructor
 * Argument: NA
 * Return type: NA
 * Description: Default constructor, initialize data member
 *****************************************************************************/
CCall::CCall()
: m_bRunning(false)
, m_bCallInitiated(false)
, m_Status(LinphoneCallIdle)
, m_pLinphoneCore(NULL)
, m_pLinphoneCall(NULL)
{
	memset(m_szSIPAddress, 0, (sizeof(char) * MAX_SIP_ADDRESS));
	memset(&m_vtable, '\0', sizeof(m_vtable));
	// TODO Auto-generated constructor stub
}

/******************************************************************************
 * Name: CCall
 * Type: Virtual  destructor
 * Argument: NA
 * Return type: NA
 * Description: Deallocate memory or assign default value to data member
 *****************************************************************************/
CCall::~CCall()
{
	m_bRunning = false;
	m_bCallInitiated = false;
	m_Status = LinphoneCallIdle;
	m_pLinphoneCore = NULL;
	m_pLinphoneCall = NULL;
	memset(m_szSIPAddress, 0, (sizeof(char) * MAX_SIP_ADDRESS));

	// TODO Auto-generated destructor stub
}

/******************************************************************************
 * Name: ThreadEntry
 * Type: Private member function
 * Argument: void
 * Return type: void
 * Description: Main thread entry point after calling of StartThread()
 *              function, and this never terminates, it initiate and
 *              terminate a call based on request
 *****************************************************************************/
void CCall::ThreadEntry(void)
{
	while(true)
	{
		if(false == m_bRunning)
		{
			usleep(50000);
			if(true == m_bCallInitiated)
			{
				m_bCallInitiated = false;
				TerminateCall();
			}

			continue;
		}

		if(false == m_bCallInitiated)
		{
			m_bCallInitiated = true;
			InitiateCall();
		}

		if(NULL != m_pLinphoneCore)
		{
			linphone_core_iterate(m_pLinphoneCore);
		}
	}
}

/******************************************************************************
 * Name: StartCall
 * Type: Public member function
 * Argument: void
 * Return type: int(always 0)
 * Description: This is the pure virtual function implementation of
 *              IStartCall interface class, this function indicate to
 *              initiate a new call
 *****************************************************************************/
int CCall::StartCall(void)
{
	m_bRunning = true;

	return 0;
}

/******************************************************************************
 * Name: SetSIPAddress
 * Type: Public member function
 * Argument: char*(SIP address)
 * Return type: int(if NULL pointer then return 1, otherwise 0)
 * Description: This is the pure virtual function implementation IStartCall
 *              interface class, this function set SIP address
 *****************************************************************************/
int CCall::SetSIPAddress(char* p_SIPAddress)
{
	int iRetStatus = 0;

	do
	{
		if(NULL == p_SIPAddress)
		{
			iRetStatus = 1;
			break;
		}

		memset(m_szSIPAddress, 0, (sizeof(char) * MAX_SIP_ADDRESS));
		strcpy(m_szSIPAddress, p_SIPAddress);

	} while(false);

	return iRetStatus;
}

/******************************************************************************
 * Name: StopCall
 * Type: Public member function
 * Argument: void
 * Return type: int(always 0)
 * Description: This is the pure virtual function implementation of IStopCall
 *              interface class, this indicates to terminate an ongoing call
 *****************************************************************************/
int CCall::StopCall(void)
{
	m_bRunning = false;

	return 0;
}

/******************************************************************************
 * Name: GetStatus
 * Type: Public member function
 * Argument: void
 * Return type: LinphoneCallState(current call status)
 * Description: This is the pure virtual function implementation of IGetStatus
 *              interface class, it return the current call status
 *****************************************************************************/
LinphoneCallState CCall::GetStatus(void)
{
	CCall::GetStatus((void*)this);
	return m_Status;
}

/******************************************************************************
 * Name: Initialize
 * Type: Public member function
 * Argument: void
 * Return type: int(always 0)
 * Description: Class in initializer function
 *****************************************************************************/
int CCall::Initialize(LinphoneCallStateCb my_call_state_changed)
{
	do
	{
        m_vtable.call_state_changed = my_call_state_changed;

		StartThread();

	} while(false);

	return 0;
}

/******************************************************************************
 * Name: InitiateCall
 * Type: Private member function
 * Argument: void
 * Return type: int(if success then 0, otherwise 1)
 * Description: This function initiate a new call
 *****************************************************************************/
int CCall::InitiateCall(void)
{
	int iRetStatus = 0;

	do
	{
		m_pLinphoneCore = linphone_core_new(&m_vtable,NULL,NULL,NULL);

		if(NULL == m_pLinphoneCore)
		{
			iRetStatus = 1;
			break;
		}

		m_pLinphoneCall = linphone_core_invite(m_pLinphoneCore, m_szSIPAddress);

		if(NULL == m_pLinphoneCall)
		{
			iRetStatus = 1;
			break;
		}

		linphone_call_ref(m_pLinphoneCall);

	} while(false);

	if(0 != iRetStatus)
	{
		if(NULL != m_pLinphoneCore)
		{
			linphone_core_destroy(m_pLinphoneCore);
			m_pLinphoneCore = NULL;
		}
	}

	return iRetStatus;
}

/******************************************************************************
 * Name: TerminateCall
 * Type: Private member function
 * Argument: void
 * Return type: int(if success then 0, otherwise 1)
 * Description: This function terminate an ongoing call
 *****************************************************************************/
int CCall::TerminateCall(void)
{
	int iRetStatus = 0;

	do
	{
		if((NULL == m_pLinphoneCall) || (NULL == m_pLinphoneCore))
		{
			iRetStatus = 1;
			break;
		}

		if((LinphoneCallEnd != linphone_call_get_state(m_pLinphoneCall)) && \
				(LinphoneCallReleased != linphone_call_get_state(m_pLinphoneCall)))
		{
			linphone_core_terminate_call(m_pLinphoneCore, m_pLinphoneCall);
			linphone_call_unref(m_pLinphoneCall);
		}

		linphone_core_destroy(m_pLinphoneCore);

		m_pLinphoneCore = NULL;
		m_pLinphoneCall = NULL;

	} while(false);

	return iRetStatus;
}

/******************************************************************************
 * Name: SetStatus
 * Type: Private member function
 * Argument: LinphoneCallState(current call status)
 * Return type: int(always 0)
 * Description: This function sets current call status
 *****************************************************************************/
int CCall::SetStatus(LinphoneCallState p_Status)
{
	m_Status = p_Status;

	return 0;
}


