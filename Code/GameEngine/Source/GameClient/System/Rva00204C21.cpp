// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Address-derived method at 0x00204C21 (71B), immediately after the matched
// holder-base destructor at 0x00204C16. Target bytes call release 0x0020453C,
// StringBase<char> construction 0x00037BA0, manager method 0x001F9EAF, and
// releaseBuffer 0x00036410. The manager global operand is VA 0x00DFDD04,
// matching the established TheParticleSystemManager definition. The BFME1
// donor supplied the body shape only; its class and method names are not used.

class Rva0020453CHolderBase
{
public:
	~Rva0020453CHolderBase() { release(); }
	virtual void holderSlot0();
	void release();

protected:
	int m_systemID;		// +0x04
	bool m_flag;		// +0x08
};

#include "ascii_string.h"

// The bfmeStopCW row takes its name as this AsciiString view; the canonical
// AsciiString local's inline ctor/dtor emit the StringBase and
// releaseBuffer calls.
class BFMERetailAsciiString : public AsciiString
{
};

class ParticleSystemTemplate;
class BfmeParticleSystemHandle;
class Rva000427195;
class Rva000411084
{
public:
	void *m_node;
	Rva000427195 *m_table;
	void *next();
};

class Rva000427195
{
public:
	void *first(Rva000411084 *iterator);
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *tmpl, bool createSlaves);
	void bfmeStopCW(const BFMERetailAsciiString &name);
	unsigned char m_pad[0x88];
	Rva000427195 m_templateMap;	// +0x88
};

extern ParticleSystemManager *TheParticleSystemManager;

struct Rva00204C21 : Rva0020453CHolderBase
{
	void rva00204C21(const char *name);
};

void Rva00204C21::rva00204C21(const char *name)
{
	release();
	{
		AsciiString text(name);
		TheParticleSystemManager->bfmeStopCW((const BFMERetailAsciiString &)text);
	}
}
