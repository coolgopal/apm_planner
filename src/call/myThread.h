
/******************************************************************************
 * File name: myThread.h
 * Created on: 05-Apr-2017
 * Description: This is a C++ header file, this file contain an abstract
 *              thread class(CThread) and must have to define ThreadEntry()
 *              function in derived class as main thread entry point
 * Author: Anonymous
 * Modified by:
 * Modify:
 * Modified on:
 *****************************************************************************/

#ifndef MYTHREAD_H_
#define MYTHREAD_H_

#include <iostream>

/* To use thread APIs */
#include <pthread.h>

/* To print any failure status
 * during thread creation*/
using namespace std;

/******************************************************************************
 * Name: CThread
 * Type: class
 * Argument: NA
 * Return type: NA
 * Description: An abstract base class for thread creation, ThreadEntry()
 *              shall be the main thread entry point in derived class if
 *              defined
 *****************************************************************************/
class CThread
{
public:
	/* Constructor */
	CThread();

	/* Virtual destructor */
	virtual ~CThread();

	/* Create thread */
	void StartThread(void);

/* End public */

protected:
	/* Pure virtual function, main thread
	 * function/main new thread entry point */
	virtual void ThreadEntry(void) = 0;

/* End protected */

private:
	/**************************************************************************
	 * Name: InternalThreadEntry
	 * Type: Private static member function
	 * Argument: void*, Calling thread object pointer(this)
	 * Return type: void*, always NULL
	 * Description: This function pointer has been provided to
	 *              pthread_create() function as third argument
	 *************************************************************************/
	static void* InternalThreadEntry(void* p_pThis)
	{
		/* call CThread::ThreadEntry() function,
		 * which is the main thread function in
		 * derived class */
		((CThread*)p_pThis)->ThreadEntry();

		/* Return always NULL */
		return NULL;

	} /* static void* InternalThreadEntry(void* pThis) */

/* End private */

private:
	/* Hold newly created thread ID */
	pthread_t m_ThreadId;

	/* To set thread attribute */
	pthread_attr_t m_Attr;

/* End private */

}; /* class CThread */

#endif /* MYTHREAD_H_ */
