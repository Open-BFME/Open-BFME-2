// ?rva000B7F04@Rva000B7F04@@QAE_NPBVAsciiString@@PAURva000B7F04Out@@@Z
// partial score=0.85 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// ?rva000B7F04@Rva000B7F04@@QAE_NPBVAsciiString@@PAURva000B7F04Out@@@Z
// @0x000B7F04 228B: string-keyed matrix fetch. Resolves the input through
// inlined AsciiString::str, queries slot 50 of the +0x44 provider; a null
// result fills the out record with a 3x4 identity (1.0 at 0/5/10) and
// returns false, otherwise slot 51 fills a stack record (returned
// pointer reused) copied field-by-field to the caller for true. Honest
// address-derived names; boundary verified (frame at 0xB7F04, ret 8).
#include "ascii_string.h"

struct Rva000B7F04Out
{
	float f00;
	int m04[11];
};

class Rva000B7F04Src
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual int vslot050(const char *s);
	virtual Rva000B7F04Out *vslot051(Rva000B7F04Out *out, int v);
};

class Rva000B7F04
{
public:
	bool rva000B7F04(const AsciiString *in, Rva000B7F04Out *out);

private:
	char m_pad00[0x44];
	Rva000B7F04Src *m_44;
};

// ?rva000B7F04@Rva000B7F04@@QAE_NPBVAsciiString@@PAURva000B7F04Out@@@Z
bool Rva000B7F04::rva000B7F04(const AsciiString *in, Rva000B7F04Out *out)
{
	if (m_44)
	{
		int t = m_44->vslot050(in->str());
		if (t)
		{
			Rva000B7F04Out tmp;
			Rva000B7F04Out *p = m_44->vslot051(&tmp, t);
			out->f00 = p->f00;
			out->m04[0] = p->m04[0];
			out->m04[1] = p->m04[1];
			out->m04[2] = p->m04[2];
			out->m04[3] = p->m04[3];
			out->m04[4] = p->m04[4];
			out->m04[5] = p->m04[5];
			out->m04[6] = p->m04[6];
			out->m04[7] = p->m04[7];
			out->m04[8] = p->m04[8];
			out->m04[9] = p->m04[9];
			out->m04[10] = p->m04[10];
			return true;
		}
		float *f = (float *)out;
		f[0] = 1.0f;
		f[1] = 0.0f;
		f[2] = 0.0f;
		f[3] = 0.0f;
		f[4] = 0.0f;
		f[5] = 1.0f;
		f[6] = 0.0f;
		f[7] = 0.0f;
		f[8] = 0.0f;
		f[9] = 0.0f;
		f[10] = 1.0f;
		f[11] = 0.0f;
	}
	return false;
}
