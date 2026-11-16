// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@ObjectDefectionHelper@@UBE?AW4NameKeyType@@XZ @0x28C992
// (69B): cached pool-name key for ObjectDefectionHelper. The class
// identity comes from the pool-name string the body pushes
// ("ObjectDefectionHelper"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Xfer;

class ObjectDefectionHelper
{
	// Retail's primary vftable 0x00BFBD40: slot 0 deleting destructor, 1 loadPostProcess, 2 GetSnapshotName,
	// 3 xfer, 4 getModuleNameKey (the class's full declaration: its Ctor.cpp view).
public:
	virtual ~ObjectDefectionHelper();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ObjectDefectionHelper@@UBE?AW4NameKeyType@@XZ
NameKeyType ObjectDefectionHelper::getModuleNameKey() const
{
	static NameKeyType TheObjectDefectionHelperPoolKey =
		TheNameKeyGenerator->nameToKey("ObjectDefectionHelper");
	return TheObjectDefectionHelperPoolKey;
}
