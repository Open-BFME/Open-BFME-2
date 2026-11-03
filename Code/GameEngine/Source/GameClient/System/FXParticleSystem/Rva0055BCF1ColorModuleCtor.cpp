// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva0055BCF1@@QAE@IPBUColorModuleTemplate@@@Z, retail 0x0055BCF1 (504 bytes).
// FXParticleSystem colour module constructor, the colour sibling of the
// rowed alpha module constructor 0x0055B52E. Sole caller 0x003AC96F (after a
// 0xB0-byte allocation; the caller then stores its own primary vtable).
// Target evidence:
//  - bases: rowed 0x0055BCD2 (vtables at +0 and +8) then the rowed colour
//    key block 0x0055BC8B at +0x0C (eight 16-byte RGB keyframes from +0x10
//    and a colour scale at +0x90) under EH states 0 and 1; this class then
//    stores vtables 0x0081D17C (+0) 0x0081C780 (+8) and 0x0081D194 (+0x0C);
//  - copies the source's eight keyframes (+0x20) and for keys 1..6 when the
//    source colour scale variable (+0xA0; low +0xA4 high +0xA8) is not zero
//    adds one rowed GameClientRandomVariable::getValue 0x002341A1 sample to
//    each non-zero channel clamped to 0..1;
//  - colour scale +0x90 from one more sample; current colour +0x94 from key 0;
//    target key +0xAC = 1; then the rowed rate update 0x0055B9BD.
// BFME 1's colour module constructor (Rva005EFB10ColorModuleCtor.cpp there)
// is the same without the per-key variation.

class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];

#include "../../../../../Libraries/Include/Lib/RGBColor.h"

struct RGBColorKeyframe
{
	RGBColor color;
	unsigned int frame;
};

#include "../../../../Include/GameClient/GameClientRandomVariable.h"

struct ColorModuleTemplate
{
	char m_pad00[0x20];
	RGBColorKeyframe m_colorKey[8]; // +0x20
	GameClientRandomVariable m_colorScale; // +0xA0
};

class __declspec(novtable) Rva0055BCD2Part0
{
public:
	virtual ~Rva0055BCD2Part0() {}
	void *m_system; // +0x04
};

class SecondaryModuleBase
{
public:
	virtual void slot00() = 0;
};

class __declspec(novtable) Rva0055BCD2 : public Rva0055BCD2Part0, public SecondaryModuleBase
{
public:
	Rva0055BCD2(unsigned int a);
	~Rva0055BCD2()
	{
		unsigned char *categoryModuleInfo = this ? (unsigned char *)this + 8 : 0;
		*(volatile unsigned int *)categoryModuleInfo = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@");
		*(volatile unsigned int *)this = (unsigned int)__identifier("??_7V3Vt01111D90@@6B@");
	}
};

class Rva0055BC8B : public Snapshot
{
public:
	Rva0055BC8B();
	virtual ~Rva0055BC8B() {}
	RGBColorKeyframe m_colorKey[8]; // +0x04
	float m_colorScale; // +0x84
};

class Rva0055B9BDView
{
public:
	void rva0055B9BD();
};

class Rva0055BCF1 : public Rva0055BCD2, public Rva0055BC8B
{
public:
	Rva0055BCF1(unsigned int system, const ColorModuleTemplate *src);
	RGBColor m_color; // +0x94
	RGBColor m_colorRate; // +0xA0
	int m_colorTargetKey; // +0xAC
};

Rva0055BCF1::Rva0055BCF1(unsigned int system, const ColorModuleTemplate *src)
	: Rva0055BCD2(system)
{
	for (int i = 0; i < 8; ++i)
	{
		m_colorKey[i] = src->m_colorKey[i];
		if (i > 0 && i < 7 && (src->m_colorScale.m_low != 0.0f || src->m_colorScale.m_high != 0.0f))
		{
			if (m_colorKey[i].color.red != 0.0f)
			{
				m_colorKey[i].color.red += src->m_colorScale.getValue();
				if (m_colorKey[i].color.red < 0.0f)
					m_colorKey[i].color.red = 0.0f;
				if (m_colorKey[i].color.red > 1.0f)
					m_colorKey[i].color.red = 1.0f;
			}
			if (m_colorKey[i].color.green != 0.0f)
			{
				m_colorKey[i].color.green += src->m_colorScale.getValue();
				if (m_colorKey[i].color.green < 0.0f)
					m_colorKey[i].color.green = 0.0f;
				if (m_colorKey[i].color.green > 1.0f)
					m_colorKey[i].color.green = 1.0f;
			}
			if (m_colorKey[i].color.blue != 0.0f)
			{
				m_colorKey[i].color.blue += src->m_colorScale.getValue();
				if (m_colorKey[i].color.blue < 0.0f)
					m_colorKey[i].color.blue = 0.0f;
				if (m_colorKey[i].color.blue > 1.0f)
					m_colorKey[i].color.blue = 1.0f;
			}
		}
	}
	m_colorScale = src->m_colorScale.getValue();
	m_color = m_colorKey[0].color;
	m_colorTargetKey = 1;
	((Rva0055B9BDView *)this)->rva0055B9BD();
}
