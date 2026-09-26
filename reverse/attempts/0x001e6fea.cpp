// ?findLocomotorTemplate@LocomotorStore@@QAEPBVLocomotorTemplate@@H@Z
// partial score=0.95 date=2026-09-26
// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// LocomotorStore template lookup (AIUpdate parseLocomotorSet cluster).
// The store map is keyed by NameKey with template-pointer values; the
// retail find body folds to the rowed map<int,int> key mechanics, so the
// member uses that spelling and the result is cast back.

#include <map>

class LocomotorTemplate;

class LocomotorStore
{
	char m_pad[0xC];
	_STL::map<int, int> m_templateMap;

public:
	const LocomotorTemplate *findLocomotorTemplate(int key);
};

const LocomotorTemplate *LocomotorStore::findLocomotorTemplate(int key)
{
	if (!key)
		return 0;
	_STL::map<int, int>::iterator it = m_templateMap.find(key);
	if (it == m_templateMap.end())
		return 0;
	return (const LocomotorTemplate *)(*it).second;
}
