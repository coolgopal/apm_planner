
/******************************************************************************
 * File name: myCall.h
 * Created on: 05-Apr-2017
 * Description: This is a C++ header file, it contain a CCall class through
 *              which we can initiate a call, terminate a call etc.
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#ifndef MYCALL_H_
#define MYCALL_H_

#include "myThread.h"
#include "myStartCall.h"
#include "myStopCall.h"

/******************************************************************************
 * Name: CCall
 * Type: class
 * Argument: NA
 * Return type: NA
 * Description: This has publicly inherited the classes CThread to create a
 *              new thread, IStartCall interface for set a SIP address and
 *              start a new call, IStopCall interface to stop an ongoing call
 *****************************************************************************/
class CCall : /* 1 */ public CThread, \
			  /* 2 */ public IStartCall, \
			  /* 3 */ public IStopCall
{
public:
	/* Constructor */
	CCall();

	/* Virtual destructor */
	virtual ~CCall();

	/* Pure virtual implementation of IStartCall
	 * interface class, this function starts a
	 * new call */
	int StartCall(void);

	/* Pure virtual implementation of IStartCall
	 * interface class, this function sets the
	 * destination SIP address */
	int SetSIPAddress(char* p_SIPAddress);

	/* Pure virtual implementation of IStopCall
	 * interface call, this function terminates
	 * an ongoing call */
	int StopCall(void);

	/* This function return the current status
	 * of a call */
	LinphoneCallState GetStatus(void);

	/* Class initializer function */
	int Initialize(void);

	/**************************************************************************
	 * Name: GetStatus
	 * Type: static member function
	 * Argument: void*(calling thread object pointer)
	 * Return type: void
	 * Description: This function sets the current call status to class
	 *              data member
	 *************************************************************************/
	static void GetStatus(void* p_pVoid)
	{
		((CCall*)p_pVoid)->SetStatus(CCall::m_sStatus);
	}

	/**************************************************************************
	 * Name: CallStateChanged
	 * Type: static member function
	 * Arguments: LinphoneCore*()
	 *			  LinphoneCall*(current call)
	 *			  LinphoneCallState(current call state)
	 *			  const char*()
	 * Return type: void
	 * Description: This function store the current call status
	 *************************************************************************/
	static void CallStateChanged(/* 1 */ LinphoneCore *lc, \
								 /* 2 */ LinphoneCall *call, \
								 /* 3 */ LinphoneCallState cstate, \
								 /* 4 */ const char *msg)
	{
		CCall::m_sStatus = cstate;
	}

/* End public */

private:
	/* Initiate a new call */
	int InitiateCall(void);

	/* Terminate a call */
	int TerminateCall(void);

	/* Set current call status */
	int SetStatus(LinphoneCallState p_Status);

	/* Pure virtual function implementation of
	 * CThread class, newly created thread entry
	 * point */
	void ThreadEntry();

private:
	/* Call is in running
	 * state or not */
	bool m_bRunning;

	/* Call terminated or not */
	bool m_bCallInitiated;

	/* Destination SIP address, maximum size if
	 * MAX_SIP_ADDRESS characters */
	char m_szSIPAddress[MAX_SIP_ADDRESS];

	/* Hold current call status */
	LinphoneCallState m_Status;

	/* This is taken for to register
	 * CallStateChanged() function*/
	LinphoneCoreVTable m_vtable;

    LinphoneCore* m_pLinphoneCore;
    LinphoneCall* m_pLinphoneCall;

    /* Current call status */
    static LinphoneCallState m_sStatus;

}; /* class CCall */

#endif /* MYCALL_H_ */
