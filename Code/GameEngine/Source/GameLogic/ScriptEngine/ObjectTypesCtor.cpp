// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0ObjectTypes@@QAE@XZ @0x003769F9 32B: ObjectTypes default ctor.
// ??4ObjectTypes@@QAEAAV0@ABV0@@Z @0x00376A9C 39B: ObjectTypes copy-assign.
// Evidence: stores vtable 0x00C18630 at +0 (vtable holds deleting dtor
// 0x00376AC3 at slot 0, empty crc at slot 1, GetSnapshotName 0x00376A19
// returning "ObjectTypes" at slot 2, xfer 0x00376B70 at slot 3, then the
// "ObjectTypes" string); zeroes AsciiString m_listName at +4 via and [m],0;
// constructs vector<AsciiString> m_objectTypes at +8 through the ICF-folded
// Vector_base at 0x00211E58 (allocator temp on esp+7, pinned AsciiString
// instantiation). Size 0x14 via factory 0x003BA7FF push 0x14 plus new.
// Callers pair this ctor with dtor 0x00376ADF and addObjectType 0x00376B50
// on the same 0x14 stack object (0x003CA322, 0x003C9F4B). ZH donor
// GameLogic/Object/ObjectTypes.cpp ObjectTypes::ObjectTypes() empty body.
// Prev 0x0037691C GlobalLanguage::parseFontDesc shares /O1 /DNDEBUG /MD;
// this TU adds the proven STLport flags from Rva00330757Member for the same
// Vector_base call shape.
#include <vector>

template <typename T> struct BfmeStringData;

#include "ascii_string.h"


class ObjectTypes
{
public:
	ObjectTypes();
	ObjectTypes &operator=(const ObjectTypes &that);
	virtual ~ObjectTypes();
private:
	AsciiString m_listName; // +4
	_STL::vector<AsciiString> m_objectTypes; // +8
};

ObjectTypes::ObjectTypes()
	: m_listName()
	, m_objectTypes(_STL::allocator<AsciiString>())
{
}

ObjectTypes &ObjectTypes::operator=(const ObjectTypes &that)
{
	m_listName = that.m_listName;
	m_objectTypes = that.m_objectTypes;
	return *this;
}
