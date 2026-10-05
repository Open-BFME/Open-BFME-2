// cl: /MD /EHs-c-
// stlport
// ?rva0010225F@Rva0010225F@@QAEXABV?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@@Z @0x0010225F 37B
// Evidence: unlock lane; vector assign 0x001020BA at +4 then null-checked calls 0x00116496 0x00116482 on +0; callers 0x00102284 0x0010231F 0x000B071D
#include <vector>

struct EvaMessageInfo
{
	char m_unported[28];
	EvaMessageInfo();
	EvaMessageInfo(const EvaMessageInfo &);
	~EvaMessageInfo();
};

// Assignment's full206B provider is EvaMessageVectorAssign.cpp at1020BA.
// Declare this specialization to avoid emitting private template dependencies
// with this unit's different compiler configuration.
namespace _STL {
template <> vector<EvaMessageInfo>& vector<EvaMessageInfo>::operator=(
 const vector<EvaMessageInfo>&);
}

class Rva00116496
{
public:
	virtual void s00();
	virtual void *s04(int x);
	virtual void s08();
	virtual void s0C();
	void rva00116496();
};

class Rva00116482
{
public:
	void rva00116482();
};

class Rva0010225F
{
public:
	void rva0010225F(const _STL::vector<EvaMessageInfo> &arg);
	void rva00102284();
private:
	Rva00116496 *m_00;
	_STL::vector<EvaMessageInfo> m_04;
	Rva00116496 *m_10;
	_STL::vector<EvaMessageInfo> m_14;
};

void operator delete(void *p);

void Rva0010225F::rva0010225F(const _STL::vector<EvaMessageInfo> &arg)
{
	m_04 = arg;
	if (m_00) {
		m_00->rva00116496();
		((Rva00116482 *)m_00)->rva00116482();
	}
}

// ?rva00102284@Rva0010225F@@QAEXXZ @0x00102284 64B.
// Target Ghidra [102284,1022C4), RET0; native calls from singleton-related
// 1022F5 and the destructor527E53 identify this address-scoped holder method.
// At +0/+10 are pointer slots, at +4/+14 the same 12-byte containers consumed
// by the full37B rva0010225F assignment method. Slot04 takes zero and returns
// the storage passed to operator delete; no application resource name asserted.
// Only the +0-nonnull branch unlocks and deletes. Earlier bank called delete
// unconditionally, obscuring this control-flow difference as stack scheduling.
// This corrected branch reproduces all64 bytes and uses full20B unlock116496,
// full37B assignment10225F and the existing retail operator delete2FD60.
void Rva0010225F::rva00102284()
{
	if (m_00) {
		m_00->rva00116496();
		void *p = m_00 ? m_00->s04(0) : (void *)0;
		::operator delete(p);
	}
	Rva00116496 *tmp = m_10;
	m_00 = tmp;
	if (tmp)
		rva0010225F(m_14);
	m_10 = 0;
}
