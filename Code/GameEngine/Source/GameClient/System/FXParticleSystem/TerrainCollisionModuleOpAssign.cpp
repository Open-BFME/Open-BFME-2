// cl: /O1 /DNDEBUG /MD /EHsc

// TerrainCollision module assignment operators.
//
// Retail 0x003A81AE (TerrainCollisionModuleInfo::operator=, 52B) copies the
// event name string at +4 through AsciiString::operator= (rowed callee
// 0x000366F0), then one movsd triple for the 12-byte event time block at +8,
// the flag byte at +0x14 and the cached dword at +0x18. Layout mirrors the
// Retail 0x003A81E2 (TerrainCollisionModuleTemplate::operator=, 51B)
// keeps the template's null-preserving u16 sub-copy at +8 and forwards the
// info subobject at +0xc to 0x003A81AE. Layouts mirror the landed copy ctor
// thunk TerrainCollisionModuleTemplateCopyCtorThunk.cpp in this folder.

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

class TerrainCollisionModuleInfoBase
{
public:
	TerrainCollisionModuleInfoBase(const TerrainCollisionModuleInfoBase &) {}
	virtual ~TerrainCollisionModuleInfoBase() {}
};

struct TerrainCollisionValueBlock
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
	virtual ~TerrainCollisionModuleInfo();
	TerrainCollisionModuleInfo &operator=(const TerrainCollisionModuleInfo &that);

private:
	AsciiString m_eventName;
	TerrainCollisionValueBlock m_eventTime;
	bool m_flag;
	unsigned int m_cached;
};

// ??4TerrainCollisionModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A81AE
TerrainCollisionModuleInfo &TerrainCollisionModuleInfo::operator=(const TerrainCollisionModuleInfo &that)
{
	m_eventName = that.m_eventName;
	m_eventTime = that.m_eventTime;
	m_flag = that.m_flag;
	m_cached = that.m_cached;
	return *this;
}

class TerrainCollisionCategoryBaseA
{
public:
	virtual ~TerrainCollisionCategoryBaseA();
};

class TerrainCollisionCategoryBaseB
{
public:
	virtual ~TerrainCollisionCategoryBaseB();
};

class TerrainCollisionCategoryBase
	: public TerrainCollisionCategoryBaseA,
	  public TerrainCollisionCategoryBaseB
{
public:
	TerrainCollisionCategoryBase(const TerrainCollisionCategoryBase &) {}
	virtual ~TerrainCollisionCategoryBase();
};

class TerrainCollisionCategoryTemplate : public TerrainCollisionCategoryBase
{
public:
	TerrainCollisionCategoryTemplate(const TerrainCollisionCategoryTemplate &that);
	virtual ~TerrainCollisionCategoryTemplate();

protected:
	volatile unsigned short m_word;
};

class TerrainCollisionModuleTemplate : public TerrainCollisionCategoryTemplate,
				public TerrainCollisionModuleInfo
{
public:
	TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that);
	TerrainCollisionModuleTemplate &operator=(const TerrainCollisionModuleTemplate &that);
	virtual ~TerrainCollisionModuleTemplate();
};

// ??4TerrainCollisionModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A81E2
TerrainCollisionModuleTemplate &TerrainCollisionModuleTemplate::operator=(const TerrainCollisionModuleTemplate &that)
{
	const void *source = &that;
	const void *word_source = source ? (const unsigned char *)source + 8 : 0;
	m_word = *(const unsigned short *)word_source;
	TerrainCollisionModuleInfo::operator=(that);
	return *this;
}

}
