// ?init@OrnamentData@@QAEXXZ
// partial score=0.96 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /arch:SSE
extern float g_ornamentDefaultFloat;

struct OrnamentData
{
	void init();
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
};

void OrnamentData::init()
{
	float f = g_ornamentDefaultFloat;
	OrnamentData * const self = this;
	const int one = 1;
	self->m_0C &= 0;
	self->m_1C |= -1;
	self->m_20 |= -1;
	self->m_24 &= 0;
	self->m_00 = f;
	self->m_04 = f;
	self->m_08 = f;
	self->m_10 = self->m_14 = self->m_18 = one;
}
