// cl: /DNDEBUG /MD
// ?peekPing@PortNegotiationSchema@@QAEPAXGG@Z 0x005DB98E 46B
// Bounds-checked 2D index into 20B elements at +0x218.
// Evidence: callers 0x5A6D0A 0x5DB570 etc.; unblocks 8.
struct Elem005DB98E
{
	char m_data[20];
};

class PortNegotiationSchema
{
	char m_pad0[0x18];
	int m_arr2[81];
	char m_pad1[0x218 - 0x18 - 81 * 4];
	Elem005DB98E m_arr[81];
public:
	void* peekPing(unsigned short x, unsigned short y);
	int GetConnectionState(unsigned short x, unsigned short y);
	bool rva005DBA60(unsigned short x);
};

void* PortNegotiationSchema::peekPing(unsigned short x, unsigned short y)
{
	if (x > 8)
		return 0;
	if (y > 8)
		return 0;
	return &m_arr[y + x * 8];
}

int PortNegotiationSchema::GetConnectionState(unsigned short x, unsigned short y)
{
	if (x > 8)
		return 0;
	if (y > 8)
		return 0;
	return m_arr2[y + x * 8];
}

// The conflict scan definition is now co-located with its 5DC586 consumer
// in NATUpdateBfme.cpp so the compiler observes its ECX-preserving contract.
