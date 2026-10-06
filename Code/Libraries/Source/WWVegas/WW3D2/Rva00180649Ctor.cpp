// cl: /DNDEBUG /MD /EHsc
// ??0BfmeResetTextureRef@@QAE@ABUBfmeResetAnyRef@@@Z @0x00180649 49B
// Ctor twin: zeroes pointer then delegates to rowed rva001805AE assign
// via 0x001805AE. EH prolog with state 0 matches /EHsc. Called from
// 0x0018067A. Unblocks 0x0018067A.
// Base renamed Rva00180649Base: invented EmptyBase with pointer member;
// unrelated empty EmptyBase elsewhere shares mangling, differing COMDAT.
struct BfmeResetTagged
{
	virtual int pad00();
	virtual int pad01();
	virtual int pad02();
	virtual int pad03();
	virtual int pad04();
	virtual int pad05();
	virtual int pad06();
	virtual int pad07();
	virtual int pad08();
	virtual int pad09();
	virtual int pad10();
	virtual int pad11();
	virtual int pad12();
	virtual unsigned GetClassId();
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

class Rva00180649Base
{
public:
	void *pointer;
	Rva00180649Base() : pointer(0) {}
	~Rva00180649Base();
};

struct BfmeResetTextureRef : public Rva00180649Base
{
	void clear();
	BfmeResetTextureRef &rva001805AE(const BfmeResetAnyRef &rhs);
	BfmeResetTextureRef(const BfmeResetAnyRef &rhs);
};

BfmeResetTextureRef::BfmeResetTextureRef(const BfmeResetAnyRef &rhs)
{
	rva001805AE(rhs);
}
