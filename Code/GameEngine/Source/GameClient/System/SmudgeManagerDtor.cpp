// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ??1SmudgeManager@@UAE@XZ, retail 0x002D29F7, 140 bytes.
// Virtual dtor over vtable 0x00C02A60 (slot 0 deleting dtor at 0x002D2A83
// calls this body). Calls the rowed reset at 0x002D27CC, frees the free
// SmudgeSet list at +0x14 via Remove_Head plus deleteInstance slot 0 with 0
// return-fed to the rowed operator delete at 0x0002FD60, frees the static
// SmudgeSet::m_freeSmudgeList Smudge pool via Remove_Head on the +0x14 list
// (donor bug transcribed verbatim) plus DLNode Remove plus operator delete,
// then restores the two DLList vptrs at +0x14/+0x08 to 0x00C02A5C by hand.
// Layout from the rowed reset TU (status at +0x04, used list at +0x08, free
// list at +0x14, count last frame at +0x20; DLNode base at +4 so Head folds
// head-4). Donor BFME1 Smudge.cpp dtor and ZH Smudge.cpp dtor verbatim
// including the second-loop wrong-list Remove_Head. Shape follows
// PlayerListDtor (tracked-pointer virtual release slot 0 with 0).

typedef int Int;


template <class T> class DLNodeClass;






#include "../../../Include/GameClient/Smudge.h"
template<> void DLListClass<SmudgeSet>::Remove_Head();
template<> void DLNodeClass<Smudge>::Remove();

class SmudgeManager
{
public:
	SmudgeManager(void);
	virtual ~SmudgeManager();

	virtual void init(void);
	virtual void reset(void);

protected:
	Int m_hardwareSupportStatus;
	DLListClass<SmudgeSet> m_usedSmudgeSetList;
	DLListClass<SmudgeSet> m_freeSmudgeSetList;
	Int m_smudgeCountLastFrame;
};

SmudgeManager::~SmudgeManager()
{
	reset();

	SmudgeSet *head;
	while ((head = m_freeSmudgeSetList.Head()) != 0) {
		m_freeSmudgeSetList.Remove_Head();
		::delete head;
	}

	Smudge *smudge;
	while ((smudge = SmudgeSet::m_freeSmudgeList.Head()) != 0) {
		m_freeSmudgeSetList.Remove_Head();
		smudge->Remove();
		::operator delete(smudge);
	}
}
