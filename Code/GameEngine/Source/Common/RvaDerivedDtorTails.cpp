// cl: /MD
//
// Derived-class destructors with empty bodies: store the class's vtable, then
// tail-jump to the rowed base destructor (11 bytes: mov [ecx], vtable; jmp).
// The derived destructor is defined here, so its vtable is emitted with the
// class and resolves in this unit. The classes are not recovered, so each keeps
// its address; the bases are the rowed destructors' address-named classes.

class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();
};

class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {
public:
    ArmyDetailsMovieClip(int, const AsciiString &, int, bool);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();
private:
    class Impl *m_impl;
};
}

class Rva006003FC
{
public:
	virtual ~Rva006003FC();
};

// ??1Rva005C33D2@@UAE@XZ @0x005C33D2 11B: vtable VA 0xc74434, then ~Rva005C7CBB
class Rva005C33D2 : public Rva005C7CBB
{
public:
	virtual ~Rva005C33D2();
};

Rva005C33D2::~Rva005C33D2()
{
}

// ??1Rva005E54AE@@UAE@XZ @0x005E54AE 11B: vtable VA 0xc77d10, then ~ArmyDetailsMovieClip
class Rva005E54AE : public StrategicHUD::ArmyDetailsMovieClip
{
public:
	Rva005E54AE(int, const AsciiString &, bool);
	virtual ~Rva005E54AE();
};

Rva005E54AE::~Rva005E54AE()
{
}

// ??1Rva005FB204@@UAE@XZ @0x005FB204 11B: vtable VA 0xc79ef0, then ~Rva006003FC
class Rva005FB204 : public Rva006003FC
{
public:
	virtual ~Rva005FB204();
};

Rva005FB204::~Rva005FB204()
{
}

// ??1Rva005FB3D9@@UAE@XZ @0x005FB3D9 11B: vtable VA 0xc79f10, then ~Rva006003FC
class Rva005FB3D9 : public Rva006003FC
{
public:
	virtual ~Rva005FB3D9();
};

Rva005FB3D9::~Rva005FB3D9()
{
}

// Constructor 5E54D5 forwards level/name/zero/back-button Boolean into
// the named 5F3E93 base, then installs the same C77D10 as destructor 5E54AE.
// ?Rva005E54AE::Rva005E54AE present-unmatched
Rva005E54AE::Rva005E54AE(int level, const AsciiString &name, bool back)
    : StrategicHUD::ArmyDetailsMovieClip(level, name, 0, back)
{
}
