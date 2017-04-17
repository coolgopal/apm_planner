
/******************************************************************************
 * File name: myStopCall.h
 * Created on: 05-Apr-2017
 * Description: This is a C++ header file, this file contain an interface
 *              to stop a call
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#ifndef MYSTOPCALL_H_
#define MYSTOPCALL_H_

/* To inherit public IGetStatus */
#include "myGetStatus.h"

/******************************************************************************
 * Name: IStopCall
 * Type: class
 * Argument: NA
 * Return type: NA
 * Description: An interface class to stop a call, this class has publicly
 *              inherited IGetStatus class because after operation we need
 *              to know the status
 *****************************************************************************/
class IStopCall : public IGetStatus
{
public:
	/* Pure virtual function */
	virtual int StopCall(void) = 0;

}; /* class IStopCall */

#endif /* MYSTOPCALL_H_ */
