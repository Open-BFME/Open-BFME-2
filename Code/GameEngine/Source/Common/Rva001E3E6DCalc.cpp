// cl: /MD
//
// ?rva001E3E6D@Rva001E3E6D@@QAEMPAURva001E3E6DArg@@@Z, retail 0x001E3E6D, 50 bytes.
// Same arg+this offsets as sibling 0x001E3F08 ([arg+0x258]->+0x1f8, [this+4]).
// Null arg or null +0x258 returns BfmeZeroRange else [this+4]+0x138 *
// [arg+0x258]+0x1f8 * g_secondsPerLogicFrame (x87 fld/fmul). Called at 0x0026C890.
// Owner identity unproven, honest Rva name.

// The data ledger identifies the shared read-only operand as float +0.0.
extern float g_secondsPerLogicFrame;

struct Rva001E3E6DMidA
{
	int m_pad00[78]; // +0x00..+0x137
	float m_val138; // +0x138
};

struct Rva001E3E6DMidB
{
	int m_pad00[126]; // +0x00..+0x1F7
	float m_val1F8; // +0x1F8
};

struct Rva001E3E6DArg
{
	int m_pad00[150]; // +0x00..+0x257
	Rva001E3E6DMidB *m_p258; // +0x258
};

class Rva001E3E6D
{
public:
	float rva001E3E6D(Rva001E3E6DArg *p);
private:
	int m_pad00; // +0x00
	Rva001E3E6DMidA *m_p04; // +0x04
};

float Rva001E3E6D::rva001E3E6D(Rva001E3E6DArg *p)
{
	if (p == 0)
		return 0.0f;
	Rva001E3E6DMidB *mid = p->m_p258;
	if (mid == 0)
		return 0.0f;
	return m_p04->m_val138 * mid->m_val1F8 * g_secondsPerLogicFrame;
}
