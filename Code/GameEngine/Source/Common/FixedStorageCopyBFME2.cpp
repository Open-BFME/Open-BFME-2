// cl: /DNDEBUG /MD
// BFME2 fixed-storage member copies. Complete retail constructors copy
// exactly 0x1C or 4 bytes through memcpy; application type names are unknown.
// As with the BFME1-derived WeaponTemplateSetHead copy, keep these helpers
// separate from their owning records so callers preserve the out-of-line ABI.
extern "C" void *memcpy(void *, const void *, unsigned);

class BfmeFixedStorage0004543D {
    char m_bytes[28];
public:
    __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
BfmeFixedStorage0004543D::BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) { memcpy(this, &other, sizeof(*this)); }

class BfmeFixedStorage002CF0F0 {
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
BfmeFixedStorage002CF0F0::BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other) { memcpy(this, &other, sizeof(*this)); }

// BF1 9cb donors unchanged through current f989 Rva007F90B0.cpp and the one-byte ByteAC copy in
// Gen_t_00776240CopyConstructor.cpp expose these primitive copy leads.
// Target222695..2226A2 and56DE10..56DE1F are independently full RET4
// leaves after prior RET16/RET8. Both return the receiver in EAX while
// copying precisely one witnessed field. Native owners, full object sizes
// and constructor-versus-method roles remain unknown. These independent
// prefix views claim only the actual byte0 or dword4 accesses; no donor
// aliases, ownership or unrelated member types are transferred.
class Rva00222695ByteField
{
public:
    Rva00222695ByteField *copyField(const Rva00222695ByteField *other);
private:
    unsigned char value;
};
Rva00222695ByteField *Rva00222695ByteField::copyField(const Rva00222695ByteField *other)
{
    value = other->value;
    return this;
}
class Rva0056DE10DwordField
{
public:
    Rva0056DE10DwordField *copyField(const Rva0056DE10DwordField *other);
private:
    unsigned char unknown[4];
    unsigned value;
};
Rva0056DE10DwordField *Rva0056DE10DwordField::copyField(const Rva0056DE10DwordField *other)
{
    value = other->value;
    return this;
}
