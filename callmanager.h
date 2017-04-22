#ifndef CALLMANAGER_H
#define CALLMANAGER_H


#include "call/myCall.h"

#include <QObject>


class CallManager : public QObject
{
    Q_OBJECT

public:
    CallManager();
//    virtual ~CallManager() {};

    static CallManager* getInstance();

    void setSIPAddress(char* sip_address);
    char* getSIPAddress();
    void start_sip_call(void);
    void end_sip_call(void);
    static void call_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg);

signals:
    void call_status_update(const char* call_status);
    void call_disconnected();

private:
    char     *m_SIPAddress;
    CCall    *m_Call;
    static CallManager* m_CallManager;

};

#endif // CALLMANAGER_H
