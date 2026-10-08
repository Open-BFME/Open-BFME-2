// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ??1Rva0052A470@@QAE@XZ @0x0052A470 (69B).
// Non-virtual dtor: AsciiString at +8 plus Rva0052413E at +0x10 plus
// Rva00524349 at +0x1C via rowed dtors plus releaseBuffer. Reverse destroy
// order +0x1C +0x10 +8 with EH states 1/0/-1. Evidence: callees rowed
// 0x00524349 0x0052413E 0x00036410, callers 0x0052A5EA 0x0052A778.
// Precedent Rva005D4913Dtor.
#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_bytes[12];
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	char m_bytes[12];
};

class Rva0052A470
{
public:
	~Rva0052A470();
    void rva0052A66A();
    void rva0052A4B5();
private:
	char m_pad00[8];
	AsciiString m_08;
	bool m_at0C;
    char m_pad0D[3];
	Rva0052413E m_10;
	Rva00524349 m_1C;
};

Rva0052A470::~Rva0052A470()
{
}

namespace AptUtils { AsciiString DotPath2SlashPath(const char *); }
class AptPlayer { public: void RemoveOverButtonHandler(const AsciiString &); };
extern "C" AptPlayer *g_pRva00224BC9;

// Retail 0x0052A66A..0x0052A765 reads the same +8 name owned by
// this class's destructor. Original method and owner identities are unknown.
void Rva0052A470::rva0052A66A()
{
    if (!((StringBase<char> *)&m_08)->isEmpty())
    {
        m_at0C = false;
        rva0052A4B5();
        if (g_pRva00224BC9)
        {
            AsciiString prefix;
            prefix.format("Palantir/%s/Spell%%d/", AptUtils::DotPath2SlashPath(m_08.str()).str());
            for (int i = 0; i < 24;)
            {
                AsciiString path;
                const char *format = prefix.str();
                ++i;
                path.format(format, i);
                g_pRva00224BC9->RemoveOverButtonHandler(path);
            }
        }
        m_08.clear();
    }
}

// ?rva0052A765@Rva0052A765Owner@@QAEXXZ @0x0052A765 7B.
// Tail-jump wrapper loads +0 pointer and jumps to rowed rva0052A66A.
// Evidence: caller 0x002D42B5 plus LINK BONUS plus pin.
class Rva0052A765Owner
{
public:
    void rva0052A765();
private:
    Rva0052A470 *m_ptr;
};

void Rva0052A765Owner::rva0052A765()
{
    m_ptr->rva0052A66A();
}
