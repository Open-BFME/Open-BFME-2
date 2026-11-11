// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva000CED4BUpdate@@YAXPAXPAVAssetList@@H@Z @0x000CED4B 150B: free update accumulating AssetLists and notifying via Rva001E11F8.
// Evidence: rowed Rva001E11F8 0x001E11F8 and StringBase isEmpty 0x00001E2F plus pinned AssetList operator<< and ThingFactory and notify.

#include "ascii_string.h"

#include "../../../../../../GameEngine/Include/Common/Rva001E11F8.h"

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

class ThingTemplate;
#include "../../../../../../GameEngine/Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

// 0x0033CF34 is rowed as ThingTemplate::GetAssetList (146B,
// ThingTemplateGetAssetList.cpp; WB callgraph names it); the found template
// is notified through a TU-local view so the call resolves to the rowed
// body instead of the unrowed Rva0020AA00Target spelling (sole U).
#include "../../../../../../GameEngine/Include/Common/ThingTemplate.h"

struct Rva000CED4BArg
{
	char m_pad[8];
	AsciiString m_08;
	AsciiString m_0c;
	char m_pad10[0x10];
	Rva001E11F8 *m_20;
	Rva001E11F8 *m_24;
	AsciiString m_28;
	char m_pad2c[0x1C];
	AsciiString m_48;
	char m_pad4c[4];
	Rva001E11F8 *m_50;
};

void __cdecl Rva000CED4BUpdate(void *p, AssetList *assetList, int c)
{
	Rva000CED4BArg *a = (Rva000CED4BArg *)p;
	*assetList << a->m_08;
	*assetList << a->m_0c;
	if (a->m_20)
		a->m_20->rva001E11F8((int)assetList, c);
	if (a->m_24)
		a->m_24->rva001E11F8((int)assetList, c);
	if (((StringBase<char> *)&a->m_28)->isEmpty() == false)
		*assetList << a->m_28;
	if (((StringBase<char> *)&a->m_48)->isEmpty() == false) {
		void *t = (void *)TheThingFactory->findTemplate(a->m_48);
		if (t != 0)
			((ThingTemplate *)t)->GetAssetList((int)assetList, c);
	}
	if (a->m_50)
		a->m_50->rva001E11F8((int)assetList, c);
}
