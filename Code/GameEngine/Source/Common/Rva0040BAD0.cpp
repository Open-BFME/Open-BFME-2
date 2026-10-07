// cl: /O1 /MD
//
// ?rva0040BAD0@Rva0040BAD0@@QAE_NPAVRva0040AF66@@@Z @0x0040BAD0 39B.
// If the 0x0040AAF8 member (unclaimed, address pinned) on our object reports
// zero for the argument's first dword, push the whole argument record into
// the +0x18 vector through the rowed push_back at 0x0040BA6A and return true.
// Evidence: retail push esi/edi / edi=[esp+0xc] / push [edi] / esi=this /
// call 0x40AAF8 / test eax / jne false / push edi / lea ecx,[esi+0x18] /
// call 0x40BA6A / mov al,1 / jmp ret / false: xor al,al / pop edi,esi /
// ret 4. The push_back spelling is copied from its rowed TU so the call
// resolves to the matched body; the argument deref passes edi itself.
namespace _STL
{
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &x);
};
}

class Rva0040AF66
{
public:
	int m_00;
};

class Rva0040BAD0
{
public:
	bool rva0040BAD0(Rva0040AF66 *arg);
	int rva0040AAF8(int x);
private:
	char m_pad00[0x18];
	_STL::vector<Rva0040AF66, _STL::allocator<Rva0040AF66> > m_vec18;
};

bool Rva0040BAD0::rva0040BAD0(Rva0040AF66 *arg)
{
	if (rva0040AAF8(arg->m_00) == 0)
	{
		m_vec18.push_back(*arg);
		return true;
	}
	return false;
}
