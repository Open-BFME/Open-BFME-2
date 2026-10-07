// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /EHsc
// Target lifecycle at 0x0030DA25 (432B) and 0x0030DBD5 (158B).
// The ctor installs table C08A2C; its slot-zero deleting dtor 30DE92
// calls 30DBD5. Base ctor 30D346 initializes the eight-byte prefix (table
// C089EC and null link at +4); the derived cleanup restores that table.
// Native EH tables establish ownership of the name +14, Dict +24, and
// reference holder +58. Target names are opaque; ZH WorldHeightMap and
// BFME1 MapObjectDestructor at donor 7dff0a4a9e9 provide semantic leads.
// BFME2 differs from that donor: one audio handle +54 and holder +58.
// Caller 30E33B pushes &name (+14), proving a reference argument.
// Key-cache storage and strings are retail evidence.
// Set_Material is the existing byte-and-relocation owner of the +2C
// ref-pointer replacement at 30D3AD, also called by this destructor.
#include "ascii_string.h"
#include "Lib/Coord3D.h"

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	~Dict() { releaseData(); }
	Dict &operator=(const Dict &src);
	int getInt(int key, bool *exists) const;
	void setInt(int key, int value);
	void setBool(int key, bool value);
private:
	void releaseData();
	void *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
private:
	NameKeyType m_key;
	const char *m_name;
};

class StaticNameKey;
extern const StaticNameKey TheKey_GenericAIObjectType;
extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey TheKey_objectEnabled;
extern const StaticNameKey TheKey_objectIndestructible;
extern const StaticNameKey TheKey_objectUnsellable;
extern const StaticNameKey TheKey_objectPowered;
extern const StaticNameKey TheKey_objectRecruitableAI;
extern const StaticNameKey TheKey_objectTargetable;
extern const StaticNameKey TheKey_objectBasePriority;
extern const StaticNameKey TheKey_objectBasePhase;



float normalizeAngle(float angle);
AsciiString Rva0030D5EEConstruct(const AsciiString &src);

class Rva0030D773
{
public:
	void rva0030D773(int val);
};

class OpaqueRefCounted { public: void Release_Ref(); };

class BfmeStringTailRecord156
{
public:
    __forceinline BfmeStringTailRecord156(void *p) : m_ptr(p) {}
    ~BfmeStringTailRecord156() { if (m_ptr) ((OpaqueRefCounted *)m_ptr)->Release_Ref(); }
private:
    void *m_ptr;
};

// Same zero-storage base as the rowed constructor in RvaSmallVtableCtors.cpp.
struct RvaSmallVtableZeroBase
{
    void *m_04;
    RvaSmallVtableZeroBase() : m_04(0) {}
};

class Rva0030D346 : public RvaSmallVtableZeroBase
{
public:
    Rva0030D346() {}
    virtual ~Rva0030D346() {}
};

class VertexMaterialClass;
class MaterialPassClass { public: void Set_Material(VertexMaterialClass *); };
class RenderObjClass;
enum BridgeTowerType { BRIDGE_TOWER_FIRST=0 };
class MapObject { public: void setBridgeRenderObject(BridgeTowerType, RenderObjClass *); };
class Rva0030D606 { public: void rva0030D606(); };

class Rva0030DBD5 : public Rva0030D346
{
public:
	Rva0030DBD5(Coord3D pos, const AsciiString &name, float angle, int a, const Dict *dictSrc, void *thing);
    virtual ~Rva0030DBD5();
private:
	Coord3D m_pos;
	AsciiString m_name;
	void *m_thing;
	float m_angleN;
	int m_20;
	Dict m_dict;
	int m_28;
	int m_2c;
	int m_30;
	int m_34[4];
	int m_44;
	char m_pad48[12];
	int m_54;
	BfmeStringTailRecord156 m_58;
};

Rva0030DBD5::Rva0030DBD5(Coord3D pos, const AsciiString &name, float angle, int a, const Dict *dictSrc, void *thing)
	: Rva0030D346(), m_dict(0), m_58(0)
{
	m_pos = pos;
	m_name = Rva0030D5EEConstruct(name);
	m_thing = thing;
	m_angleN = normalizeAngle(angle);
	m_20 = a;
	m_54 = 1;
	if (dictSrc != 0)
	{
		m_dict = *dictSrc;
		bool exists = false;
		int v = m_dict.getInt(((Rva00148F5ECache *)&TheKey_GenericAIObjectType)->get(), &exists);
		if (exists)
			((Rva0030D773 *)this)->rva0030D773(v);
	}
	else
	{
		m_dict.setInt(((Rva00148F5ECache *)&TheKey_objectInitialHealth)->get(), 100);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectEnabled)->get(), true);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectIndestructible)->get(), false);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectUnsellable)->get(), false);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectPowered)->get(), true);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectRecruitableAI)->get(), true);
		m_dict.setBool(((Rva00148F5ECache *)&TheKey_objectTargetable)->get(), false);
		m_dict.setInt(((Rva00148F5ECache *)&TheKey_objectBasePriority)->get(), 40);
		m_dict.setInt(((Rva00148F5ECache *)&TheKey_objectBasePhase)->get(), 1);
	}
	m_2c = 0;
	m_30 = 0;
	m_28 = 0xff00;
	for (int i = 0; i < 4; ++i)
		m_34[i] = 0;
	m_44 = 0;
}

Rva0030DBD5::~Rva0030DBD5()
{
    ((MaterialPassClass *)this)->Set_Material(0);
    m_30 = 0;
    Rva0030DBD5 *cur = (Rva0030DBD5 *)m_04;
    while (cur) {
        Rva0030DBD5 *next = (Rva0030DBD5 *)cur->m_04;
        cur->m_04 = 0;
        ::delete cur;
        cur = next;
    }
    for (int i=0; i<4; ++i)
        ((MapObject *)this)->setBridgeRenderObject((BridgeTowerType)i,0);
    ((Rva0030D606 *)this)->rva0030D606();
}
