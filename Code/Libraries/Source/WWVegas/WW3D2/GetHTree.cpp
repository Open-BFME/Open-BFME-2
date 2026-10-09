// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Get_HTree@@YAPAVHTreeClass@@PBD@Z @ 0x0017FC7C (178 bytes).
// Free hierarchy lookup: builds the "h*"+name key lowercased, fetches the
// counted prototype from the asset registry, and returns its tree after the
// slot10/slot11 check. Ported from the BFME1 reference GetHTree.cpp (which
// documents the same lookup with a 512-byte key buffer, a hidden-return
// registry reference, and a 4-byte owner holding the prototype at +0 with
// the tree at +0x14). BFME2 differences carried here: the "h*" prefix goes
// through _mbscpy (retail calls the static strcpy twice) and _strlwr arrives
// via the msvcr71 import, so neither is intrinsic.
// Bind this caller's address-pinned hierarchy ref helpers to the matched
// release body and the byte-matched generic counted registry lookup.
#pragma comment(linker, "/alternatename:?Release_Ref@HierarchyPrototype@@QAEXXZ=?Release_Ref@TextureBaseClass@@QAEXXZ")
#pragma comment(linker, "/alternatename:?Rva0061F230_GetPrototype@@YA?AVHierarchyPrototypeRef@@PBD@Z=?Rva009EBCE0_GetPrototype@@YA?AVRva009EBCE0AssetReference@@PBD@Z")

extern "C" char *_mbscpy(char *destination, const char *source);
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *string);

class HTreeClass;

class HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual int slot10();
	virtual void slot11();
	void Release_Ref();

	char m_pad[0x10]; // +0x04
	HTreeClass *m_tree; // +0x14
};

// Counted registry reference returned by value from the asset registry.
// The non-trivial destructor forces the hidden-return slot; retail reuses
// the dead argument slot for it.
// Match the existing counted-registry release provider and shared texture view.
#include "../../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"
class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			((TextureClass *)m_object)->Release_Ref();
	}

private:
	HierarchyPrototype *m_object;
};

// Four-byte owner: holds the prototype pointer and releases it.
class HTreePrototypeOwner
{
public:
	HTreePrototypeOwner(const HierarchyPrototypeRef &source);
	~HTreePrototypeOwner()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

// Asset-registry prototype lookup (retail 0x0061F230). Evidence: frameless
// SEH body returning a counted reference through the hidden slot (null name
// writes a null reference), reading the registry singleton, called with the
// lowercased "h*"+name key here and from the 0x0017FB1E sibling.
extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Get_HTree@@YAPAVHTreeClass@@PBD@Z
HTreeClass *Get_HTree(const char *name)
{
	if (name == 0)
		return 0;

	char lookup[512];
	_mbscpy(lookup, "h*");
	_mbscpy(lookup + 2, name);
	_strlwr(lookup);

	HTreePrototypeOwner owner(Rva0061F230_GetPrototype(lookup));
	if (owner.m_prototype == 0)
		return 0;

	HierarchyPrototype *object = owner.m_prototype;
	if ((unsigned char)object->slot10() == 0)
		object->slot11();
	return object->m_tree;
}
