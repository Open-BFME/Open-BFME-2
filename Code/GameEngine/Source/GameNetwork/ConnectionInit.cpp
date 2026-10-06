// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058BAA7@Connection@@QAEXPAUInitAddrs@@ABVUnicodeString@@H@Z @0x0058BAA7 181B Connection init with address block plus name plus id new NetCommandList plus latencies; evidence: StringBase wide set 0x00037150 NetCommandList new 0x10 ctor 0x0058B06A reset 0x0058B283x2 rep stosd 0xC8 frameGrouping 0x344; callers 0x004D1703 0x004D175B
#include "unicode_string.h"
struct InitAddrs { unsigned int a; unsigned int b; };
class NetCommandList
{
public:
	NetCommandList();
	void reset();
private:
	const void *m_vtable;
	void *m_first;
	void *m_last;
	void *m_lastMessageInserted;
};
class Connection
{
public:
	void rva0058BAA7(InitAddrs *addrs, const UnicodeString &name, int id);
private:
	int m_id;
	unsigned int m_openedTime;
	unsigned int m_unknown08;
	unsigned int m_addrA;
	unsigned int m_addrB;
	UnicodeString m_name;
	NetCommandList *m_list;
	unsigned int m_retryTime;
	float m_averageLatency;
	float m_latencies[200];
	int m_frameGrouping;
	int m_lastTimeSent;
	unsigned int m_unknown34C;
	int m_numRetries;
	unsigned int m_retryMetricsTime;
};
void Connection::rva0058BAA7(InitAddrs *addrs, const UnicodeString &name, int id)
{
	m_unknown08 = id;
	m_addrA = addrs->a;
	m_addrB = addrs->b;
	m_name.set(name);
	if (!m_list) {
		m_list = new NetCommandList;
		m_list->reset();
	}
	m_list->reset();
	m_lastTimeSent = 0;
	m_unknown34C = 0;
	m_numRetries = 0;
	m_retryMetricsTime = 0;
	m_frameGrouping = 1;
	for (int i = 0; i < 200; ++i)
		m_latencies[i] = 0.0f;
	m_id = -1;
	m_openedTime = 0;
	m_averageLatency = 0.0f;
}
