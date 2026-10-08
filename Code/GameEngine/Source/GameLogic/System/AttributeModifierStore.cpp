// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// stlport
// AttributeModifierStore.cpp -- AttributeModifierStore members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes.
//
// The store keeps its modifiers in a vector at +0x0C; the per-modifier
// query (0x004036B1) is rowed under a placeholder name with the argument
// types its row carries.

// Keep shared copy helpers at their verified speed/frame-omission settings.
// The unsigned max body remains supplied by its canonical owner.
#pragma optimize("ty", on)
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned &max<unsigned>(const unsigned &a, const unsigned &b);
}
#include <vector>
#pragma optimize("", on)
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <class T> class StringBase;

class Rva004036B1
{
public:
	Bool rva004036B1(void *key, float *value, const StringBase<char> *name);	// 0x004036B1
};

class Rva0040450E;
class ModuleData;

class INI;
class AttributeModifierStore
{
public:
	Bool getModifier(Int index, void *key, float *value, const StringBase<char> *name);
	Rva0040450E *replaceModifier(Int index);
	Int rva00214713(Int key);
	static void parseModifierListDefinition(INI *ini);

private:
	unsigned char m_pad00[0xc];
	std::vector<Rva004036B1 *> m_modifiers;		// +0x0C
	std::vector<const ModuleData *> m_retired; // +0x18 native four-byte pointer slots
};

// AttributeModifierStore::getModifier, retail 0x00214762.
Bool AttributeModifierStore::getModifier(Int index, void *key, float *value, const StringBase<char> *name)
{
	if (index < 0 || index > m_modifiers.size() - 1 || m_modifiers[index] == 0)
		return false;
	return m_modifiers[index]->rva004036B1(key, value, name);
}

// Native 0x00214B61..0x00214BB0 and caller 0x00214C4E's 0xD4 allocation
// prove this modifier record constructor. Native 0x00214917 assigns its
// by-value name at +0x10; 0x004043FF releases that name before vector cleanup.
// The 0x4C bulk-zero members are trivial. EH state 1 owns the name.
// These vector views call existing owners for the native three-pointer header;
// they do not identify the modifier vector's element type or its stride.
struct BfmeE16 { unsigned char bytes[16]; };
struct Rva00214B22Record;
namespace _STL
{
template <> class vector<Rva00214B22Record, allocator<Rva00214B22Record> >
{
public:
	~vector();
private:
	unsigned int m_words[3];
};
}

class ModifierVectorHeader
{
public:
	__forceinline ModifierVectorHeader(
		const _STL::allocator<BfmeE16> &alloc = _STL::allocator<BfmeE16>())
	{
		// A valid constructor receiver is nonnull. Placement construction
		// uses this existing member storage and allocates no memory.
		__assume(this != 0);
		typedef _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > Base;
		new(this) Base(alloc);
	}
	__forceinline ~ModifierVectorHeader()
	{
		((_STL::vector<Rva00214B22Record> *)this)->~vector();
	}
private:
	unsigned int m_words[3];
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_bytes[0x4C];
};

class Rva0040450E
{
public:
	friend class AttributeModifierStore;
	Rva0040450E();
	void rva0040450E(int);
	void rva00214917(AsciiString name);
private:
	ModifierVectorHeader m_values;
	unsigned int m_word0C;
	AsciiString m_name10;
	unsigned int m_key14, m_word18;
	Rva0042526Member m_1C, m_68;
	unsigned char m_tailB4[0x20];
};

Rva0040450E::Rva0040450E()
{
	rva0040450E(0);
}

void Rva0040450E::rva00214917(AsciiString name)
{
	m_name10 = name;
}

Rva0040450E *AttributeModifierStore::replaceModifier(Int index)
{
    if (index == -1)
        return 0;
    Rva0040450E *oldModifier = (Rva0040450E *)m_modifiers[index];
    m_retired.push_back(reinterpret_cast<const ModuleData *const &>(oldModifier));
    oldModifier->m_tailB4[0x1D] = 1;
    Rva0040450E *modifier = new Rva0040450E;
    modifier->rva00214917(oldModifier->m_name10);
    modifier->m_key14 = oldModifier->m_key14;
    m_modifiers[index] = (Rva004036B1 *)modifier;
    return modifier;
}

// Native 004043FF's established destructor owner. Its owning member offsets
// agree with the record constructor and replacement; original class name remains unknown.
class Rva002146F7
{
public:
    ~Rva002146F7();
private:
    ModifierVectorHeader m_values;
    unsigned m_word0C;
    AsciiString m_name10;
    unsigned char m_unreconstructed14[0xCC - 0x14];
    unsigned char *m_storageCC;
    unsigned char m_flagsD0[4];
};
Rva002146F7::~Rva002146F7()
{
    if (m_storageCC)
    {
        delete m_storageCC;
        m_storageCC = 0;
    }
}

struct FieldParse;
enum NameKeyType { NAMEKEY_INVALID = -1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern AttributeModifierStore *TheAttributeModifierStore;
int Rva00404715Get();
class INI {
public:
    const char *getNextToken(const char *seps);
    void initFromINI(void *what, const FieldParse *parseTable);
    int getLoadType() const { return m_loadType; }
private:
    char m_pad[8]; int m_loadType;
};
struct Rva004DFCB0Element { unsigned word0; };
class Rva00214ACC { public: void rva00214ACC(Rva004DFCB0Element value); };
class ModifierRecordScope {
public:
    __forceinline ModifierRecordScope() { ((Rva0040450E *)m_storage)->Rva0040450E::Rva0040450E(); }
    __forceinline ~ModifierRecordScope() { ((Rva002146F7 *)m_storage)->~Rva002146F7(); }
private:
    unsigned m_storage[0xD4 / 4];
};
void AttributeModifierStore::parseModifierListDefinition(INI *ini)
{
    const char *name = ini->getNextToken(0);
    bool isNew = true;
    int key = TheNameKeyGenerator->nameToKey(name);
    AttributeModifierStore *store = TheAttributeModifierStore;
    int index = store->rva00214713(key);
    Rva0040450E *modifier;
    if (index == -1) {
        modifier = new Rva0040450E;
    } else if (ini->getLoadType() == 5) {
        modifier = store->replaceModifier(index);
        isNew = false;
    } else {
        ModifierRecordScope temporary;
        ini->initFromINI(&temporary, (const FieldParse *)Rva00404715Get());
        return;
    }
    modifier->rva00214917(AsciiString(name));
    modifier->m_key14 = key;
    ini->initFromINI(modifier, (const FieldParse *)Rva00404715Get());
    if (isNew) {
        Rva004DFCB0Element slot = { (unsigned)modifier };
        ((Rva00214ACC *)TheAttributeModifierStore)->rva00214ACC(slot);
    }
}
