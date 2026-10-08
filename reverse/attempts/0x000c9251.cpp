// ?init@OrnamentData@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// OrnamentData envelope init: the 53-byte leaf that W3DLaserDrawModuleData and
// FadeAndDieOrnamentUpdate call at +0x4C and +0x28.
// ?init@OrnamentData@@QAEXXZ @0x000C9251

extern float g_Va00BBB8D8;

struct OrnamentData
{
	void init() throw();
	float m_f00, m_f04, m_f08;
	int m_reset0C;
	int m_i10, m_i14, m_i18;
	int m_i1C, m_i20;
	int m_reset24;
};

// ?init@OrnamentData@@QAEXXZ @0x000C9251
void OrnamentData::init() throw()
{
	float one = g_Va00BBB8D8;
	OrnamentData *self = this;
	int ione = 1;
	self->m_reset0C = 0;
	self->m_i1C = -1;
	self->m_i20 = -1;
	self->m_reset24 = 0;
	self->m_f00 = one;
	self->m_f04 = one;
	self->m_f08 = one;
	self->m_i10 = ione;
	self->m_i14 = ione;
	self->m_i18 = ione;
}
