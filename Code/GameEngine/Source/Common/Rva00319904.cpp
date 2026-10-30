// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00319904@Rva003193EC@@QAEXPAV1@@Z @0x00319904 32B
// Method of Rva003193EC (this+arg are Rva003193EC* proven by rowed second
// callee 0x003198B8 ?rva003198B8@Rva003193EC@@QAEXPAV1@@Z). Drains other's
// +0x78 ArmySummary entry list into this +0x78 via rowed
// 0x0040ED4F ?MergeUnitsFromArmy@ArmySummary@@QAEXAAV1@@Z then forwards to rva003198B8.
// Evidence: packet disasm ret-4 single ptr arg plus callers 0x002B4A8D 0x002B672F.

class ArmySummary
{
public:
	void MergeUnitsFromArmy(ArmySummary &other);
};

class Rva0037DCA5;
class BfmeY1038;
template <typename T> class StringBase;
class Rva0031980CListener;
struct Rva00319714Call;

class Rva0031980CList
{
public:
	void forEach(void (Rva0031980CListener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva00319714Call &call);

private:
	Rva0031980CListener **m_begin;		// +0x00
	Rva0031980CListener **m_end;		// +0x04
	Rva0031980CListener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

class Rva003193EC
{
public:
	void rva00319904(Rva003193EC *other);
	bool rva003193EC(int x);
	bool rva00319413(Rva0037DCA5 *p);
	void rva003190E7(bool flag);
	void rva003198B8(Rva003193EC *other);
	void rva003191B1();
	void rva003192B1();
private:
	char m_pad00[8];
	Rva0031980CList m_list08;
	char m_pad18[0x78 - 0x18];
	BfmeY1038 *m_78;
	char m_pad7C[0x88 - 0x7C];
	StringBase<unsigned short> *m_88;
};

void Rva003193EC::rva00319904(Rva003193EC *other)
{
	((ArmySummary *)m_78)->MergeUnitsFromArmy(*(ArmySummary *)other->m_78);
	rva003198B8(other);
}
