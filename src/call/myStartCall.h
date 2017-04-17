
/******************************************************************************
 * File name: myStartCall.h
 * Created on: 05-Apr-2017
 * Description: This is a C++ header file, this file contain an interface
 *              to set a SIP address and start a call
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#ifndef MYSTARTCALL_H_
#define MYSTARTCALL_H_

/* To inherit IGetStatus */
#include "myGetStatus.h"

/* Maximum length of a SIP address */
#define MAX_SIP_ADDRESS 500

/******************************************************************************
 * Name: IStartCall
 * Type: class
 * Argument: NA
 * Return type: NA
 * Description: An interface class to start a call and set SIP address
 *              also, this class has publicly inherited IGetStatus class
 *              because after operation we need to know the status
 *****************************************************************************/
class IStartCall : public IGetStatus
{
public:
	/* Pure virtual functions, set a user provided
	 * SIP address to start a call */
	virtual int SetSIPAddress(char* p_SIPAddress) = 0;

	/* Start a new call */
	virtual int StartCall(void) = 0;

}; /* class IStartCall */

#endif /* MYSTARTCALL_H_ */
