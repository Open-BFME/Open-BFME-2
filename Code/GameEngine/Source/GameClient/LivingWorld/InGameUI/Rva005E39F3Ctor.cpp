// ArmyDetailsPanel icon constructor family, first member: retail 0x005E39F3
// (120B, RET 0x10). The shared virtual-base constructor 0x005F412B and the
// icon-slot reference forwarder 0x005F38D8 are already rowed; the comments in
// Rva005F4179Dtor.cpp name this trio 005E39F3/005E3BD5/005E3C90 as the native
// ArmyDetailsPanel icon constructors. Class names remain address-derived.
//
// Layout proved by the retail stores: vbtable pointer at +0, arg pointer +4,
// int +8, reference +0xC, vtordisp +0x10, virtual Rva005F4179 base +0x14
// (whose vtable this most-derived constructor patches to 0xC77C50).
// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

class Rva005F3F73
{
public:
	Rva005F3F73(void *, void *) throw();
private:
	char storage[0x18];
};

class Rva005F4096
{
public:
	void clear();
	Rva005F4096(Rva005F3F73 *p) : m_ptr(p) {}
private:
	Rva005F3F73 *m_ptr;
};

class Rva005F4179Base
{
public:
	Rva005F4179Base() : m_04(0) {}
	virtual ~Rva005F4179Base() {}
protected:
	int m_04;
};

class ArmyHeroIconMovieClip;

class Rva005F4179 : public Rva005F4179Base
{
public:
	Rva005F4179(void *clip);
	virtual ~Rva005F4179();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	Rva005F4096 m_08;
};

// Same counted icon-slot owner as Rva005F2577Holder in the matched
// CreateMemberIconSlot provider: null guard, refcount at +4, slot-0 release.
struct Rva005F38D8Ref
{
	struct Inner { virtual void release(); int references; };
	Inner *m_ptr;
	__forceinline ~Rva005F38D8Ref()
	{
		Inner *iconSlot = m_ptr;
		if (iconSlot && --iconSlot->references == 0)
			iconSlot->release();
	}
};

class Rva005F38D8
{
public:
	Rva005F38D8Ref rva005F38D8(int position);
	void *unknown00;
	void *implementation;
};

struct Rva005E39F3Arg
{
	char m_pad[0x10];
	void *m_10;
	char m_pad14[0x4];
	Rva005F38D8 *m_18;
};

class Rva005E39F3 : public virtual Rva005F4179
{
public:
	Rva005E39F3(Rva005E39F3Arg *arg, void *clip, int count);
	virtual void DoUpdate();
private:
	Rva005E39F3Arg *m_04;
	int m_08;
	Rva005F38D8Ref m_0c;
};

Rva005E39F3::Rva005E39F3(Rva005E39F3Arg *arg, void *clip, int count)
	: Rva005F4179(clip), m_04(arg), m_08(count),
	  m_0c(arg->m_18->rva005F38D8(-1))
{
}

class ArmyHeroIconMovieClip;

namespace StrategicInGameUI
{
class ArmyHeroIcon : public virtual Rva005F4179
{
public:
	ArmyHeroIcon(void *owner, void *clip, void *entry);
	virtual ~ArmyHeroIcon();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	void *m_owner;
	void *m_hero;
	void *m_clip;
};
}

// ArmyDetailsPanel icon ctor family member 2: retail 0x005E3BD5 (146B,
// RET 0x14). ArmyHeroIcon base at +0, virtual Rva005E39F3 at +0x10 and the
// shared virtual Rva005F4179 base at +0x24 (vtordisp +0x20). The ctor
// constructs the shared virtual base first, then the ArmyHeroIcon base from
// the arg's +0x10 owner, then the icon base.
class Rva005E3BD5 : public StrategicInGameUI::ArmyHeroIcon, public Rva005E39F3
{
public:
	Rva005E3BD5(Rva005E39F3Arg *arg, void *clip, int count, void *entry);
	virtual void DoUpdate();
};

Rva005E3BD5::Rva005E3BD5(Rva005E39F3Arg *arg, void *clip, int count, void *entry)
	: Rva005F4179(clip), StrategicInGameUI::ArmyHeroIcon(arg->m_10, clip, entry),
	  Rva005E39F3(arg, clip, count)
{
}
