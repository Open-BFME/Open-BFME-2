// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0045A421@AutoAbilityBehavior@@QAEXPAX@Z, retail 0x0045A421, 38 bytes.
// Copies the AsciiString at src+0x10 to the member at +0x20 via the pinned
// AsciiString::operator= at 0x000366F0, then arms wake via the rowed
// UpdateModule::setWakeFrame at 0x0044DF71 with the Object at +8 and delay 1.
// Layout follows the rowed dtor ??1AutoAbilityBehavior at 0x0045A37F
// (AsciiString at +0x20) and the pinned ctor at 0x0045A78F (Object at +8).
// Callers at 0x0045A726 and 0x0045A785 pass through to this leaf.

class Object;

#include "ascii_string.h"


enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime delay);

	unsigned char m_pad00[8];
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

struct Rva0045A421Src
{
	unsigned char m_pad[0x10];
	AsciiString m_str10;
};

class AutoAbilityBehavior : public UpdateModule
{
public:
	void rva0045A421(void *src);

private:
	AsciiString m_str20; // +0x20
};

void AutoAbilityBehavior::rva0045A421(void *src)
{
	Object *obj = getObject();
	Rva0045A421Src *s = (Rva0045A421Src *)src;
	m_str20 = s->m_str10;
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}
