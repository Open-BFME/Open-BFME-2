// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ?rva005B2B6D@Rva005B2B6D@@QAEXPBD@Z @ 0x005B2B6D, 112 bytes. Vtable
// slot 7 proves a virtual method; its class is address-derived. Retail reads
// a wide string at +0x68 and calls the rowed Mouse method for these path keys.
#include "unicode_string.h"
#include "ascii_string.h"
#include <stdio.h>
#include <string.h>

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString name, int a0, const RGBColor *a1, float a2);
};
extern Mouse *TheMouse;

class CommandButton;
class Rva00406ED7
{
public:
	const CommandButton *rva00406ED7(int index);
};

class Rva005B2B6D;
class Rva005B2B6DOwner
{
public:
	char m_pad[0x27c];
	Rva00406ED7 m_buttons;
	char m_pad2[0x410 - 0x27c - sizeof(Rva00406ED7)];
	Rva005B2B6D *m_current;
};

UnicodeString __cdecl Rva005B2376Describe(void *power, const AsciiString &unused, const AsciiString &fallback);

class Rva005B2B6D
{
public:
	void rva005B2B6D(const char *path);
	void rva005B2CE5(const char *path);
private:
	char m_pad[4];
	Rva005B2B6DOwner *m_owner;
	char m_pad2[0x60];
	UnicodeString m_name;
};

void Rva005B2B6D::rva005B2B6D(const char *path)
{
	if (m_name.isEmpty())
		return;
	if (strstr(path, "/mcRows/") || strstr(path, "/Palantir/Buttons/") ||
		strstr(path, "/mcMyPowerIcon/"))
		TheMouse->rva001EEA6D(m_name, -1, 0, 1.0f);
}

void Rva005B2B6D::rva005B2CE5(const char *path)
{
	int index;
	if (sscanf(path, "%d", &index) != 1)
		return;
	--index;
	const CommandButton *button = m_owner->m_buttons.rva00406ED7(index);
	if (m_owner->m_current == this)
	{
		AsciiString noCurrent("TOOLTIP:CAH_NO_CURRENT_POWER");
		AsciiString current("TOOLTIP:CAH_CURRENT_POWER");
		m_name = Rva005B2376Describe((void *)button, current, noCurrent);
	}
	else
	{
		m_name = Rva005B2376Describe((void *)button,
			AsciiString::TheEmptyString, AsciiString::TheEmptyString);
	}
}
