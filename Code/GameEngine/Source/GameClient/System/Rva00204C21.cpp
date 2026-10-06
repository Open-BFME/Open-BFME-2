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
	void release();
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString();
	void *m_bfmeBufCW;
};

class ParticleSystemManager
{
public:
	void bfmeStopCW(const BFMERetailAsciiString &name);
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
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);
		TheParticleSystemManager->bfmeStopCW(text);
	}
}
