// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva00431FB5@@UAE@XZ, retail 0x00431FB5..0x00431FF2 (61 bytes, EH);
// pinned until now as the opaque ??1Rva00431FB5@@UAE@XZ. A message translator
// derived from the rowed Rva0042CBB6 (itself a GameMessageTranslator shape,
// base Rva001DB080 with the BDBA74 table): it drops the 0x00E0322C singleton
// and releases the owned pointer at +8 (rowed clear 0x000AD6F4); the base's
// empty inline destructors leave only the BDBA74 vftable store. Class name
// address-derived.
class Rva001DB080
{
public:
	virtual void translate() = 0;
	virtual ~Rva001DB080() {}
};

class Rva0042CBB6 : public Rva001DB080
{
public:
	virtual void translate();
};

class Rva000AD6F4
{
public:
	void clear();
private:
	void *m_ptr;
};

extern int g_Va00E0322C;

class Rva00431FB5 : public Rva0042CBB6
{
public:
	virtual void translate();
	virtual ~Rva00431FB5();
private:
	int m_04;
	Rva000AD6F4 m_08;
};

Rva00431FB5::~Rva00431FB5()
{
	g_Va00E0322C = 0;
	m_08.clear();
}
