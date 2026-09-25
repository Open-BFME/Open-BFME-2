// cl: /O1 /DNDEBUG /MD /EHsc

// RenderObjectDrawModuleInfo assignment operator.
//
// Retail 0x003A7D2E (123B) copies the header bool/dword/bool at +4/+8/+0xC,
// then three string-plus-three-dwords blocks at +0x10/+0x20/+0x30, each
// string assigned through AsciiString::operator= (rowed callee 0x000366F0).
// Member layout mirrors the landed copy ctor thunk
// RenderObjectDrawModuleInfoCopyCtorThunk.cpp in this folder. The template
// companion (null-preserving sub at +8 forwarding to this body) is already
// rowed at 0x003A7DA9.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);

private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that)
		: StringBase<char>(that)
	{
	}
	~AsciiString();
	AsciiString &operator=(const AsciiString &that);
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfoBase(const RenderObjectDrawModuleInfoBase &) {}
	virtual ~RenderObjectDrawModuleInfoBase() {}
};

class RenderObjectDrawModuleInfo : public RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &);
	virtual ~RenderObjectDrawModuleInfo();
	RenderObjectDrawModuleInfo &operator=(const RenderObjectDrawModuleInfo &that);

private:
	bool m_enabled;
	unsigned int m_type;
	bool m_flag;
	AsciiString m_name0;
	unsigned int m_value00;
	unsigned int m_value01;
	unsigned int m_value02;
	AsciiString m_name1;
	unsigned int m_value10;
	unsigned int m_value11;
	unsigned int m_value12;
	AsciiString m_name2;
	unsigned int m_value20;
	unsigned int m_value21;
	unsigned int m_value22;
};

// ??4RenderObjectDrawModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A7D2E
RenderObjectDrawModuleInfo &RenderObjectDrawModuleInfo::operator=(const RenderObjectDrawModuleInfo &that)
{
	m_enabled = that.m_enabled;
	m_type = that.m_type;
	m_flag = that.m_flag;
	m_name0 = that.m_name0;
	m_value00 = that.m_value00;
	m_value01 = that.m_value01;
	m_value02 = that.m_value02;
	m_name1 = that.m_name1;
	m_value10 = that.m_value10;
	m_value11 = that.m_value11;
	m_value12 = that.m_value12;
	m_name2 = that.m_name2;
	m_value20 = that.m_value20;
	m_value21 = that.m_value21;
	m_value22 = that.m_value22;
	return *this;
}

}
