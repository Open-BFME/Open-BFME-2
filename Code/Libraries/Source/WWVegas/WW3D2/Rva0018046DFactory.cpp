// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// Ghidra-bounded 94-byte return-by-value factory at 0x0018046D. Retail clears
// the hidden result for a null name; otherwise it gets a counted
// HierarchyPrototypeRef from the rowed registry lookup at 0x0061F230, builds
// the address-derived owner through the matched ctor at 0x0018043C, and then
// releases the temporary reference. The exact owner name is not established.
// This uses the landed 94-byte sibling factory pattern at 0x00180054.
class HierarchyPrototype
{
public:
	void Release_Ref();
};

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

class Rva0018043C
{
public:
	Rva0018043C() : m_prototype(0) {}
	Rva0018043C(const HierarchyPrototypeRef &source);
	~Rva0018043C()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}
	HierarchyPrototype *m_prototype;
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

Rva0018043C Rva0018046D_MakeOwner(const char *name)
{
	if (name == 0)
	{
		Rva0018043C empty;
		return empty;
	}
	return Rva0018043C(Rva0061F230_GetPrototype(name));
}
