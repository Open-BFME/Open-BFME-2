// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva0048F365Helper@AssaultTransportAIUpdate@@QAEXXZ, retail 0x0048F365
// (93 bytes). Loop-zeroing helper over three count-sized arrays plus scalar
// tails: clears the dword run at +0x3E8 plus the byte runs at +0x410 and
// +0x41A for the +0x43C count, zeroes the count, zeroes the three floats at
// +0x424/+0x428/+0x42C, zeroes the ints at +0x430/+0x434/+0x438 plus the
// byte at +0x440. Called at member position by the behavior ctor plus the
// dispatcher methods. Row supersedes the helper pin.

class AssaultTransportAIUpdate
{
public:
	void Rva0048F365Helper();

private:
	unsigned char m_pad00[0x3E8];
	int m_array3E8[10];
	unsigned char m_array410[10];
	unsigned char m_array41A[10];
	float m_float424;
	float m_float428;
	float m_float42C;
	int m_int430;
	int m_int434;
	int m_int438;
	int m_count43C;
	unsigned char m_byte440;
};

void AssaultTransportAIUpdate::Rva0048F365Helper()
{
	for (int i = 0; i < m_count43C; ++i)
	{
		m_array3E8[i] = 0;
		m_array410[i] = 0;
		m_array41A[i] = 0;
	}
	m_count43C = 0;
	float *floats424 = &m_float424;
	floats424[0] = 0.0f;
	floats424[1] = 0.0f;
	floats424[2] = 0.0f;
	m_int430 = 0;
	m_int434 = 0;
	m_int438 = 0;
	m_byte440 = 0;
}
