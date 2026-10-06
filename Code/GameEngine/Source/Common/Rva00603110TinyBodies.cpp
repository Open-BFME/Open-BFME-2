// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva0060C1B0@@YGXPAXPBVAsciiString@@@Z
// retail 0x003F92BB, 31 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva00603110TinyBodies.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor body is
// byte-identical to retail once relocations are masked (unique hit on unclaimed
// .text). Only the placed body is defined here; the donor's other 23 accessor
// definitions are omitted.
//
// A lookup through the living-world manager: find the item by name, and store
// its value through the out pointer only when the name resolved. The global is
// EA's `LivingWorldManager *TheLivingWorldManager`, defined once elsewhere;
// this TU sees it only through its own local view, and the pointee is cast at
// the use because the view types differ.

class AsciiString;
class LivingWorldManager;

struct Rva00612430Item
{
	char m_padding[4];
	void *m_value;
};

class Rva00612430Owner
{
public:
	Rva00612430Item *find(const AsciiString &name);
};

extern LivingWorldManager *TheLivingWorldManager;

void __stdcall Rva0060C1B0(void *out, const AsciiString *name)
{
	Rva00612430Item *item = reinterpret_cast<Rva00612430Owner *>(TheLivingWorldManager)->find(*name);
	if (item != 0)
		*(void **)out = item->m_value;
}