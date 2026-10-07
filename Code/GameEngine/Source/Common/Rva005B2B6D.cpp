// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ?rva005B2B6D@Rva005B2B6D@@QAEXPBD@Z @ 0x005B2B6D, 112 bytes. Vtable
// slot 7 proves a virtual method; its class is address-derived. Retail reads
// a wide string at +0x68 and calls the rowed Mouse method for these path keys.
#include "unicode_string.h"
#include <string.h>

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString name, int a0, const RGBColor *a1, float a2);
};
extern Mouse *TheMouse;

class Rva005B2B6D
{
public:
	void rva005B2B6D(const char *path);
private:
	char m_pad[0x68];
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
