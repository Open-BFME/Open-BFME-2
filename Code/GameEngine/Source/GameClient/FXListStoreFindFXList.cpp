// cl: /Oy- /DNDEBUG /MD /GX-
// platformsdk
//
// ?findFXList@FXListStore@@QBEPBVFXList@@PBD@Z,
// retail 0x001E281A, 69 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/FXList.cpp,
// FXListStore::findFXList): name-keyed FXList lookup that treats "None" as
// empty. The retail body follows the reference source: the name resolves
// through the matched nameToKey row and the map find through the 0x2888D4
// pin, returning the stored list or null.

#include <windows.h>
#include <string.h>
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class FXList
{
};

struct FXListMapNode
{
	void *m_next;
	NameKeyType m_key;
	FXList *m_value;
};

class FXListMap
{
public:
	FXListMapNode *find(const NameKeyType &key) const;
};

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;

private:
	char m_pad[0xC];
	FXListMap m_fxmap;
};

extern FXListStore *TheFXListStore;

// ?findFXList@FXListStore@@QBEPBVFXList@@PBD@Z
const FXList *FXListStore::findFXList(const char *name) const
{
	if (_strcmpi(name, "None") == 0)
		return NULL;

	FXListMapNode *it = m_fxmap.find(TheNameKeyGenerator->nameToKey(name));
	if (it != NULL) {
		return it->m_value;
	}
	return NULL;
}
