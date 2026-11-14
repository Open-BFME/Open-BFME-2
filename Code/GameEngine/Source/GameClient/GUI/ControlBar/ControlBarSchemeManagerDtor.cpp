// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??1ControlBarSchemeManager@@QAE@XZ, retail 0x003204D9, 101 bytes. Manager dtor: deletes each scheme via the ControlBarScheme deleting dtor 0x0032013C (rowed here: this unit emits retail's copy) then clears list at +0xC and nulls current at +0x0.
// Evidence: donor ZH ControlBarSchemeManager::~ControlBarSchemeManager; deleting-dtor caller at 0x0031AA18; layout m_currentScheme+0x0 multiplyer+0x4 list+0xC from ControlBarScheme.cpp init TU; callees rowed 0x32002C 0x2FD60 0x23DAA5 0x4EC395.

#include "../../../../Include/GameClient/ControlBarSchemeClass.h"

#include <list>
namespace _STL {
// Retail keeps these out-of-line operations, shared by pointer-list instances.
template <> _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::~_List_base();
template <> void _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::clear();
}
// Native EH cleanup 0x0077AFBB calls the complete list destructor 0x00200667,
// whose 5-byte tail call reaches the list-base destructor at 0x004EC395.
// The real pointer-list member preserves both levels; declaring only List_base
// incorrectly bound the cleanup directly to the latter. The full parent and EH
// graph verify this member lifetime independently of the donor type spelling.

struct CBMNode
{
	CBMNode *m_next;
	CBMNode *m_prev;
	ControlBarScheme *m_obj;
};

struct CBMList
{
	CBMNode *m_header;
};

class ControlBarSchemeManager
{
public:
	~ControlBarSchemeManager();
private:
	void *m_currentScheme;
	char m_pad4[8];
	_STL::list<ControlBarScheme *> m_schemeList;
};

ControlBarSchemeManager::~ControlBarSchemeManager()
{
	CBMList *cBMList = (CBMList *)&m_schemeList;
	CBMNode *cur = cBMList->m_header->m_next;
	while (cur != cBMList->m_header)
	{
		ControlBarScheme *obj = cur->m_obj;
		if (obj)
			delete obj;
		cur = cur->m_next;
	}
	m_schemeList.clear();
	m_currentScheme = 0;
}
