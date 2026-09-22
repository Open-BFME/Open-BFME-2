// cl: /O1 /DNDEBUG /MD /EHsc

// Open-BFME5: TerrainCollisionModuleInfo copy constructor.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that)
		: StringBase<char>(that)
	{
	}
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

private:
	BFMERetailAsciiString m_eventName;
	TerrainCollisionValueBlock m_eventTime;
	bool m_flag;
	unsigned int m_cached;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo(
	const TerrainCollisionModuleInfo &that)
	: TerrainCollisionModuleInfoBase(that),
	  m_eventName(that.m_eventName),
	  m_eventTime(that.m_eventTime),
	  m_flag(that.m_flag),
	  m_cached(that.m_cached)
{
}

}
