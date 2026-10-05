// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x00355B61 (85 bytes): SubsystemInterface plus Snapshot bases and two
// 0x14-byte ArmorTemplateMap members. The map calls must use the already-owned
// constructor/dtor COMDATs at 0x00355B42 and 0x00355257, not local instantiations.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8];
};

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
};

class ArmorTemplateMap
{
public:
	ArmorTemplateMap();
	~ArmorTemplateMap();

private:
	char m_pad[0x14];
};

class Rva00355B61 : public SubsystemInterface, public SnapshotBase
{
public:
	Rva00355B61();
	virtual ~Rva00355B61();
	void init() { }
	void reset() { }
	void update() { }

private:
	ArmorTemplateMap m_map1;
	ArmorTemplateMap m_map2;
};

Rva00355B61::Rva00355B61()
{
}
