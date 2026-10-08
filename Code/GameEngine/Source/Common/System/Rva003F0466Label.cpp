// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F0466@Rva003F0466@@QAE?AVUnicodeString@@XZ, retail 0x003F0466, 122 bytes.
// __thiscall UnicodeString getter via AsciiString at +0x124: returns TheEmptyString
// when empty else TheGameText virtual slot 0x38 fetch. Evidence: rowed StringBase<char>
// isEmpty 0x00001E2F, rowed StringBase<ushort> copy 0x00037050, rowed releaseBuffer
// 0x00036E70, globals TheGameText 0x00DFF0BC and UnicodeString::TheEmptyString
// 0x00A0C898, caller 0x005E2644, neighbours 0x003F0442 0x003F07E5.
// Note: the shared header's AsciiString::isEmpty is inline, but retail calls the
// rowed out-of-line StringBase<char>::isEmpty, so the check goes through a
// StringBase<char> reference (same one-pointer layout the header itself relies on).
#include "ascii_string.h"

#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

// LivingWorldRegion::GetFortressDisplayName (0x003F0466) and
// GetFortressDisplayDescription (0x003F04E0): WorldBuilder names
// (LivingWorldRegion.cpp lines 1478 and 1486), the labels at +0x124 / +0x128
// fetched through TheGameText unless empty.
class LivingWorldRegion
{
public:
	UnicodeString GetFortressDisplayName();
	UnicodeString GetFortressDisplayDescription();
private:
	char m_pad[0x124];
	AsciiString m_fortressNameLabel;			// +0x124
	AsciiString m_fortressDescriptionLabel;		// +0x128
};

UnicodeString LivingWorldRegion::GetFortressDisplayName()
{
	return !((const StringBase<char> *)&m_fortressNameLabel)->isEmpty() ? TheGameText->fetchLabel(m_fortressNameLabel) : UnicodeString::TheEmptyString;
}

UnicodeString LivingWorldRegion::GetFortressDisplayDescription()
{
	return !((const StringBase<char> *)&m_fortressDescriptionLabel)->isEmpty() ? TheGameText->fetchLabel(m_fortressDescriptionLabel) : UnicodeString::TheEmptyString;
}

// Native 0x003F8497..0x003F8509, 114B. The predicate and the optional
// +0x14 child are the same receiver view as the rowed 0x003F8478 wrapper.
// Retail constructs a temporary UnicodeString through the child's rowed
// 0x003F83B5 getter, then copies either it or TheEmptyString to the hidden
// return pointer. WB's callgraph twin independently shows that conditional
// temporary and its teardown. Original owner and method names are unknown.
class Rva003F83B5
{
public:
	UnicodeString rva003F83B5();
};

class Rva003F8052
{
public:
	bool rva003F8052();
	UnicodeString rva003F8497();
private:
	char m_pad00[0x14];
	Rva003F83B5 *m_child14;
};

UnicodeString Rva003F8052::rva003F8497()
{
	return rva003F8052() && m_child14 ? m_child14->rva003F83B5() : UnicodeString::TheEmptyString;
}
