// cl: /DNDEBUG /MD
// Object-side ammo-availability gate called by Weapon::isAmmoReady (retail
// 0x002CC3FF). The body advances this by 0x330 and null-checks a pointer the
// callee fetches at +0x24 there; both identities are unproven so both names
// are address-derived. The callee stays an opaque pin for this caller: its
// four-byte body is also used by NetWrapperCommandMsg::getDataOffset, which
// does not make the Object-side subobject a network command.
typedef bool Bool;

// Host of the +0x24 fetch at retail 0x00091A56. One ledger body is retained
// under the target-supported network identity; this alias preserves the
// independently observed Object-side call without claiming a shared owner.
class Rva00091A56DwordField
{
public:
    int get() const;
};

class Object
{
public:
    Bool rva0028AF65() const;
};

// ?rva0028AF65@Object@@QBE_NXZ @0x0028AF65 (17B)
Bool Object::rva0028AF65() const
{
    const Rva00091A56DwordField *slot =
        (const Rva00091A56DwordField *)((const char *)this + 0x330);
    return (Bool)slot->get();
}
