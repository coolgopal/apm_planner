
/******************************************************************************
 * File name: myThread.cpp
 * Created on: 05-Apr-2017
 * Description: This is a C++ class member function definition file, contain
 *              member function definition of CThread class
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#include "myThread.h"

/******************************************************************************
 * Name: CThread
 * Type: Constructor
 * Argument: NA
 * Return type: NA
 * Description: Initialize default value to data members
 *****************************************************************************/
CThread::CThread()
: m_ThreadId(0)
{

}

/******************************************************************************
 * Name: CThread
 * Type: Virtual destructor
 * Argument: NA
 * Return type: NA
 * Description: deallocate memory or assign default value to data member
 *****************************************************************************/
CThread::~CThread()
{
	m_ThreadId = 0;
}

/******************************************************************************
 * Name: StartThread
 * Type: Public member function
 * Argument: void
 * Return type: void
 * Description:
 *****************************************************************************/
void CThread::StartThread(void)
{
	/* Status of every thread creation steps */
	int iStatus = 0;

	do
	{
		iStatus = 0;

		/* Initialize thread attribute with default attributes */
		iStatus = pthread_attr_init(&m_Attr);

		/* Check successfully initialized or not */
		if(0 != iStatus)
		{
			/* Failed to initialized thread attribute with
			 * default attribute, notify user about failure
			 * with line no and file name */
			cout << "pthread_attr_init() failed, line no : " \
					<< __LINE__ << ", file : " << __FILE__ << endl;

			/* We will not go for next steps,
			 * terminate the loop */
			break;
		}

		iStatus = 0;

		/* Set detached state to the thread */
		iStatus = pthread_attr_setdetachstate(&m_Attr, PTHREAD_CREATE_DETACHED);

		/* Check whether able to set detached state or not */
		if(0 != iStatus)
		{
			/* Failed to set detached state to thread, notify user
			 * about failure with line no and file name */
			cout << "pthread_attr_setdetachstate() failed, line no : " \
					<< __LINE__ << ", file : " << __FILE__ << endl;

			/* We will not go for next steps,
			 * terminate the loop */
			break;
		}

		iStatus = 0;

		/* Create a new thread, if success then new thread execution will
		 * start from InternalThreadEntry() function with 'this' as argument*/
		iStatus = pthread_create(&m_ThreadId, &m_Attr, CThread::InternalThreadEntry, this);

		if(0 != iStatus)
		{
			/* Failed to create a new thread, notify user about failure
			 * with line no and file name */
			cout << "pthread_create() failed, line no : " \
					<< __LINE__ << ", file : " << __FILE__ << endl;

			/* We will not go for next steps,
			 * terminate the loop */
			break;
		}

		iStatus = 0;

		/* Destroy previous thread attribute */
		iStatus = pthread_attr_destroy(&m_Attr);

		/* Check for successful destruction */
		if(0 != iStatus)
		{
			/* Failed to destroy, notify user about failure
			 * with line no and file name */
			cout << "pthread_attr_destroy() failed, line no : " \
					<< __LINE__ << ", file : " << __FILE__ << endl;

			/* We will not go for next steps,
			 * terminate the loop */
			break;
		}

	} while(false);

} /* void CThread::StartThread(void) */

