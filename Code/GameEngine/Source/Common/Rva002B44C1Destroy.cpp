// cl: /MD
// ?Rva002B44C1Destroy@@YAXPAVRva002B2F49@@0@Z @0x002B44C1 27B.
// Chain via rowed 0x002B2F49: destroy range of Rva002B2F49 holders calling
// rowed release with flag 0. Evidence: single call site shape push 0 plus
// this-plus-4 loop, callee row in Rva002B2F49Release.cpp, prev/next same
// dir same flags, unblocks 0x002B61C5, caller at 0x002B61D3.
struct Rva002B2F49Inner;
class Rva002B2F49
{
public:
	void *rva002B2F49(unsigned int flag);
private:
	Rva002B2F49Inner *m_ptr;
};
void __cdecl Rva002B44C1Destroy(Rva002B2F49 *first, Rva002B2F49 *last)
{
	for (; first != last; ++first)
		first->rva002B2F49(0);
}
