// Donor: BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/Common/BfmeConv2037.cpp (ordinary C++ reference).
// Target boundary: preceding RET4 ends0x55B9BD; this body ends RET0x55BA3C.
// Native index +AC selects 16-byte keys from +C; next time +1C minus +C
// is an unsigned delta. Native x/y/z slots +94/+98/+9C produce +A0/+A4/+A8
// rates, or zero rates when the next time is zero. Retail constants are 1.0
// at0xBBB8D8 and the compiler's unsigned-to-float correction at0xBC26EC.
// Owner, key capacity and original method name remain unproven. The local
// eight-key view is donor structure plus target offsets, never instantiated.
// Neighbor parser placement alone is not evidence of particle-system identity.
// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD


class Rva0055B9BDKey
{
public:
	unsigned int m_TimeEN;
	float m_XEN;
	float m_YEN;
	float m_ZEN;
};

class Rva0055B9BDView
{
public:
	void rva0055B9BD();

	unsigned char m_HeadEN[0xc];
	Rva0055B9BDKey m_KeysEN[8];
	unsigned char m_PadEN[8];
	float m_PxEN;
	float m_PyEN;
	float m_PzEN;
	float m_VxEN;
	float m_VyEN;
	float m_VzEN;
	int m_IndexEN;
};

// ?rva0055B9BD@Rva0055B9BDView@@QAEXXZ
void Rva0055B9BDView::rva0055B9BD()
{
	int i = m_IndexEN;
	unsigned int dt = m_KeysEN[i + 1].m_TimeEN;

	if (dt == 0)
	{
		m_VxEN = 0.0f;
		m_VyEN = 0.0f;
		m_VzEN = 0.0f;
		return;
	}

	dt -= m_KeysEN[i].m_TimeEN;

	float inv = 1.0f / (float)dt;

	m_VxEN = (m_KeysEN[i].m_XEN - m_PxEN) * inv;
	m_VyEN = (m_KeysEN[i].m_YEN - m_PyEN) * inv;
	m_VzEN = (m_KeysEN[i].m_ZEN - m_PzEN) * inv;
}
