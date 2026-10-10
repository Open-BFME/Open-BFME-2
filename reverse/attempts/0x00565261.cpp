// ?rva00565261@LivingWorldCampaignAct@@QAEXXZ
// partial score=0.85 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// LivingWorldCampaignAct: three loops over record vectors that build one LivingWorld
// event object per record and hand it to the rowed appender 0x002B8AC0 (as
// Rva00211FA8Controls.cpp's rva00211396 does with BfmeRectVNH). Vector begin/end at
// +0x78/+0x7C and +0x84/+0x88 hold 16-byte records, +0x6C/+0x70 20-byte ones.
// Target evidence: bytes and callee relocations; the object classes are the rowed
// constructors 0x003FD3C7 (string-handle copy), 0x003FD348 (scaled value) and
// BfmeRectVNH 0x003FD498. Names are address-derived.
#include "ascii_string.h"

class ModuleData;
class Rva002B8AC0 { public: void rva002B8AC0(const ModuleData *); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	void *m_ref;
};

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned, char);
	virtual ~BfmeBaseVNH();
	virtual void handle();
	unsigned value04;
	char flag08;
};

class BfmeRectVNH : public BfmeBaseVNH
{
public:
	BfmeRectVNH(unsigned, const AsciiString &, char);
	AsciiString text0C;
};

class Rva003FD3EF : public BfmeBaseVNH
{
public:
	Rva003FD3EF(unsigned, const Rva0036CA00Str &, char);
	virtual ~Rva003FD3EF();
	Rva0036CA00Str m_0c;
};

class Rva003FD348 : public BfmeBaseVNH
{
public:
	Rva003FD348(unsigned, unsigned, char);
	virtual ~Rva003FD348();
	unsigned m_0c;
};

struct StrRecord16 { int m_00; unsigned m_w; Rva0036CA00Str m_s; char m_f; const Rva0036CA00Str &str() const { return m_s; } unsigned width() const { return m_w; } char flag() const { return m_f; } };
struct ScaleRecord16 { int m_00; unsigned m_w; char m_f; unsigned m_x; unsigned width() const { return m_w; } char flag() const { return m_f; } };
struct TextRecord20 { int m_00; unsigned m_w; AsciiString m_s; char m_f; const AsciiString &str() const { return m_s; } unsigned width() const { return m_w; } char flag() const { return m_f; } };

class LivingWorldCampaignAct
{
public:
	void rva00565148();
	void rva005651D2();
	void rva00565261();
private:
	unsigned textCount() const { return m_textEnd - m_textBegin; }
	unsigned strCount() const { return m_strEnd - m_strBegin; }
	unsigned scaleCount() const { return m_scaleEnd - m_scaleBegin; }

	char m_pad00[0x6C];
	TextRecord20 *m_textBegin;	// +0x6C
	TextRecord20 *m_textEnd;	// +0x70
	char m_pad74[4];
	StrRecord16 *m_strBegin;	// +0x78
	StrRecord16 *m_strEnd;		// +0x7C
	char m_pad80[4];
	ScaleRecord16 *m_scaleBegin;	// +0x84
	ScaleRecord16 *m_scaleEnd;	// +0x88
};

void LivingWorldCampaignAct::rva00565148()
{
	for (unsigned i = 0; i < strCount(); ++i) {
		StrRecord16 &r = m_strBegin[i];
		Rva003FD3EF *event = new Rva003FD3EF(r.width(), r.str(), r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}

void LivingWorldCampaignAct::rva005651D2()
{
	for (unsigned i = 0; i < textCount(); ++i) {
		TextRecord20 &r = m_textBegin[i];
		BfmeRectVNH *event = new BfmeRectVNH(r.width(), r.str(), r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}

void LivingWorldCampaignAct::rva00565261()
{
	for (unsigned i = 0; i < scaleCount(); ++i) {
		ScaleRecord16 &r = m_scaleBegin[i];
		Rva003FD348 *event = new Rva003FD348(r.width(), r.m_x, r.flag());
		((Rva002B8AC0 *)TheLivingWorldLogic)->rva002B8AC0((const ModuleData *)event);
	}
}
