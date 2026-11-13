// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// InGameSimpleHelp (WorldBuilder InGameSimpleHelp.cpp names its Impl::Impl
// 0x005397F7; the outer class name follows from that Impl). Target facts for
// 0x005398CD (ret 8): a reference counted object (count +0x04, cleared by
// the base; vtable 0x00869268) that builds its 0x14-byte Impl with itself
// and the two texts. Built by InGameHotSpotSimpleHelp and
// StrategicHUD::StandardCommandButtonSettings::CreateHelp.
#include "unicode_string.h"

// The reference counted base (count +0x04; released through 0x0007DEEF).
#include "../../../../Include/Common/Rva005398CDRefCounted.h"

class InGameSimpleHelp : public Rva005398CDRefCounted
{
public:
	class Impl;

	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
	virtual ~InGameSimpleHelp();

private:
	Impl *m_impl; // +0x08
};

class InGameSimpleHelp::Impl
{
public:
	Impl(InGameSimpleHelp *owner, const UnicodeString &title, const UnicodeString &text); // 0x005397F7 (pinned)

private:
	char m_data[0x14];
};

InGameSimpleHelp::InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text)
	: m_impl(new Impl(this, title, text))
{
}

#pragma comment(linker, "/alternatename:??1Rva005398CDRefCounted@@UAE@XZ=??1Coord2D@@QAE@XZ")
// ~InGameSimpleHelp (retail 0x00539926, installs this class's vftable 0x00C69268)
// and its deleting destructor 0x00539961 are defined in Rva005396E6Dtor.cpp.
