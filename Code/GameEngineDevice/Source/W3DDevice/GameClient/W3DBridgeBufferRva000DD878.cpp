// cl: /DNDEBUG /MD /EHsc
// ?rva000DD878@W3DBridgeBuffer@@QAEXH@Z 0x000DD878 64B W3DBridgeBuffer method ret 4 one unused int arg
// evidence: neighbours 0x000DD816 clearBridge and 0x000DD8B8 allocateBridgeBuffers same TU flags
// caller 0x000DF745 49B forwards its first arg and reads D7B6 D7B5 C count layout stride 0x114
// layout: bridges[200] at +0x10 size 0x114 visible at +0x104 count at +0xD7B0 flags at +0xD7B5 +0xD7B6 size 0xD7C0

typedef int Int;

class W3DBridge
{
public:
	unsigned char m_pad[0x104];
	unsigned char m_visible;
	unsigned char m_pad2[0x114 - 0x105];
};

class W3DBridgeBuffer
{
public:
	void rva000DD878(int dummy);
private:
	void *m_vertexBridge;
	void *m_indexBridge;
	int m_08;
	int m_curNumBridgeIndices;
	W3DBridge m_bridges[200];
	int m_numBridges;
	unsigned char m_padD7B4;
	unsigned char m_flagD7B5;
	unsigned char m_flagD7B6;
	unsigned char m_padTail[0xD7C0 - 0xD7B7];
};

void W3DBridgeBuffer::rva000DD878(int dummy)
{
	(void)dummy;
	m_flagD7B6 = m_flagD7B5;
	for (Int i = 0; i < m_numBridges; ++i)
	{
		unsigned char cur = m_bridges[i].m_visible;
		m_bridges[i].m_visible = 1;
		if (cur != 1)
			m_flagD7B6 = 1;
	}
}
