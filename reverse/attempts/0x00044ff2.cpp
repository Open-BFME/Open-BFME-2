// ?rva00044FF2@W3DDisplay@@QAEXHHH@Z
// partial score=0.97 date=2026-10-07
// ?rva00044FF2@W3DDisplay@@QAEXHHH@Z
// partial score=0.97 date=2026-10-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
//
// Small W3DDisplay vtable slots (vtable VA 0x00BC3C80, which also holds
// testMinSpecRequirements and the rows of W3DDisplayRva000433AC.cpp) that had
// no ledger owner. Three of them reach the terrain render object
// (TheTerrainRenderObject, VA 0x00DE1EAC) and its +0x3878/+0x387C helpers,
// whose 0x000729CC flag setter is already rowed; 0x00073CC0 is a 4-argument
// method on the +0x387C helper (ret 0x10, also called that way from
// 0x000450CE). The +0x188 object shares the 0x00045837 query with the
// MilesAudioManager +0xBE8 one; TheAudio is VA 0x00DFE6E8. Method names stay
// address derived: the bytes prove the hops, offsets and argument counts only.

typedef int Int;
typedef bool Bool;

class GlobalData;
extern GlobalData *TheGlobalData;
extern void *g_Va00DFE750;

class Rva000683DC
{
public:
 void rva000683DC();
};
class Rva006C0840
{
public:
 Int rva006C0840(Int x, Int y);
};

void __cdecl operator delete(void *p);

#define VSLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define VSLOTS16(p) VSLOTS4(p##0) VSLOTS4(p##1) VSLOTS4(p##2) VSLOTS4(p##3)

class Rva00260A3C
{
public:
	virtual ~Rva00260A3C();
	Bool test() const;
};

class Rva000729CC
{
public:
	void rva000729CC(Bool on);
	void rva00073CC0(Int a, Int b, Int c, Int d);
 void rva000731F4(Int x, Int y, unsigned char level, Bool flag);
};

class BaseHeightMapRenderObjClass
{
public:
	char m_pad00[0x3878];
	Rva000729CC *m_3878;
	Rva000729CC *m_387c;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class AudioManager
{
public:
	VSLOTS16(s0) VSLOTS16(s1) VSLOTS16(s2) VSLOTS16(s3) VSLOTS16(s4) VSLOTS16(s5)
	virtual void s960(); virtual void s961(); virtual void s962();
	virtual Bool rva0004672AQuery();	// slot 99
};
extern AudioManager *TheAudio;

class Rva00049F4FObject
{
public:
	VSLOTS16(s0) VSLOTS16(s1) VSLOTS16(s2) VSLOTS16(s3) VSLOTS16(s4) VSLOTS16(s5)
	VSLOTS16(s6) VSLOTS16(s7) VSLOTS16(s8)
	VSLOTS4(s90) VSLOTS4(s91)
	virtual Int rva00049F59Query();	// slot 152
};

class Rva00046791Item
{
public:
	VSLOTS4(s0) VSLOTS4(s1) VSLOTS4(s2)
	virtual void rva000467A5Slot();	// slot 12
};

class W3DDisplay
{
public:
	void rva00044FD5(Bool on);
 void rva00044FF2(Int x, Int y, Int setting);
	void rva00045086(Bool on);
	void rva000450A3(Int a, Int b, Int c);
	Bool rva000466FA();
	void rva000466B9();
	void rva00046791();
	Int rva00049F4F(Rva00049F4FObject *obj);
private:
	char m_pad00[0x184];
	Int m_184;
	Rva00260A3C *m_188;
	char m_pad18C[0x2a4 - 0x18c];
	Rva00046791Item **m_2a4;
	Rva00046791Item **m_2a8;
};

// vtable 0x00BC3C80#78
void W3DDisplay::rva00044FD5(Bool on)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->m_3878)
		TheTerrainRenderObject->m_3878->rva000729CC(on);
}

// vtable 0x00BC3C80#81
void W3DDisplay::rva00045086(Bool on)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->m_387c)
		TheTerrainRenderObject->m_387c->rva000729CC(on);
}

// vtable 0x00BC3C80#79
void W3DDisplay::rva000450A3(Int a, Int b, Int c)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->m_387c)
		TheTerrainRenderObject->m_387c->rva00073CC0(a, b, c, 0);
}

// vtable 0x00BC3C80#27
Bool W3DDisplay::rva000466FA()
{
	Bool result = false;
	if ((m_184 && m_188 && m_188->test()) || (TheAudio && TheAudio->rva0004672AQuery()))
		result = true;
	return result;
}

// vtable 0x00BC3C80#32
void W3DDisplay::rva00046791()
{
	for (Rva00046791Item **it = m_2a4; it != m_2a8; ++it)
		(*it)->rva000467A5Slot();
}

// vtable 0x00BC3C80#100
void W3DDisplay::rva000466B9()
{
	if (m_184 == 0)
		return;
	Rva00260A3C *p = m_188;
	if (p == 0)
		return;
	if (p->test())
		return;
	p->Rva00260A3C::~Rva00260A3C();
	operator delete(p);
	m_188 = 0;
	m_184 = 0;
}

// vtable 0x00BC3C80#37
Int W3DDisplay::rva00049F4F(Rva00049F4FObject *obj)
{
	if (obj)
		return obj->rva00049F59Query();
	return 0;
}

// Native 0x00044FF2..0x00045086, RET 12. ZH W3DDisplay::setShroudLevel
// supplies the shroud-alpha/notification semantics. BFME 2 independently
// uses +0x3878 and +0x387C helpers and GlobalData bytes BE8/BE9/BEA;
// the extra taint query and second helper update are target evidence.
// The method and unclaimed helper identities remain address derived.
void W3DDisplay::rva00044FF2(Int x, Int y, Int setting)
{
 if (TheTerrainRenderObject && TheTerrainRenderObject->m_3878)
 {
  if (setting == 2)
   TheTerrainRenderObject->m_3878->rva000731F4(x, y, ((const unsigned char *)TheGlobalData)[0xBEA], false);
  else if (setting == 1)
   TheTerrainRenderObject->m_3878->rva000731F4(x, y, ((const unsigned char *)TheGlobalData)[0xBE9], false);
  else
   TheTerrainRenderObject->m_3878->rva000731F4(x, y, ((const unsigned char *)TheGlobalData)[0xBE8], false);
  ((Rva000683DC *)TheTerrainRenderObject)->rva000683DC();
  Rva000729CC *helper = TheTerrainRenderObject->m_387c;
  if (helper && g_Va00DFE750)
   helper->rva00073CC0(x, y, ((Rva006C0840 *)g_Va00DFE750)->rva006C0840(x, y), 1);
 }
}
