// cl: /MD
// Address-derived AptValue cleanup helper at 0x006F3670 (51 bytes). The body
// calls the rowed sound-type predicate ?isSound@BfmeAptValue006DCD20@@QBEHXZ
// (0x006DC3F0), the rowed checked cast ?rva006DCFE0@... (0x006DCFE0), frees the
// +0x24 buffer through the global free-function pointer at 0x00E17784, and
// returns the rowed undefined singleton at 0x00E18078. Only the free pointer is
// unpinned; it is a DIR32 data slot copied from retail, not a call pin. Identity
// not recovered: the function name is address-derived.

class BfmeAptValue006DCD20
{
public:
	int isSound() const;
	BfmeAptValue006DCD20 *rva006DCFE0();
};

class BfmeAptSoundValue
{
public:
	char m_pad[0x24];
	void *m_data;
	int m_size;
};

extern void (__cdecl *g_bfmeAptFreeAtE17784)(void *data, int size);
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;

BfmeAptValue006DCD20 *Rva006F3670(BfmeAptValue006DCD20 *value)
{
	if (static_cast<unsigned char>(value->isSound()))
	{
		BfmeAptSoundValue *sound = (BfmeAptSoundValue *)value->rva006DCFE0();
		if (sound->m_data)
		{
			g_bfmeAptFreeAtE17784(sound->m_data, sound->m_size);
		}
	}
	return g_aptUndefinedAtE18078;
}
