// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /Oy- /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022CD78@@QAE@XZ @0x0022CD78 (70B): EH ctor running
// baseConstruct() from an inlined novtable head, storing the own vtable,
// then constructing the +0xC 2x0x10 array through the rowed... (unrowed)
// vector-construct helper at 0x00629512 with the rowed element ctor
// 0x0022CD65 and the dtor thunk 0x0022CA3B as callbacks; returns this.
// Follows precedent Rva0022E03FTwins (same ehdata 0x00B6F8B7 family):
// the head's virtual dtor is the unwind-guard source under /EHsc.
// Evidence: baseConstruct call 0x22CD89; vtable VA 0x00BE7528 whose slot 0
// is the scalar deleting dtor at 0x0022CDBE; helper pushes
// (thunk, ctor, 2, 0x10, this+0xC); helper ret 0x14 (stdcall, 5 args);
// address-derived.
class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) Rva0022CD78Head
{
public:
	__forceinline Rva0022CD78Head() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022CD78Head() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
private:
	char m_flag;
	int m_value;
};

void __stdcall Rva00629512ConstructN(void *mem, int stride, int count, void *ctorFn, void *dtorFn);
void Rva0022CD65Construct(void *);
void Rva0022CA3BThunk();

class Rva0022CD78 : public Rva0022CD78Head
{
public:
	virtual void rva_vtable_anchor() {}
	Rva0022CD78();
private:
	char m_arr[32]; // +0xC: 2 elements of 0x10 built by the helper
};

Rva0022CD78::Rva0022CD78()
{
	Rva00629512ConstructN(&m_arr, 0x10, 2,
		reinterpret_cast<void *>(Rva0022CD65Construct),
		reinterpret_cast<void *>(Rva0022CA3BThunk));
}
