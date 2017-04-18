#include "callmanager.h"

#include <QDebug>

char *CallManager::m_SIPAddress = "";
CCall *CallManager::m_Call = NULL;

CallManager::CallManager()
{

}

void CallManager::start_sip_call(void)
{
    qDebug() << "CallManager::start_sip_call => " << m_SIPAddress;

    if (m_Call == NULL)
    {
        m_Call = new CCall();
        m_Call->Initialize();
    }
//    m_Call->SetSIPAddress("sip:swapan_gh@sip.linphone.org");
    m_Call->SetSIPAddress(m_SIPAddress);
    m_Call->StartCall();
}

void CallManager::end_sip_call(void)
{
    qDebug() << "CallManager::end_sip_call";

    m_Call->StopCall();
//    delete(m_Call);
}
