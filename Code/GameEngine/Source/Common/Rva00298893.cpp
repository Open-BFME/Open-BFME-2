// cl: /DNDEBUG /MD
// ?rva00298893@BfmeSubBGB@@QAE_NXZ retail 0x00298893 174B
// BfmeSubBGB method looping +0x244 via slot 0x8C then +0x254 via slot 0x3C plus findObjectByID and report then +0x274 chain.
// Evidence: self bfmeDoBGB pin 0x002984D4 with 8 0; TheGameLogic extern in use 72 TUs; findObjectByID row 0x00049DC5; report pin 0x00294D61.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class Rva00294D61
{
public:
	void report(Object *obj, int v);
};
class BfmeSubBGB;
class LoopRes
{
public:
	virtual void v0();
};
class ElemInner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual LoopRes *v35();
};
struct Elem
{
	char m_pad[0xc];
	ElemInner m_inner;
};
struct IdHolder
{
	char m_pad[8];
	ObjectID m_id;
};
class Mid254
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual IdHolder *v15();
};
class Inner250Res
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14(BfmeSubBGB *b);
};
class Inner250
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual Inner250Res *w31();
};
struct Ptr274
{
	char m_pad[0x250];
	Inner250 *m_ptr;
};
class BfmeSubBGB
{
public:
	void bfmeDoBGB(int a, int b);
	bool rva00298893();
	char m_pad0[0x244];
	Elem **m_244;
	char m_pad244[0xc];
	Mid254 *m_254;
	char m_pad254[0x1c];
	Ptr274 *m_274;
};
bool BfmeSubBGB::rva00298893()
{
	LoopRes *found = 0;
	Elem **pp = m_244;
	if (pp) {
		do {
			Elem *e = *pp;
			if (!e)
				break;
			found = e->m_inner.v35();
			if (found)
				break;
			++pp;
		} while (pp);
	}
	ObjectID oid = m_254->v15() ? m_254->v15()->m_id : INVALID_OBJECT_ID;
	Object *o = TheGameLogic->findObjectByID(oid);
	if (o)
		((Rva00294D61 *)o)->report((Object *)this, 1);
	if (found) {
		Ptr274 *p274 = m_274;
		if (p274) {
			Inner250 *p250 = p274->m_ptr;
			Inner250Res *r = p250 ? p250->w31() : 0;
			if (r)
				r->v14(this);
		}
		found->v0();
		return true;
	}
	bfmeDoBGB(8, 0);
	return false;
}
