// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8D06@Rva002BA8F1Logic@@QAEXPAVXfer@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// recovered 2026-10-05 from packet 0x002B8D06 216B lane=unlock.
// Evidence: erase via rowed void* 0x0031BD55 then reserve 0x002B712E and push_back 0x004DFCB0 for vector<ModuleData*>; LivingWorldArmyID helper 0x00318D1E; lookup via pin 0x002B488E Rva002BA8F1Logic; Xfer slots 0x28 version {1,1} 0x04 isLoading 0x7C unsigned count per Rva003F2394Xfer donor shape; callers 0x002BB428 0x002BB437 0x003F3EBC 0x003F5D13.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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
	char m_pad[0x20];
	int m_armyID;
};

struct Rva002B488EResult
{
	char m_pad[0x20];
	int m_armyID;
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int id);
	void rva002B8D06(Xfer *xfer, _STL::vector<const ModuleData *> *vec);
};

void __cdecl XferLivingWorldArmyID(Xfer *xfer, int *value);

void Rva002BA8F1Logic::rva002B8D06(Xfer *xfer, _STL::vector<const ModuleData *> *vec)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	if (xfer->isLoading()) {
		int count = 0;
		xfer->xferInt(count);
		((_STL::vector<void *> *)vec)->erase(((_STL::vector<void *> *)vec)->begin(), ((_STL::vector<void *> *)vec)->end());
		vec->reserve(count);
		for (int i = 0; i < count; ++i) {
			int armyID;
			XferLivingWorldArmyID(xfer, &armyID);
			const ModuleData *found = (const ModuleData *)rva002B488E(armyID);
			if (found != 0) {
				vec->push_back(found);
			}
		}
	} else {
		int count = (int)vec->size();
		xfer->xferInt(count);
		for (int i = 0; i < count; ++i) {
			int armyID = (*vec)[i]->m_armyID;
			XferLivingWorldArmyID(xfer, &armyID);
		}
	}
}
