// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00509E43@Made002CC8A4@@UAE_NHPAVObject@@@Z, retail 0x00509E43..
// 0x00509F3A (247 bytes, RET 8): slot 1 of Made002CC8A4's vtable (the nugget
// parseMetaImpactNugget news). It rejects a missing object, one whose
// template carries +0x113 bit 0x40, +0x108 bit 0x80 or +0x114 bit 0x2000, and
// one the rowed Object 0x0028DB0F test refuses (told whether this nugget's
// +0x144 value is non-zero). When the template's +0x610 value scaled by 0.2
// reaches this nugget's +0x128 limit, only a non-zero +0x144 with template
// +0x11F bit 0x80 passes. An object whose +0x274 link's template lacks the
// 0x2000 bit is rejected; a dead object (+0x438 bit 0) passes only while its
// +0x254 body's slot-16 frame has not passed TheGameLogic's frame, a live one
// only without this nugget's +0x154 flag. The rest is decided by the pinned
// 0x005075D6 check. WorldBuilder's twin is unnamed.

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Rva00509E43Template
{
	unsigned char m_pad000[0x108];
	unsigned char m_flags108;				// +0x108
	unsigned char m_pad109[0x113 - 0x109];
	unsigned char m_flags113;				// +0x113
	unsigned int m_flags114;				// +0x114
	unsigned char m_pad118[0x11F - 0x118];
	unsigned char m_flags11F;				// +0x11F
	unsigned char m_pad120[0x610 - 0x120];
	float m_610;							// +0x610
};

class Rva00509E43Body
{
public:
#define V(n) virtual void v##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual unsigned int frame();			// slot 16
};

struct Rva00509E43Link
{
	unsigned char m_pad00[0x04];
	Rva00509E43Template *m_template04;
};

class Object
{
public:
	bool rva0028DB0F(bool flag) const;

	unsigned char m_pad000[0x04];
	Rva00509E43Template *m_template04;		// +0x04
	unsigned char m_pad008[0x254 - 0x08];
	Rva00509E43Body *m_body254;				// +0x254
	unsigned char m_pad258[0x274 - 0x258];
	Rva00509E43Link *m_link274;				// +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_status438;				// +0x438
};

// The pinned check shared with the rowed slot 0x00508925.
class Rva00508925
{
public:
	unsigned char rva005075D6(int a, int b);
};

class Made002CC8A4
{
public:
	virtual void v0();
	virtual bool rva00509E43(int a, Object *obj);

private:
	unsigned char m_pad004[0x128 - 0x04];
	float m_limit128;						// +0x128
	unsigned char m_pad12C[0x144 - 0x12C];
	float m_144;							// +0x144
	unsigned char m_pad148[0x154 - 0x148];
	bool m_154;								// +0x154
};

bool Made002CC8A4::rva00509E43(int a, Object *obj)
{
	if (!obj)
		return false;
	Rva00509E43Template *tmpl = obj->m_template04;
	if (!(tmpl->m_flags113 & 0x40) && !(tmpl->m_flags108 & 0x80) && !(tmpl->m_flags114 & 0x2000))
	{
		bool nonZero = m_144 != 0.0f;
		if (!obj->rva0028DB0F(nonZero))
		{
			tmpl = obj->m_template04;
			if (!(tmpl->m_610 * 0.2f >= m_limit128) || (nonZero && (tmpl->m_flags11F & 0x80)))
			{
				if (!obj->m_link274 || (obj->m_link274->m_template04->m_flags114 & 0x2000))
				{
					if (obj->m_status438 & 1)
					{
						Rva00509E43Body *body = obj->m_body254;
						if (!body || body->frame() < TheGameLogic->getFrame())
							return false;
					}
					else if (m_154)
						return false;
					return reinterpret_cast<Rva00508925 *>(this)->rva005075D6(a, (int)obj);
				}
			}
		}
	}
	return false;
}
