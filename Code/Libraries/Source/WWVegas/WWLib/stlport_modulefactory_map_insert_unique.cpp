// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z,
// retail 0x00413740, 134 bytes. Dedicated TU.
//
// ModuleFactory::ModuleTemplateMap red-black tree no-hint insert_unique
// (pair<iterator,bool> shape: search with less, decrement on begin miss,
// then _M_insert or existing). Retail calls the rowed _M_insert 0x0041362C
// and the rowed _M_decrement. Same 134B shape as the int-pod16 precedent.
// Evidence: unlock lane makes 0x00414009 and 0x004138C7 ready; left-spine
// search with setl and begin fast path.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

enum NameKeyType
{
	NAMEKEY_0 = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		int m_whichInterfaces;
	};
};

typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryInsertValue;
typedef _STL::_Rb_tree<NameKeyType, ModuleFactoryInsertValue, _STL::_Select1st<ModuleFactoryInsertValue>, _STL::less<NameKeyType>, _STL::allocator<ModuleFactoryInsertValue> > ModuleFactoryInsertTree;

template _STL::pair<ModuleFactoryInsertTree::iterator, bool> ModuleFactoryInsertTree::insert_unique(const ModuleFactoryInsertTree::value_type &);
