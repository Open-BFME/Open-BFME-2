// cl: /DNDEBUG /MD
//
// Small forwarders whose whole retail body calls already-rowed bodies. Each
// name is the pin its matched callers link against (reverse/symbols.csv notes
// give the call sites); the callees are declared, not defined, so every call
// resolves to the callee's own row.
//
//   forwarder   body                                 callee(s)
//   0x005F327A  mov ecx,[ecx+4]; jmp                 0x005F30AE ArmyDetailsMovieClip::Impl::Update
//   0x004D0E8B  push 0; call; ret                    0x004D00BB ConnectionManager
//   0x001B8040  call; jmp                            0x001C4300, 0x001C4440
//
// 0x005F327A reads the pointer at +4 the way ArmyDetailsMovieClip's own
// m_impl sits there (ctor 0x005F3E93); the receiver's class is not proven, so
// it keeps its pinned address name.

namespace StrategicHUD
{
class ArmyDetailsMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::ArmyDetailsMovieClip::Impl
{
public:
	void Update();
};

class Rva005F327ARun
{
public:
	void run();

private:
	void *m_vptr;
	StrategicHUD::ArmyDetailsMovieClip::Impl *m_impl; // +0x04
};

void Rva005F327ARun::run()
{
	m_impl->Update();
}

class ConnectionManager
{
public:
	void rva004D00BB(int arg);
	void rva004D0E8B();
};

void ConnectionManager::rva004D0E8B()
{
	rva004D00BB(0);
}

void bfmeStep1_009A75E0();
void bfmeInstallSpreadTable();

void bfmeRun_009A75E0()
{
	bfmeStep1_009A75E0();
	bfmeInstallSpreadTable();
}
