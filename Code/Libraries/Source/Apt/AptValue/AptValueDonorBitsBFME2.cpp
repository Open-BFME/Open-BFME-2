// cl: /O2 /MD
// AptValue names from APT0.19.03 Xbox final PDB/MAP (GUID729627e9-b922-4d59-
// 9b50-e116a2834635 age24). Target AptValue constructor/predicates already prove
// an 8-byte polymorphic value with flags at+4. These complete target bodies
// independently measure refCount bits6..17 / isDefined bit4 / GCMark bit1.
// ReleaseValues at6E6D90 calls getRefCount at6E6DCF before selecting delayed
// cleanup or virtual ForceDelete; release-donor callee identity agrees.
// Explicit bool-to-integer normalization is present in both setter bodies.
// ClearReleaseAtEnd at6DBDC0 is already ledgered and is not counted here.
// Unaccessed flag names are deliberately left unspecified.
class AptValue {
    virtual void slot0();
    struct {
        unsigned int unknown0:1;
        unsigned int gcMark:1;
        unsigned int releaseAtEnd:1;
        unsigned int destroyedGC:1;
        unsigned int isDefined:1;
        unsigned int unknown5:1;
        unsigned int refCount:12;
        unsigned int remaining:14;
    } flags;
    void SetDestroyedGC();
public:
    unsigned int getRefCount() const;
    void setIsDefined(bool value);
    void setGCMark(bool value);
};
unsigned int AptValue::getRefCount() const { return flags.refCount; }
void AptValue::setIsDefined(bool value) { flags.isDefined=value?1:0; }
void AptValue::setGCMark(bool value) { flags.gcMark=value?1:0; }

// Original MAP private signature and source230e7c503b5dbf7e name mbDestroyedGC;
// target independent OR8 confirms bit3 in the established flags+4 prefix.
void AptValue::SetDestroyedGC() { flags.destroyedGC=1; }
#pragma comment(linker, "/alternatename:?rva006dbd80@Rva006E0460@@QAEXXZ=?SetDestroyedGC@AptValue@@AAEXXZ")
