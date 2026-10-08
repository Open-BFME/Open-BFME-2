// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0020443D@Rva0020453CHolderBase@@UAEXPBD@Z @0x0020443D 138B
// slot 8 of vtable 0x00BE39F4 (RVA 0x007E39F4), class of ??1Rva0020453CHolderBase.
// Reloads one FXParticleSystem block by name: calls slot 7, then INI::loadBlock
// with "Data\INI\FXParticleSystem.ini", "FXParticleSystem", name, load type 1 and null Xfer.
// Evidence: vtable slot 8, INI ctor 0x0002CDB0/dtor 0x0002CE5B, StringBase PBD 0x00037BA0 x3,
// loadNamedBlock 0x0002DD38 whose only caller 0x002044A5 passes those literals, EH prolog 0x00629188.
#include <vector>

#include "ascii_string.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class Rva00601BBCHelper
{
public:
	Rva00601BBCHelper();
	virtual ~Rva00601BBCHelper();

private:
	char m_body[0x30];
};

class INI
{
public:
	INI();
	~INI();
	bool loadBlock(AsciiString filename, AsciiString blockType, AsciiString blockName, INILoadType loadType, Xfer *pXfer);

private:
	void *m_file;
	AsciiString m_filename;
	unsigned int m_readBufferNext;
	unsigned int m_readBufferUsed;
	unsigned int m_lineNum;
	char m_buffer[0x418 - 0x14];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_blockEndToken;
	const char *m_endScriptToken;
	unsigned char m_endOfFile;
	char m_curBlockStart[0x838 - 0x431];
	Rva00601BBCHelper m_helper;
	AsciiString m_str86C;
	_STL::vector<AsciiString> m_vec870;
};

// The 0xD4-byte particle system template (rowed copy constructor 0x001FCE6B)
// and TheParticleSystemManager's 0x001FCF11, which takes a name and a new
// template (not yet rowed; pinned).
namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);
private:
	unsigned char m_body[0xD4];
};
}

class ParticleSystemManager
{
public:
	void rva001FCF11(const AsciiString &name, FXParticleSystem::ParticleSystemTemplate *tmpl);
};
extern ParticleSystemManager *TheParticleSystemManager;

class Rva0020453CHolderBase
{
public:
	virtual void dummy0() = 0;
	virtual void dummy1() = 0;
	virtual void dummy2() = 0;
	virtual void dummy3() = 0;
	virtual void dummy4() = 0;
	virtual void dummy5() = 0;
	virtual void dummy6() = 0;
	virtual void dummy7() = 0;
	virtual void rva0020443D(const char *name);
	virtual void rva002044C7(const char *name, const FXParticleSystem::ParticleSystemTemplate &source);
};

void Rva0020453CHolderBase::rva0020443D(const char *name)
{
	dummy7();
	INI ini;
	ini.loadBlock("Data\\INI\\FXParticleSystem.ini", "FXParticleSystem", name, INI_LOAD_OVERWRITE, 0);
}

// ?rva002044C7@Rva0020453CHolderBase@@UAEXPBDABVParticleSystemTemplate@FXParticleSystem@@@Z
// @0x002044C7 117B, slot 9 of the same vtable: after slot 7 it hands
// TheParticleSystemManager the name and a new copy of the given template
// (rowed copy constructor 0x001FCE6B). The name's AsciiString is built in the
// template argument's slot once the copy is made. WorldBuilder's twin
// (0x00B302E0) is unnamed.
void Rva0020453CHolderBase::rva002044C7(const char *name, const FXParticleSystem::ParticleSystemTemplate &source)
{
	dummy7();
	FXParticleSystem::ParticleSystemTemplate *copy = new FXParticleSystem::ParticleSystemTemplate(source);
	TheParticleSystemManager->rva001FCF11(name, copy);
}
