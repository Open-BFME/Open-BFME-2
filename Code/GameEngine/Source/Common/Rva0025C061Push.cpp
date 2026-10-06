// cl: /MD
// ?rva0025C061@Rva0025C061@@QAEXPAX@Z, retail 0x0025C061, 28 bytes.
// Reads ScienceType at arg+0x74 and pushes it into the vector<ScienceType> at
// this+4 (callee ?push_back@?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@QAEXABW4ScienceType@@@Z
// rowed in Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp).
// Evidence: callers at 0x005960D2/0x0059634C/0x00596483/0x0059666C pass the same
// holder pointer this free-function wrapper received; prev/next rows live in
// Code/GameEngine/Source/Common (FreeMemberDeleters.cpp /O1 /MD).
enum ScienceType
{
	SCIENCE_FIRST = 0
};

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &v);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva0025C061
{
public:
	void rva0025C061(void *holder);
private:
	int m_unk0;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sciences;
};

void Rva0025C061::rva0025C061(void *holder)
{
	m_sciences.push_back((ScienceType)*(int *)((char *)holder + 0x74));
}
// ?rva00596635@Rva00596635@@QAE_NPAX@Z @0x00596635 72B
// __thiscall predicate over holder arg: requires Rva005964ECGet(holder)!=0,
// then if inner(+4)[0x123]&1 pushes Science at holder+0x74 into derived
// vector at this+0x10, else calls base Rva0025C061::rva0025C061(holder).
// Returns true in both push paths, false when predicate fails.
// Evidence: push esi mov edi ecx call 0x5964EC test je; mov eax[esi+4] test
// [eax+123]1 je to base call else vector push_back via 0x2E01C6; callers at
// 0x004E0216; this+0x10 vector, base+0x04 vector (base size 0x10).
int __stdcall Rva005964ECGet(void *holder);
class Rva00596635 : public Rva0025C061
{
public:
	bool rva00596635(void *holder);
private:
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sciences10;
};
bool Rva00596635::rva00596635(void *holder)
{
	if (((unsigned char)Rva005964ECGet(holder)) != 0)
	{
		void *inner = *(void **)((char *)holder + 4);
		if ((((unsigned char *)inner)[0x123] & 1) != 0)
		{
			m_sciences10.push_back((ScienceType)*(int *)((char *)holder + 0x74));
		}
		else
		{
			Rva0025C061::rva0025C061(holder);
		}
		return true;
	}
	return false;
}
