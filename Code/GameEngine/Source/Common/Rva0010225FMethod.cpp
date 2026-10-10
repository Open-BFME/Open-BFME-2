// cl: /O1 /Ob1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Rva0010225F: the planning UI post-effect holder; 0x0010231F is its Update.
// Native 0x0010231F..0x00102404 (229 bytes) and WB 0x007760E0 independently
// establish saving the +0/+4 pair into +10/+14, creating the lookup-table
// effect from g_00DEC3B8, and applying BlendFactor=1 and plan_vol.tga.
// Existing 28-byte vector/provider names remain neutral ABI views, not
// claims that these post-effect records are application Eva messages.
// Rva00111AA7's 40-byte constructor and the 53-byte paired teardown prove
// the full temporary extent; target accesses independently prove +08/+18.
// The pre-existing factory member view retains the target's unused ECX;
// its owned provider is the stdcall Rva00101FD8Create, not a new identity.
// The assignment of the saved message list goes through a reference to the
// +0x14 vector: native forms its address before pushing the source.

// ?rva0010225F@Rva0010225F@@QAEXABV?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@@Z @0x0010225F 37B
// Evidence: unlock lane; vector assign 0x001020BA at +4 then null-checked calls 0x00116496 0x00116482 on +0; callers 0x00102284 0x0010231F 0x000B071D
#include <vector>
#include "ascii_string.h"

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
template <> vector<EvaMessageInfo>::~vector();
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
	void rva0010231F();
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

class Rva00111B25Record { public: ~Rva00111B25Record(); };
class Rva00111AA7 {
public:
 Rva00111AA7(const char *,int);
 __forceinline ~Rva00111AA7() { reinterpret_cast<Rva00111B25Record*>(this)->~Rva00111B25Record(); }
 unsigned int word00,word04; float value08; unsigned int word0C,word10,word14,word18;
};
struct BfmeAssignRecord28;
namespace _STL { template <> void vector<BfmeAssignRecord28>::push_back(const BfmeAssignRecord28 &); }
class LookupTablePostEffect;
class Rva001022F5 { public: LookupTablePostEffect *rva00101FD8Create(const StringBase<char> &); };
extern const StringBase<char> g_00DEC3B8;
void Rva0010225F::rva0010231F() {
 if (!m_10) {
  m_10=m_00;
  _STL::vector<EvaMessageInfo> &dst=m_14;
  dst=m_04;
  m_00=reinterpret_cast<Rva00116496 *>(reinterpret_cast<Rva001022F5 *>(this)->rva00101FD8Create(g_00DEC3B8));
  if (m_00) {
   _STL::vector<EvaMessageInfo> args;
   Rva00111AA7 blend("BlendFactor",0);
   blend.value08=(1.0f);
   reinterpret_cast<_STL::vector<BfmeAssignRecord28> *>(&args)->push_back(reinterpret_cast<const BfmeAssignRecord28 &>(blend));
   Rva00111AA7 lookup("LookupTexture",1);
   reinterpret_cast<AsciiString *>(&lookup.word18)->operator=("plan_vol.tga");
   reinterpret_cast<_STL::vector<BfmeAssignRecord28> *>(&args)->push_back(reinterpret_cast<const BfmeAssignRecord28 &>(lookup));
   rva0010225F(args);
  }
 }
}
