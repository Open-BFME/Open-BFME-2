// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 0x0040EC7C..0x0040ECCD: one-type adapter for the existing
// HasDelayedCarryoverUnitOfTypes call view at 0x0040CC3C. The original
// adapter name is unproven. The temporary's identity is established by
// ObjectTypes ctor 0x003769F9, addObjectType 0x00376B50 and dtor 0x00376ADF.
#include "ascii_string.h"

class ObjectTypes
{
public:
    ObjectTypes();
    virtual ~ObjectTypes();
    void addObjectType(const AsciiString &name);

private:
    // Verified 0x14-byte stack object: vptr, name and three vector pointers.
    AsciiString m_listName;
    void *m_objectTypes[3];
};

enum ObjectID { INVALID_OBJECT_ID = 0 };

class Rva0040D701ArmySummary
{
public:
    bool rva0040EC7C(const AsciiString &name);
    ObjectID rva0040E83A(const AsciiString &name);
    ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes *types);
    bool HasDelayedCarryoverUnitOfTypes(ObjectTypes *types);
};

bool Rva0040D701ArmySummary::rva0040EC7C(const AsciiString &name)
{
    ObjectTypes types;
    types.addObjectType(name);
    return HasDelayedCarryoverUnitOfTypes(&types);
}

// Native40E83A-40E88B constructs the same ObjectTypes temporary and returns
// the complete ObjectID from the existing pinned spawn method at40E589.
// The adapter's original name remains unknown; WB confirms its callgraph.
ObjectID Rva0040D701ArmySummary::rva0040E83A(const AsciiString &name)
{
    ObjectTypes types;
    types.addObjectType(name);
    return SpawnOneDelayedCarryoverUnit(&types);
}
