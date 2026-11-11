// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??1CastleBehavior@@UAE@XZ @0x0039857D 225B evidence: pinned name; vtable VA 0x00C1A780 slot0 deleting dtor caller 0x00399357; donor open-bfme-1 CastleBehaviorDestructorThunk.cpp; callees rowed 0x00397E50 0x003968D3 0x00036410 0x002F0B52 0x00030830 0x00455050

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"

#include "../../../../Include/GameLogic/Module/Rva00397E50.h"

#include "../../../../Include/GameLogic/Rva002EE9B7.h"

class Rva00395CEB
{
public:
	~Rva00395CEB();
private:
	char m_pad[12];
};

class Rva0024A797_Root
{
public:
	virtual ~Rva0024A797_Root();
private:
	char m_pad04[8];
};

class Rva0024A797_Mid
{
public:
	virtual void f1();
};

class Rva0024A797_B2
{
public:
	virtual void f2();
private:
	char m_pad08[12];
};

class Rva0024A797 : public Rva0024A797_Root, public Rva0024A797_Mid, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class Rva00455050_E1
{
public:
	virtual void fe();
};

class Rva00455050 : public Rva0024A797, public Rva00455050_E1
{
public:
	virtual ~Rva00455050();
private:
	char m_pad24[12];
};

class CastleBehavior_30
{
public:
	virtual void f30();
};

// Native unwind calls prove the existing neutral 12-byte storage provider at
// 0x0007FAB3. Its whole destructor and free relocation match here; the buffer
// element types and original class name remain unknown.
struct Rva004E013BBuffer
{
	void *m_begin;
	void *m_end;
	void *m_cap;
	~Rva004E013BBuffer()
	{
		if (m_begin != 0)
			free(m_begin);
	}
};

class CastleBehavior : public Rva00455050, public CastleBehavior_30
{
public:
	virtual ~CastleBehavior();
private:
	char m_pad34[0x1c];
	Rva004E013BBuffer m_vec50;
	Rva004E013BBuffer m_vec5c;
	Rva004E013BBuffer m_vec68;
	Rva004E013BBuffer m_vec74;
	Rva004E013BBuffer m_vec80;
	Rva002EE9B7 m_tree8c;
	AsciiString m_str98;
	char m_pad9c[4];
	Rva00395CEB m_mapA0;
};

// ??1CastleBehavior@@UAE@XZ
CastleBehavior::~CastleBehavior()
{
	((Rva00397E50 *)this)->rva00397E50();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0024A797_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva0024A797_B2@@UAEXXZ=?update@CastleBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f30@CastleBehavior_30@@UAEXXZ=?rva0039A245@Rva0039A245@@UAEXXZ")
#pragma comment(linker, "/alternatename:?fe@Rva00455050_E1@@UAEXXZ=?Rva00452D78Adjust@@YIPAXPAX@Z")
