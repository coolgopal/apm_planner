#include "callmanager.h"

#include <QDebug>

//char *CallManager::m_SIPAddress = "";
//CCall *CallManager::m_Call = NULL;
CallManager* CallManager::m_CallManager = NULL;

CallManager::CallManager()
{
    m_SIPAddress = "";
    m_Call = new CCall();
    m_Call->Initialize(CallManager::call_state_changed);
}

CallManager* CallManager::getInstance()
{
    if (m_CallManager == NULL)
        m_CallManager = new CallManager();

    return m_CallManager;
}

void CallManager::setSIPAddress(char* sip_address)
{
    m_SIPAddress = sip_address;
}

char* CallManager::getSIPAddress()
{
    return m_SIPAddress;
}

void CallManager::start_sip_call(void)
{
    qDebug() << "CallManager::start_sip_call => " << m_SIPAddress;

//    m_Call->SetSIPAddress("sip:swapan_gh@sip.linphone.org");
    m_Call->SetSIPAddress(m_SIPAddress);
    m_Call->StartCall();

//    emit call_status_update("Calling..");
}

void CallManager::end_sip_call(void)
{
    qDebug() << "CallManager::end_sip_call";

    m_Call->StopCall();
//    delete(m_Call);

    emit call_status_update("");
}

void CallManager::call_state_changed(LinphoneCore *lc, LinphoneCall *call, LinphoneCallState cstate, const char *msg)
{
    static char *call_state_text = "";
    switch (cstate) {
        case LinphoneCallOutgoingRinging:
            call_state_text = strdup("Ringing..");
            break;
        case LinphoneCallConnected:
            call_state_text = strdup("Connected..");
            break;
        case LinphoneCallEnd:
            call_state_text = strdup("Disconnected..");
            emit getInstance()->call_disconnected();
            break;
        case LinphoneCallError:
            call_state_text = strdup("Failed..");
            emit getInstance()->call_disconnected();
            break;
        default:
//            call_state_text = strdup("...");
            break;
    }

    emit getInstance()->call_status_update(call_state_text);
    qDebug() << "call_state_changed: " << call_state_text;
}
