// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0042DB21@Rva0042DB21@@QAEXPBD@Z @ 0x0042DB21 184B: conditional holder reset plus two notifies
// builds Rva00527CCE from GetLevel/AfterLevel when holder at +0x18 is empty then hands it to +0x24 via rva005785A2 and +0x2c via rva005796B3
// evidence: chain via rowed reset 0x002D38EB plus pinned ctor 0x00527C04 plus rowed AfterLevel 0x00412845 GetLevel 0x004128BB plus rowed notifies 0x005785A2 0x005796B3; pattern from AptPalantirCallbacks OnHelpBoxLoaded and Rva00578AC1 OnCommandUILoaded
#include "ascii_string.h"

const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

class Rva00527CCE
{
public:
	Rva00527CCE(int level, const AsciiString &name);

private:
	unsigned char m_pad[0x20];
};

class Rva002D38EB
{
public:
	void reset(Rva00527CCE *p);

	Rva00527CCE *m_ptr;
};

class Rva00578AC1
{
public:
	void rva005785A2(void *selection);
};

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
};

class Rva0042DB21
{
public:
	void rva0042DB21(const char *path);

private:
	unsigned char m_pad00[0x18];
	Rva002D38EB m_holder; // +0x18
	unsigned char m_pad1C[0x8]; // +0x1C..0x23
	Rva00578AC1 *m_24; // +0x24
	unsigned char m_pad28[0x4]; // +0x28..0x2B
	Rva005796B3 *m_2c; // +0x2C
};

void Rva0042DB21::rva0042DB21(const char *path)
{
	if (m_holder.m_ptr == 0)
	{
		m_holder.reset(new Rva00527CCE(Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path))));
		if (m_24 != 0)
			m_24->rva005785A2(m_holder.m_ptr);
		if (m_2c != 0)
			m_2c->rva005796B3(m_holder.m_ptr);
	}
}
