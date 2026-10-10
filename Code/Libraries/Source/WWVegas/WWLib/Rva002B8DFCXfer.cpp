// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8DFC@Rva002BA8F1Logic@@QAEXPAVXfer@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// Player-id sibling of rva002B8D06 (same skeleton, same erase/reserve/push_back callees): ids go through the
// rowed XferLivingWorldPlayerID 0x002034C4 and resolve through the rowed find 0x002B51F8; the saved id is read at +0x14 of each entry.
// Evidence: retail frame and callees read at the REL32s; skeleton from the rowed rva002B8D06.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(int &value);
};

class ModuleData
{
public:
	char m_pad[0x14];
	int m_playerID;
};

class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	void rva002B8DFC(Xfer *xfer, _STL::vector<const ModuleData *> *vec);
};

void XferLivingWorldPlayerID(Xfer *xfer, int *value);

void Rva002BA8F1Logic::rva002B8DFC(Xfer *xfer, _STL::vector<const ModuleData *> *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	if (xfer->isLoading()) {
		int count;
		xfer->xferInt(count);
		((_STL::vector<void *> *)vec)->erase(((_STL::vector<void *> *)vec)->begin(), ((_STL::vector<void *> *)vec)->end());
		vec->reserve(count);
		for (int i = 0; i < count; ++i) {
			int armyID;
			XferLivingWorldPlayerID(xfer, &armyID);
			const ModuleData *found = (const ModuleData *)find(armyID, 0);
			if (found != 0) {
				vec->push_back(found);
			}
		}
	} else {
		int count = (int)vec->size();
		xfer->xferInt(count);
		for (int i = 0; i < count; ++i) {
			int armyID = (*vec)[i]->m_playerID;
			XferLivingWorldPlayerID(xfer, &armyID);
		}
	}
}
