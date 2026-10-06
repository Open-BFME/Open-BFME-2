// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?doRetryMetrics@Connection@@IAEXXZ, retail 0x0058BA7B 44 bytes.
// Connection::doRetryMetrics via BFME1 donor Code/GameEngine/Source/GameNetwork/Connection.cpp
// (same body) and Connection_doSend.cpp. Evidence: timeGetTime IAT call,
// 10000ms window at +0x354, m_numRetries zero at +0x350, static numSeconds
// at 0x00A063A8, caller 0x0058BC71 in 0x0058BB5C.
typedef int Int;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Connection
{
protected:
	void doRetryMetrics();
private:
	Int m_id;
	unsigned long m_openedTime;
	char _pad[0x350 - 8];
	Int m_numRetries;
	unsigned long m_retryMetricsTime;
};

void Connection::doRetryMetrics()
{
	static Int numSeconds = 0;
	unsigned long curTime = timeGetTime();
	if ((curTime - m_retryMetricsTime) > 10000) {
		m_retryMetricsTime = curTime;
		++numSeconds;
		m_numRetries = 0;
	}
}
