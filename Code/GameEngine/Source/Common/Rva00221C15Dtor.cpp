// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??1Rva00221C15@@QAE@XZ @0x00221C78 54B
// Dtor of Rva00221C15: second base Rva00221B42 at +8 via rowed 0x00221B0D plus
// base vtable restore to g_00BC6F20. Layout from rowed ctor 0x00221C15.
// Evidence: retail bytes and caller 0x00221C5C deleting shape.
#include "ascii_string.h"

#include "../../Include/Common/Rva0022185A.h"

class Rva00221A58
{
public:
	Rva00221A58(const Rva00221A58 &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	Rva0022185A m_0C;
	int m_18;
};

class Rva00221B42
{
public:
	~Rva00221B42();
private:
	Rva00221A58 m_00;
	AsciiString m_1C;
};

extern "C" const unsigned char __identifier("??_7Secondary005E7ED7@@6B@")[];

class Rva00221C15Empty
{
public:
	Rva00221C15Empty() {}
	~Rva00221C15Empty() {}
};

class Rva00221C15Base : public Rva00221C15Empty
{
public:
	~Rva00221C15Base() { *(const void **)&m_vtable = __identifier("??_7Secondary005E7ED7@@6B@"); }
protected:
	const void *m_vtable;
	int m_04;
};

class Rva00221C15 : public Rva00221C15Base, public Rva00221B42
{
public:
	~Rva00221C15();
};

Rva00221C15::~Rva00221C15()
{
}

// Native 005EB095..005EB0CB is the destructor of the panel constructed
// at 005EAF19. Its primary table87820C points to deleting wrapper5EB079;
// secondary table8781FC points to the +8 adjustor5EB071. The primary
// counted base restores BC6F20; the movie-clip base at +8 calls5FBBEE.
#include "../../Include/Common/Rva0007DF07.h"
class Rva005FBBEE
{
public:
    virtual ~Rva005FBBEE();
};
namespace StrategicInGameUI {
class DynamicAutoResolveDialog { public: class Impl; };
class DynamicAutoResolveDialog::Impl { public: class PlayerPanelMovieClip; };
class __declspec(novtable) DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip
    : public Rva0007DF07, public Rva005FBBEE
{
public:
    virtual ~PlayerPanelMovieClip();
};
DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::~PlayerPanelMovieClip() {}
}
