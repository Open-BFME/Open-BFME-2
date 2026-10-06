// cl: /MD
// ?rva004C0D4F@Rva004C0D4F@@QAE_NXZ 0x004C0D4F 77B: ask helper via GameLogic findObjectByID and AIUpdate slot 0xa4.
// Evidence: 9 matched callers; global 0x009FE78C (TheGameLogic); pins bfmeAskBUE/BVF/BVG/CCD; vtable slot 0xa4; offsets +0x104 +0x100 +8 +0x74 +0xec +0x254.
enum ObjectID {};
class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class AIUpdate
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void *GetResult();
};

class Object
{
public:
	int m_pad[149];
	AIUpdate *m_ai;
};

struct P8
{
	char m_pad[116];
	int m_val;
};

struct Ret
{
	char m_pad[236];
	int m_val;
};

class Rva004C0D4F
{
public:
	bool rva004C0D4F();
private:
	char m_pad0[8];
	P8 *m_p8;
	char m_padC[244];
	Ret *m_result;
	int m_objectID;
};

bool Rva004C0D4F::rva004C0D4F()
{
	if (m_objectID == 0)
		return false;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)m_objectID);
	if (obj == 0)
		return false;
	AIUpdate *ai = obj->m_ai;
	if (ai == 0)
		return false;
	Ret *r = (Ret *)ai->GetResult();
	m_result = r;
	if (r == 0)
		return false;
	r->m_val = m_p8->m_val;
	return true;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeAskCFC@BfmeOuterCFC@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskCCD@BfmeOuterCCD@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskBVF@BfmeOuterBVF@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskBVG@BfmeOuterBVG@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskCAE@BfmeOuterCAE@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskBUE@BfmeOuterBUE@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskDHA@BfmeOuterDHA@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskDHB@BfmeOuterDHB@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?bfmeAskDHC@BfmeOuterDHC@@QAE_NXZ=?rva004C0D4F@Rva004C0D4F@@QAE_NXZ")
