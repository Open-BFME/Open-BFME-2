// cl: /DNDEBUG /MD
//
// ?receivedAPong@PortNegotiationSchema@@QAE_NGGH@Z @0x005DBEEB 66B.
// PortNegotiationSchema indexed notify: bounds-checked element via rowed 0x005DB98E,
// Elem time smooth via rowed 0x005DB885, then list at +0x04 forEach with
// notify 0x005CB260. Evidence: callers 0x005A80CF; callees all rowed;
// neighbours 0x005DBE6A/0x005DC3C1; same forEach cast shape as
// Rva005DC3C1.cpp.
class GameSlot;

struct Elem005DB98E
{
public:
	void rva005DB885(int a);
	void rva005DB8F7(float a, float b, float c);
	int m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	float m_0C; // +0x0C
	unsigned long m_10; // +0x10
};

class Rva005DBE6AListener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva005DBDF7Call
{
	void (Rva005DBE6AListener::*notify)(void *, int, int);
	void *arg;
	int value;
	int extra;
};

class Rva005DBE6AList
{
public:
	void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *arg, int value, int extra);
	void apply(const Rva005DBDF7Call &call);
private:
	Rva005DBE6AListener **m_begin; // +0x00
	Rva005DBE6AListener **m_end; // +0x04
	Rva005DBE6AListener **m_capacity; // +0x08
	unsigned int m_index; // +0x0C
};

class PortNegotiationSchema
{
public:
	void* peekPing(unsigned short x, unsigned short y);
	int GetConnectionState(unsigned short x, unsigned short y);
	bool IsConflictingWithProceedingNegotiation(unsigned short x);
	bool rva005DBA9C(bool flag);
	int getTimeToSendPing(unsigned short idx);
	int getActionID(unsigned short x, unsigned short y);
	bool isConnectionDone(unsigned short first, unsigned short second);
	bool isRetryConnectingOverLimit(unsigned short first, unsigned short second);
	bool receivedAPong(unsigned short x, unsigned short y, int a);
	bool setPingStats(unsigned short x, unsigned short y, float a, float m_pingsSent, float pongsReceived);
	bool sentAPingPacket(unsigned short x, unsigned short y);
	void handleNegotiationResult(unsigned short a, unsigned short b, int expected, int newVal);
	char m_pad00[0x4];
private:
	Rva005DBE6AList m_list; // +0x04
	unsigned short m_cur; // +0x14
	char m_pad16[0x2];
	int m_arr2[64]; // +0x18
	int m_arr118[64]; // +0x118
	Elem005DB98E m_arr[64]; // +0x218
	int m_718[8]; // +0x718
	char m_pad738[0x100];
	unsigned short m_retries[64]; // +0x838
	GameSlot **m_slots; // +0x8B8
};

struct Rva005DBDF7Call;


class Rva005CB260
{
public:
	void rva005CB260();
};





bool PortNegotiationSchema::receivedAPong(unsigned short x, unsigned short y, int a)
{
	void *elem = peekPing(x, y);
	if (!elem)
		return false;
	((Elem005DB98E *)elem)->rva005DB885(a);
	m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva005CB260::rva005CB260, this, x, y);
	return true;
}

// ?setPingStats@PortNegotiationSchema@@QAE_NGGMMM@Z @0x005DBE95 86B: float triple setter
// sibling of 0x005DBEEB with rowed 0x005DB8F7 plus same forEach.
bool PortNegotiationSchema::setPingStats(unsigned short x, unsigned short y, float a, float m_pingsSent, float pongsReceived)
{
	void *elem = peekPing(x, y);
	if (!elem)
		return false;
	((Elem005DB98E *)elem)->rva005DB8F7(a, m_pingsSent, pongsReceived);
	m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva005CB260::rva005CB260, this, x, y);
	return true;
}
