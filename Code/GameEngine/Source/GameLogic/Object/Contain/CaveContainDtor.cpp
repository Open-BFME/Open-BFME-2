// cl: /O1 /DNDEBUG /MD
//
// ??1CaveContain@@MAE@XZ, retail 0x004663B2, 77 bytes.
// CaveContain behavior dtor over the pinned OpenContain base (0xFC).
// Restores the primary vtable slot and eight secondary slots at
// +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34 plus the derived slot at
// +0xFC, then tail-jumps to the pinned base dtor at 0x00464692
// (??1Rva00039D6AFlatBase@@UAE@XZ). The rowed pool key at 0x4663FF and the
// rowed instance factory 0x24B797 (news 0x10C) prove the class. Shape follows
// the landed PoisonedBehaviorDtor TU (vptr stores plus base tail-jmp); the
// ten vtable immediates resolve through DIR32. Donor is ZH CaveContain.

class Thing;
class ModuleData;

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class Rva00039D6AFlatBase : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~Rva00039D6AFlatBase();
};

class CaveExtra { public: virtual void caveExtra(); };

class CaveContain : public Rva00039D6AFlatBase, public CaveExtra
{
protected:
	virtual ~CaveContain();

private:
	unsigned char m_100; // +0x100
	unsigned char m_pad101[3];
	int m_104;
	int m_108;
};

CaveContain::~CaveContain()
{
}
