// cl: /O1 /DNDEBUG /MD /EHsc

// TerrainCollision module assignment operators.
//
// Retail 0x003A81AE (TerrainCollisionModuleInfo::operator=, 52B) copies the
// event name string at +4 through AsciiString::operator= (rowed callee
// 0x000366F0), then one movsd triple for the 12-byte event time block at +8,
// the flag byte at +0x14 and the cached dword at +0x18. Layout mirrors the
// landed copy ctor thunk TerrainCollisionModuleInfoCopyCtorThunk.cpp.

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

}
