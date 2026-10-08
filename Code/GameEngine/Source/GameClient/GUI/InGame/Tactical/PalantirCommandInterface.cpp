// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// WorldBuilder callgraph lead: PalantirCommandInterface::Impl::OnToggleFlashLoaded
// at VA 0x013CC080, PalantirCommandInterface.cpp:1188. Target ABI and
// offsets below come from native bytes; the class name remains a donor lead.
#include "ascii_string.h"

struct CameraMarker;
class Rva00528FE6 {
public:
 void rva00528FE6(CameraMarker *marker);
private:
 void *m_ptr;
};
class Rva005C3932 {
public:
 Rva005C3932(int level, const AsciiString &name);
private:
 char m_data[8];
};
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// Native 0x0052991E..0x00529A21, RET4: the same toggle-clip allocation
// and lifetime as CommandUIImpl::OnToggleFlashLoaded. Target-specific
// parsers are rowed; six slots are 0x14 bytes from +0x64, holder +8.
// The owning UI class has not been established from target evidence.
bool __cdecl Rva00529628Get(const char *path, int *slot);
bool __cdecl Rva00528C30Get(const char *path, AsciiString &name);
class Rva0052991E
{
	struct Slot
	{
		char m_pad00[8];
		Rva00528FE6 m_toggleFlash;
		char m_pad0C[0x14 - 0x0C];
	};
	char m_pad00[0x64];
	Slot m_slots[6];
public:
	void rva0052991E(const char *path);
};
void Rva0052991E::rva0052991E(const char *path)
{
	AsciiString name;
	Slot *button;
	{
		int slot;
		if (!Rva00529628Get(path, &slot))
			return;
		if (!Rva00528C30Get(path, name))
			return;
		button = &m_slots[slot];
	}
	if (*(void **)&button->m_toggleFlash)
		return;
	button->m_toggleFlash.rva00528FE6((CameraMarker *)new Rva005C3932(Rva004128BBGetLevel(name.str()), AsciiString(Rva00412845AfterLevel(name.str()))));
}
