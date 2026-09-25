// cl: /O1 /DNDEBUG /MD /EHsc

// LifeEvent module assignment operators.
//
// Retail 0x003A7A51 (LifeEventModuleInfo::operator=, 46B) copies the name
// string at +4 through AsciiString::operator= (rowed callee 0x000366F0),
// then one movsd triple for the 12-byte value block at +8 and the event
// type dword at +0x14. Retail 0x003A7A7F (LifeEventModuleTemplate::operator=,
// 51B) keeps the template's null-preserving u16 sub-copy at +8 and forwards
// the info subobject at +0xc to 0x003A7A51. Layouts mirror the landed copy
// ctor thunks LifeEventModuleInfoCopyCtorThunk.cpp and
// LifeEventModuleTemplateCopyCtorThunk.cpp in this folder.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that)
		: StringBase<char>(that)
	{
	}
	AsciiString &operator=(const AsciiString &that);
};

namespace FXParticleSystem
{

class LifeEventModuleInfoBase
{
public:
	LifeEventModuleInfoBase(const LifeEventModuleInfoBase &) {}
	virtual ~LifeEventModuleInfoBase() {}
};

struct LifeEventValueBlock
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class LifeEventModuleInfo : public LifeEventModuleInfoBase
{
public:
	LifeEventModuleInfo(const LifeEventModuleInfo &);
	virtual ~LifeEventModuleInfo();
	LifeEventModuleInfo &operator=(const LifeEventModuleInfo &that);

private:
	AsciiString m_name;
	LifeEventValueBlock m_values;
	unsigned int m_eventType;
};

// ??4LifeEventModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A7A51
LifeEventModuleInfo &LifeEventModuleInfo::operator=(const LifeEventModuleInfo &that)
{
	m_name = that.m_name;
	m_values = that.m_values;
	m_eventType = that.m_eventType;
	return *this;
}

}
