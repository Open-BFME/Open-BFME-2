// cl: /DNDEBUG /MD
//
// ?receivedAPong@PortNegotiationSchema@@QAE_NGGH@Z @0x005DBEEB 66B.
// PortNegotiationSchema indexed notify: bounds-checked element via rowed 0x005DB98E,
// Elem time smooth via rowed 0x005DB885, then list at +0x04 forEach with
// notify 0x005CB260. Evidence: callers 0x005A80CF; callees all rowed;
// neighbours 0x005DBE6A/0x005DC3C1; same forEach cast shape as
// Rva005DC3C1.cpp.
class Rva005DBE6AListener
{
public:
	virtual void notify(void *, int, int);
};

class Rva005DBE6AList
{
public:
	void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *arg, int value, int extra);
private:
	Rva005DBE6AListener **m_begin;
	Rva005DBE6AListener **m_end;
	Rva005DBE6AListener **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

struct Elem005DB98E
{
public:
	void rva005DB885(int a);
	void rva005DB8F7(float a, float b, float c);
};

class PortNegotiationSchema
{
public:
	void *peekPing(unsigned short x, unsigned short y);
	bool receivedAPong(unsigned short x, unsigned short y, int a);
	bool setPingStats(unsigned short x, unsigned short y, float a, float b, float c);
private:
	char m_pad00[4];
	Rva005DBE6AList m_list;
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
bool PortNegotiationSchema::setPingStats(unsigned short x, unsigned short y, float a, float b, float c)
{
	void *elem = peekPing(x, y);
	if (!elem)
		return false;
	((Elem005DB98E *)elem)->rva005DB8F7(a, b, c);
	m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva005CB260::rva005CB260, this, x, y);
	return true;
}
