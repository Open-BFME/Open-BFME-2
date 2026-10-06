// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005FD0FA@Rva005FD0FA@@QAEXHPBVImage@@@Z @0x005FD0FA 157B
// Apt UpgradeIcon setter with index: same family as AptImageKeySetters.cpp.
// Early-out when the indexed slot already holds the image, otherwise format
// "_level%u.%s_UpgradeIcon%d" from the rowed level getter 0x005FC754 and the
// rowed name getter 0x005FC75B (deref plus empty fallback
// g_Rva0107301CEmptyString), set/clear the +0x28 Rva00524306 list via rowed
// 0x00524725/0x00524306, reset +0x4c to -1 when clearing the current slot,
// and store the image at +0x3c[index]. Caller 0x005F4917 passes
// (count image). Prev/next share /O1.
#include "ascii_string.h"

class Image;

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

class Rva005FC75BAddDwordField
{
public:
	int get() const;
};

class Rva005FC754PtrChaseField
{
public:
	int get() const;
};

class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &key);
	void rva00524725(const AsciiString &key, const Image *image);
private:
	char m_vec[12];
};

extern const char g_Rva0107301CEmptyString[];

class Rva005FD0FA
{
public:
	void rva005FD0FA(int index, const Image *image);
	void OnUpgradeIconRollOver(const char *value);
	void OnUpgradeIconRollOut(const char *value);
private:
	char m_pad00[0x18];
	void *m_owner; // +0x18 read by both getters
	char m_pad1C[0x0C]; // to +0x28
	Rva00524306 m_images; // +0x28
	char m_pad34[0x08]; // to +0x3c
	const Image *m_slot[4]; // +0x3c
	int m_current; // +0x4c
};

void Rva005FD0FA::rva005FD0FA(int index, const Image *image)
{
	const Image *&slot = m_slot[index];
	if (image == slot)
		return;
	AsciiString key;
	const char *t = *(const char **)((const Rva005FC75BAddDwordField *)this)->get();
	const char *suffix = t ? t + 8 : g_Rva0107301CEmptyString;
	key.format("_level%u.%s_UpgradeIcon%d", ((const Rva005FC754PtrChaseField *)this)->get(), suffix, index);
	if (image)
		m_images.rva00524725(key, image);
	else
	{
		m_images.rva00524306(*(const StringBase<char> *)&key);
		if (m_current == index)
			m_current = -1;
	}
	slot = image;
}

// Retail 0x005FD069, 59 bytes: the "ArmyUnitIcon" widget's
// "_level<n>._OnUpgradeIconRollOver" callback, bound as a member pointer by
// its constructor 0x005FD251 (that binding is its only reference): the
// rolled-over slot becomes current when it holds an image.
void Rva005FD0FA::OnUpgradeIconRollOver(const char *value)
{
	if (value && isdigit(*value))
	{
		int index = atoi(value);
		if (index >= 0 && index < 4 && m_slot[index])
			m_current = index;
	}
}

// Retail 0x005FD0A4, 58 bytes: "_OnUpgradeIconRollOut", bound alongside;
// rolling out of the current slot clears it.
void Rva005FD0FA::OnUpgradeIconRollOut(const char *value)
{
	if (value && isdigit(*value))
	{
		int index = atoi(value);
		if (index >= 0 && index < 4 && m_current == index)
			m_current = -1;
	}
}
