#ifndef __CS_AUTOLOCK_H__
#define __CS_AUTOLOCK_H__

class CAutoLock
{
public:
	CAutoLock(CRITICAL_SECTION & mt) {m_pLock = &mt; EnterCriticalSection(m_pLock);}
	~CAutoLock(){LeaveCriticalSection(m_pLock);}
private:
	CRITICAL_SECTION * m_pLock;
};

#endif//__CS_AUTOLOCK_H__