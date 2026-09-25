// cl: /O1 /DNDEBUG /MD /arch:SSE

// RenderObjectDrawModuleInfo default constructor.
//
// Retail 0x00562BB1 (70B, frameless) stores the info vtable (0xC1C1B8),
// nulls the three name strings at +0x10/+0x20/+0x30 from their inline
// defaults, then assigns the flag byte at +0xC, the three value dwords,
// the three floats, the three 8-valued dwords, and the header bool and
// float at +4/+8. Member layout mirrors the landed copy ctor thunk
// RenderObjectDrawModuleInfoCopyCtorThunk.cpp in this folder; the header
// float at +8 takes 0.0f (movss) matching retail.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);

private:
	void *m_data;
};

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	AsciiString(const AsciiString &that);

private:
	char *m_text;
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
};

class RenderObjectDrawModuleInfo : public RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfo();
	virtual ~RenderObjectDrawModuleInfo();

private:
	bool m_enabled;
	float m_type;
	bool m_flag;
	AsciiString m_name0;
	unsigned int m_value00;
	float m_value01;
	int m_value02;
	AsciiString m_name1;
	unsigned int m_value10;
	float m_value11;
	int m_value12;
	AsciiString m_name2;
	unsigned int m_value20;
	float m_value21;
	int m_value22;
};

// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@XZ @0x562BB1
RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo()
{
	m_flag = false;
	m_value00 = 0;
	m_value01 = 0.0f;
	m_value02 = 8;
	m_value10 = 0;
	m_value11 = 0.0f;
	m_value12 = 8;
	m_value20 = 0;
	m_value21 = 0.0f;
	m_value22 = 8;
	m_enabled = false;
	m_type = 0.0f;
}

}
