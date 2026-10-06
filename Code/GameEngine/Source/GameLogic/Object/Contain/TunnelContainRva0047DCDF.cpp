// cl: /MD
//
// ?rva0047DCDF@TunnelContain@@UAEXP6AXPAX0@Z0I@Z @0x0047DCDF 48B.
// Target evidence: the only reference to this body is slot 73 of the vtable
// 0x00C475A4, which the matched TunnelContain ctor 0x0047DC41 and dtor
// 0x0047DB3A install at +0x34 -- the contain interface base of the
// OpenContain-family layout (vptrs at +0, +0xC, +0x10, +0x20, +0x24, +0x28,
// +0x2C, +0x30, +0x34). It is therefore TunnelContain's override of that
// interface's slot 73; the slot's name is not established, hence the address
// name. cl 7.1 compiles an override of a non-primary base's virtual with the
// base subobject's this and folds the adjustment into the member accesses,
// which is why retail reads the Object pointer at TunnelContain+0x1C as
// [ecx-0x18] (no adjustor thunk; the honest class model reproduces it).
// Body: when bit 0 of the flags is set, forwards (callback, user data,
// bit 3 of the flags) to the rowed visitor 0x004F553F on the +0x2E8 member
// of the controlling player of the Object at +0x1C (that field's meaning is
// not asserted; it is the one the body dereferences). /G7 gives the byte
// form of the flag extraction (shr ebx,3; and bl,1).
class Thing;
class ModuleData;
class Player;
typedef void (__cdecl *Rva004F553FCb)(void *data, void *user);
class Rva004F553F
{
public:
	void rva004F553F(Rva004F553FCb cb, void *user, bool flag);
};
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Player
{
public:
	unsigned char m_pad000[0x2E8];
	Rva004F553F *m_2E8;
};
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); int m_14; int m_18; Object *m_1C; };
struct B20 { virtual void f20(); };
struct B24 { virtual void f24(); };
struct B28 { virtual void f28(); };
struct B2C { virtual void f2C(); };
struct B30 { virtual void f30(); };
class ContainIface34
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags) = 0;
};
class TunnelContain
	: public B00, public B0C, public B10, public B20, public B24, public B28, public B2C, public B30
	, public ContainIface34
{
public:
	virtual void rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags);
};
void TunnelContain::rva0047DCDF(Rva004F553FCb cb, void *user, unsigned int flags)
{
	if (!(flags & 1))
		return;
	Player *player = m_1C->getControllingPlayer();
	player->m_2E8->rva004F553F(cb, user, (flags >> 3) & 1);
}
