// ?rva0037E18A@Rva0037E270@@QAEHPAVObject@@0@Z
// partial score=0.96 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
// ?rva0037E18A@Rva0037E270@@QAEHPAVObject@@0@Z @0x0037E18A 115B. Scaled value
// via template lookup: float mult from g_Va00BBB8D8 overwritten by virtual slot
// 0x70 of Object::rva0028BC94 result using bool +0xA0, then ThingTemplate pin
// 0x0033A69A on Rva002D06CA rowed 0x002D06CA result of AsciiString +0xD4.
// Evidence: callees rowed 0x0028BC94 0x002D06CA plus pin 0x0033A69A, globals
// g_Va00BBB8D8 g_009FF000, layout from neighbour Rva0037E270Lookup.cpp.
#include "ascii_string.h"
class Object
{
public:
	void *rva0028BC94();
};
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
class ThingTemplate
{
public:
	int rva0033A69A(Object *o, int a, int b) const;
};
class Rva0037E18AIface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual float v28(unsigned char b);
};
extern float g_Va00BBB8D8;
extern Rva002D06CA *g_009FF000;
class Rva0037E270
{
	char m_pad00[0x94];
	int m_94;
	char m_pad98[4];
	int m_9C;
	unsigned char m_A0;
	char m_padA1[0xD4 - 0xA1];
	AsciiString m_str;
public:
	int rva0037E18A(Object *a, Object *b);
};
// ?rva0037E18A@Rva0037E270@@QAEHPAVObject@@0@Z present-unmatched
int Rva0037E270::rva0037E18A(Object *a, Object *b)
{
	float mult = g_Va00BBB8D8;
	if (b != 0) {
		void *found = b->rva0028BC94();
		if (found != 0)
			mult = ((Rva0037E18AIface *)found)->v28(*(volatile unsigned char *)&m_A0);
	}
	Rva002D06CA *mgr = g_009FF000;
	void *def = mgr->rva002D06CA(&m_str);
	if (def == 0)
		return 0;
	int v = ((ThingTemplate *)def)->rva0033A69A(a, 0, m_94);
	return (int)((float)v * mult);
}
