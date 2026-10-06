// cl: /O1 /MD
//
// ?rva000B0298@Rva000B0298@@QAEXXZ @0x000B0298 30B: vector-range destroy
// and free, frameless twin of the EH dtor 0x000B0254. Destroys
// [m_00,m_04) via rowed Destroy 0x000AFF52, frees m_00 via rowed free
// 0x00030830 when non-null. Honest address-derived names; boundary
// verified (push esi at 0xB0298, ret at end).
struct EvaMessageInfo
{
	~EvaMessageInfo();
};
namespace _STL
{
	template <class _ForwardIter> void __cdecl _Destroy(_ForwardIter first, _ForwardIter last);
	void __cdecl free(void *p);
}
class Rva000B0298
{
public:
	void rva000B0298();

private:
	EvaMessageInfo *m_00;
	EvaMessageInfo *m_04;
};
// ?rva000B0298@Rva000B0298@@QAEXXZ
void Rva000B0298::rva000B0298()
{
	_STL::_Destroy(m_00, m_04);
	EvaMessageInfo *p = m_00;
	if (!p)
		return;
	_STL::free(p);
}
