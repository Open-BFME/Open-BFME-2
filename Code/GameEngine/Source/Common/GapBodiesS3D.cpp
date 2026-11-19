// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached forwarders from .text gaps no ledger row covers
// (seat-3 batch D; see GapBodiesS3A.cpp). Each body is reached only through a
// retail table in .rdata; retail bytes establish every shape. The unrowed
// callees are pinned under address-derived names with the argument counts
// their own `ret` immediates prove.

// --- 0x0035A97E (22B): slot 0 of table 0x00C153D4, the data ledger's
// ??_7Rva00359853@@6B@ that the constructor 0x00359853 and the stack visitor
// in Rva0035A292::rva0035A005 install: both cell coordinates and the +0x08
// word to the +0x04 object's 0x0035A8D7 (ret 0xC).
class Rva0035A8D7
{
public:
	void rva0035A8D7(void *a, void *b, void *c);			// 0x0035A8D7
};

class Rva00359853
{
public:
	virtual void slot00(int cellX, int cellY);
private:
	Rva0035A8D7 *m_target;									// +0x04
	void *m_08;												// +0x08
};

void Rva00359853::slot00(int cellX, int cellY)
{
	m_target->rva0035A8D7((void *)cellX, (void *)cellY, m_08);
}

// --- 0x004E81DE (33B): when the flag is set, pass the +0x08 word, the first
// argument and the float to the +0x04 object's 0x004E7FCA (ret 0xC).
// 0x004E7FCA is rowed as TerrainResourceClaimFeedback::Impl::
// updateClaimedDecalForClaimant(list<ClaimedDecal> *, ObjectID, Real).
struct ClaimedDecal;
#include "../../../../reference/open-bfme-1/game/GameEngine/Include/Common/ObjectID.h"
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class list;
}
class TerrainResourceClaimFeedback
{
public:
	class Impl
	{
	public:
		void updateClaimedDecalForClaimant(_STL::list<ClaimedDecal, _STL::allocator<ClaimedDecal> > *pending, ObjectID id, float radius);
	};
};

class ClaimedDecalUpdateCallback
{
public:
	virtual void rva004E81DE(void *claimantId, float value, bool on);
private:
	TerrainResourceClaimFeedback::Impl *m_target;			// +0x04
	void *m_08;												// +0x08
};

void ClaimedDecalUpdateCallback::rva004E81DE(void *claimantId, float value, bool on)
{
	if (on)
		m_target->updateClaimedDecalForClaimant((_STL::list<ClaimedDecal, _STL::allocator<ClaimedDecal> > *)m_08, (ObjectID)(int)claimantId, value);
}

// --- 0x005AF117 (24B): dispatch on the 0x00E046BC mode word: 0 runs the
// rowed AptMessenger 0x005AEBD3, 1 runs 0x005AED3C.
extern int g_Va00E046BC;

class AptMessenger
{
public:
	void rva005AEBD3();										// 0x005AEBD3
	virtual void rva005AF117();
};

class AptMessengerOnline : public AptMessenger
{
public:
    void UpdatePlayerTabButtons(); // 0x005AED3C, recovered WB identity
};

void AptMessenger::rva005AF117()
{
	switch (g_Va00E046BC)
	{
	case 0:
		rva005AEBD3();
		break;
	case 1:
		static_cast<AptMessengerOnline *>(this)->UpdatePlayerTabButtons();
		break;
	}
}
