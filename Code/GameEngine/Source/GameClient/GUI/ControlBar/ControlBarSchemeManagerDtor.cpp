// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??1ControlBarSchemeManager@@QAE@XZ, retail 0x003204D9, 101 bytes. Manager dtor: deletes each scheme via rowed Rva0031FAF0 dtor then clears list at +0xC and nulls current at +0x0.
// Evidence: donor ZH ControlBarSchemeManager::~ControlBarSchemeManager; deleting-dtor caller at 0x0031AA18; layout m_currentScheme+0x0 multiplyer+0x4 list+0xC from ControlBarScheme.cpp init TU; callees rowed 0x32002C 0x2FD60 0x23DAA5 0x4EC395.

class Rva0031FAF0
{
public:
	~Rva0031FAF0();
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
		void clear();
	private:
		void *m_header;
	};
	typedef _List_base<int, allocator<int> > ListBaseInt;
}

struct CBMNode
{
	CBMNode *m_next;
	CBMNode *m_prev;
	Rva0031FAF0 *m_obj;
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
	_STL::ListBaseInt m_schemeList;
};

ControlBarSchemeManager::~ControlBarSchemeManager()
{
	CBMList *p = (CBMList *)&m_schemeList;
	CBMNode *cur = p->m_header->m_next;
	while (cur != p->m_header)
	{
		Rva0031FAF0 *obj = cur->m_obj;
		if (obj)
			delete obj;
		cur = cur->m_next;
	}
	m_schemeList.clear();
	m_currentScheme = 0;
}
