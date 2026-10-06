// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?xfer@Rva0040DB52@@MAEXPAVXfer@@@Z retail 0x0040E6F6 132B
// Slot 3 xfer of Rva0040DB52 (vtable 0x008394CC): version {1,1} then +0x04 +0x0c(bool) +0x10(ModuleData) then isLoading erase of ScienceType vec at +0x14 and ptr vec at +0x20 then vector helpers.
// Evidence: chain lane calls 0x0040E269 now ready, vslot slot 3, callees erase ScienceType 0x00532803 erase voidptr 0x0031BD55 helpers 0x003F2394 0x0040E269 rowed.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModuleData;
enum ScienceType
{
	SCIENCE_INVALID = -1,
	SCIENCE_0 = 0
};

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
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20(int *value);
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
	virtual void xferModuleData(const ModuleData *&value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(Bool *value);
};

#include "Common/Snapshot.h"

Xfer *Rva003F2394Xfer(Xfer *xfer, _STL::vector<ScienceType> *vec);
Xfer *Rva0040E269Xfer(Xfer *xfer, _STL::vector<const ModuleData *> *vec);

class Rva0040DB52 : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_04;
	char m_pad08[4];
	Bool m_0C;
	char m_pad0D[3];
	const ModuleData *m_10;
	_STL::vector<ScienceType> m_vec14;
	_STL::vector<void *> m_vec20;
};

void Rva0040DB52::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	xfer->slot20(&m_04);
	xfer->xferBool(&m_0C);
	xfer->xferModuleData(m_10);
	if (xfer->isLoading()) {
		m_vec14.clear();
		m_vec20.clear();
	}
	Rva003F2394Xfer(xfer, &m_vec14);
	Rva0040E269Xfer(xfer, reinterpret_cast<_STL::vector<const ModuleData *> *>(&m_vec20));
}
