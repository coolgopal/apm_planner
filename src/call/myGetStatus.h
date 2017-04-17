
/******************************************************************************
 * File name: myGetStatus.h
 * Created on: 05-Apr-2017
 * Description: This is a c++ header file and this file
 *              contain an interface of getting current call status
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#ifndef MYGETSTATUS_H_
#define MYGETSTATUS_H_

/* To use LinphoneCallState */
#include "linphonecore.h"

/******************************************************************************
 * Name: IGetStatus
 * Type: class
 * Argument: NA
 * Return type: NA
 * Description: An interface class for knowing the current call status
 *****************************************************************************/
class IGetStatus
{
public:
	/* Pure virtual function */
	virtual LinphoneCallState GetStatus(void) = 0;

}; /* class IGetStatus */

#endif /* MYGETSTATUS_H_ */
