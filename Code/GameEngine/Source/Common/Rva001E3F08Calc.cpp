// cl: /MD
//
// ?rva001E3F08@Rva001E3F08@@QAEMPAURva001E3F08Arg@@@Z, retail 0x001E3F08, 31 bytes.
// Float product: [esp+4]->+0x258->+0x1f8 times [this+4]->+0x28 times
// global 0x00DBA4F8. x87 fld/fmul shape. Called at 0x001E407C etc.
// Owner identity unproven, honest Rva name.

extern float g_secondsPerLogicFrame;

struct Rva001E3F08MidA
{
	int m_pad00[10]; // +0x00..+0x27
	float m_val28; // +0x28
};

struct Rva001E3F08MidB
{
	int m_pad00[126]; // +0x00..+0x1F7
	float m_val1F8; // +0x1F8
};

struct Rva001E3F08Arg
{
	int m_pad00[150]; // +0x00..+0x257
	Rva001E3F08MidB *m_p258; // +0x258
};

class Rva001E3F08
{
public:
	float rva001E3F08(Rva001E3F08Arg *p);
private:
	int m_pad00; // +0x00
	Rva001E3F08MidA *m_p04; // +0x04
};

float Rva001E3F08::rva001E3F08(Rva001E3F08Arg *p)
{
	return p->m_p258->m_val1F8 * m_p04->m_val28 * g_secondsPerLogicFrame;
}
