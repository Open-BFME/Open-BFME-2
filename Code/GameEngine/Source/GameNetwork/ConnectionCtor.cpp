// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0Connection@@QAE@XZ, retail 0x0058BDA0 90 bytes.
// Connection ctor via BFME1 donor Code/GameEngine/Source/GameNetwork/Connection.cpp.
// Evidence: 0xC8 rep stosd for 200 latencies, 0x7D0 retryTime, 0x344 frameGrouping,
// timeGetTime-adjacent layout with +0x350 numRetries +0x354 retryMetricsTime,
// caller 0x004D16DB in 0x004D1616. m_averageLatency after frameGrouping for retail movss order.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef long time_t;
typedef float Real;
#define CONNECTION_LATENCY_HISTORY_LENGTH 200
class NetCommandRef;
class ConnectionNetCommandList
{
public:
	NetCommandRef *getFirstMessage() { return m_first; }
private:
	void *m_vptr;
	NetCommandRef *m_first;
};
struct ConnectionBlock0C
{
	ConnectionBlock0C() : m_unknown00(0), m_unknown04(0), m_unknown08(0) {}
	UnsignedInt m_unknown00;
	UnsignedShort m_unknown04;
	UnsignedInt m_unknown08;
};
class Connection
{
public:
	Connection();
private:
	Int m_id;
	UnsignedInt m_openedTime;
	UnsignedInt m_unknown08;
	ConnectionBlock0C m_block0C;
	ConnectionNetCommandList *m_netCommandList;
	time_t m_retryTime;
	Real m_averageLatency;
	Real m_latencies[CONNECTION_LATENCY_HISTORY_LENGTH];
	time_t m_frameGrouping;
	time_t m_lastTimeSent;
	UnsignedInt m_unknown34C;
	Int m_numRetries;
	UnsignedInt m_retryMetricsTime;
};

Connection::Connection()
{
	m_numRetries = 0;
	m_retryMetricsTime = 0;
	m_unknown08 = 0;
	m_netCommandList = 0;
	m_lastTimeSent = 0;
	m_unknown34C = 0;
	m_openedTime = 0;
	m_retryTime = 2000;
	m_frameGrouping = 1;
	m_averageLatency = 0.0f;
	m_id = -1;
	for (Int i = 0; i < CONNECTION_LATENCY_HISTORY_LENGTH; ++i) {
		m_latencies[i] = 0.0f;
	}
}
