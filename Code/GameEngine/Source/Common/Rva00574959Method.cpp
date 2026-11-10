// cl: /O1 /DNDEBUG /MD
// ?rva00574959@Rva00574959@@QAEHHH@Z retail 0x00574959 79B
// The local object's matched constructor at 0x00574815 installs the vtable
// whose virtual slots the 0x005CBB4A helper dispatches through. The helper
// receives raw fields at outer offsets +0x1C and +0x44 plus this method's
// 32-bit argument; their meanings are unresolved. Cleanup uses the matched
// 0x005CB9F3 vtable-reset body through its existing address-derived owner.
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();
};

class Rva00574815
{
public:
	Rva00574815(int arg);
	void rva005CBB4A(int first, int second, int third);
	__forceinline ~Rva00574815()
	{
		((Rva0005CB9F3DwordImmSetter *)this)->apply();
	}

private:
	unsigned int m_layout[3];
};
#include "../../Include/Common/Rva005CBB4A.h"

struct Rva005CBC95Pixel;
namespace StrategicInGameUI { class CommonBehavior { public: class Impl; }; }
class StrategicInGameUI::CommonBehavior::Impl
{
public:
	virtual int slot02(const Rva005CBC95Pixel &pos, int modifiers);

private:
	char m_pad04[0x1c - 4];
	int m_1c;
	char m_pad20[0x24];
	int m_44;
	char m_pad48[0x10];
	unsigned char m_58;
};

int StrategicInGameUI::CommonBehavior::Impl::slot02(const Rva005CBC95Pixel &pos, int modifiers)
{
	m_58 = 1;
	Rva00574815 local((int)this);
	((Rva005CBB4A*)&local)->rva005CBB4A((void*)m_1c, (int)&pos, m_44);
	return 0;
}
