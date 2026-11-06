// cl: /MD
// AptObject slot 11 forwards directly to AptValueWithHash slot 11.
// Retail vtables 0x008EA264 and 0x008EA228 establish the two owners.

class AptValue;

class EAStringC;

class AptValueWithHash
{
public:
    virtual void DestroyGCPointers();
};

// Retail vtable 0x008EA264: slot 7 objectMemberLookup, slot 11 DestroyGCPointers.
class AptObject : public AptValueWithHash
{
public:
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual void DestroyGCPointers();
};

void AptObject::DestroyGCPointers()
{
    AptValueWithHash::DestroyGCPointers();
}
