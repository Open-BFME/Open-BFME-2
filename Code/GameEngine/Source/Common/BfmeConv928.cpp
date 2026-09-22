// cl: /O1 /DNDEBUG /MD /EHsc
// ?bfmeGo928F@BfmeThing928F@@QAEXXZ, retail 0x0010C80A (27B). Ported from
// Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv928.cpp (BFME1 0x007B4F80).
// Trimmed to the placed three-call dispatcher; siblings declared-only here.
// Callees resolve via ledger pins at 0x0010C6C4 (bfmeOne928F),
// 0x00108842 (bfmeTwo928F) and 0x00108A79 (bfmeTail928F): the donor's own
// family names on unclaimed ground. /O1 is load-bearing for bfmeTwo928F
// (pop-ecx cleanup plus esi-homed this); the dispatcher stays green under it.

struct Bfme928FNode
{
	virtual void *deleteInstance(int flag);
	char m_bfmePadA[0x64 - 4];
	Bfme928FNode *m_nextB; // +0x64 retail link
	char m_bfmePadB[0x114 - 0x68];
	Bfme928FNode *m_nextA; // +0x114 retail link
};

class BfmeSub928F
{
public:
	void bfmeTail928F();
};

class BfmeThing928F
{
public:
	void bfmeGo928F();
	void bfmeOne928F();
	void bfmeTwo928F();
	char m_bfmePad0[0x10];
	Bfme928FNode *m_bfmeHeadA; // +0x10
	int m_bfmeUnknown14; // +0x14 retail gap, untouched by this drainer
	Bfme928FNode *m_bfmeHeadB; // +0x18
	char m_bfmePad1[0x24c - 0x1c];
	BfmeSub928F *m_bfmeSub; // +0x24c
};

// ?bfmeGo928F@BfmeThing928F@@QAEXXZ
void BfmeThing928F::bfmeGo928F()
{
	bfmeOne928F();
	bfmeTwo928F();
	m_bfmeSub->bfmeTail928F();
}

// ?bfmeTwo928F@BfmeThing928F@@QAEXXZ, retail 0x00108842 (83B).
// Twin list-drain over one node type with two link fields: phase A walks
// +0x114, phase B walks +0x64. Each node is released through its slot0
// deleteInstance(0) deleter with the freed pointer fed to operator delete
// (Radar deleteListResources precedent); the link is nulled before the
// release exactly as retail. Phase B needs the link as a reference local:
// a sourced-before `Node* &` commits the null store above the push with
// zero emitted bytes (address-take law, RebuildHole/WeaponFire precedent)
// while the direct phase A shape already orders itself under /O1.
void BfmeThing928F::bfmeTwo928F()
{
	Bfme928FNode *cursor = m_bfmeHeadA;
	while (cursor != 0) {
		Bfme928FNode *next = cursor->m_nextA;
		cursor->m_nextA = 0;
		::operator delete(cursor->deleteInstance(0));
		cursor = next;
	}
	m_bfmeHeadA = 0;
	cursor = m_bfmeHeadB;
	while (cursor != 0) {
		Bfme928FNode * &linkB = cursor->m_nextB;
		Bfme928FNode *next = linkB;
		linkB = 0;
		::operator delete(cursor->deleteInstance(0));
		cursor = next;
	}
	m_bfmeHeadB = 0;
}
