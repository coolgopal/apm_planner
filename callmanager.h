#ifndef CALLMANAGER_H
#define CALLMANAGER_H


#include "call/myCall.h"


class CallManager
{
public:
    static char *m_SIPAddress;


    CallManager();

    static void start_sip_call(void);
    static void end_sip_call(void);

private:
    static CCall *m_Call;

};

#endif // CALLMANAGER_H
