// cl: /O1 /arch:SSE /G7 /MD
// Three adjacent 15-byte nullable-pointer predicates (retail 0x002E6AA7, 0x002E6AB6, 0x002E6AC5):
// each loads a pointer from the receiver and, when it is non-null, reports whether one of its
// dwords (offsets 0x14, 0x20 and 0x24) is non-zero. Owner and field identities are unresolved
// (BFME1 9cbfb551 PathfindCell nullable-pointer operations are a semantic lead only), so the
// classes carry address names. Codegen: the conditional-expression form keeps `test ecx,ecx`
// on the pointer; the if/assign form compares it against the zeroed result register.

class Rva002E6AA7Nonzero
{
public:
    bool nonzero() const;
    const unsigned *m_pointee;
};
// ?nonzero@Rva002E6AA7Nonzero@@QBE_NXZ @0x002E6AA7 15B
bool Rva002E6AA7Nonzero::nonzero() const
{
    return m_pointee ? m_pointee[5] != 0 : false;
}

class Rva002E6AB6Nonzero
{
public:
    bool nonzero() const;
    const unsigned *m_pointee;
};
// ?nonzero@Rva002E6AB6Nonzero@@QBE_NXZ @0x002E6AB6 15B
bool Rva002E6AB6Nonzero::nonzero() const
{
    return m_pointee ? m_pointee[8] != 0 : false;
}

class Rva002E6AC5Nonzero
{
public:
    bool nonzero() const;
    const unsigned *m_pointee;
};
// ?nonzero@Rva002E6AC5Nonzero@@QBE_NXZ @0x002E6AC5 15B
bool Rva002E6AC5Nonzero::nonzero() const
{
    return m_pointee ? m_pointee[9] != 0 : false;
}
