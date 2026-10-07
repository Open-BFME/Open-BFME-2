// cl: /DNDEBUG /MD /EHsc
// Reconstruction of the predicate at 0x00318CA4 (41B): when the global's
// +0xF4 word is zero, forward the owner's +0x54 word to the +0x98 helper
// (callee 0x002E0BC0, pinned from the retail call) and negate the byte
// result. The global matches the TheLivingWorldLogic lead (0x009FEF10);
// all names are address-derived and the offsets are target facts.
// The native provider normalizes its bool result with movzx eax,al at
// 0x002E0BE0. Keep each caller's byte-sized test while naming its int ABI.
class Rva002E071E {
public:
    int rva002E0BC0(int value);
};

class Rva00318CA4Global {
public:
    unsigned char pad00[0x98];
    Rva002E071E* m_98;
    unsigned char pad9C[0xF4 - 0x9C];
    int m_f4;
};

extern Rva00318CA4Global* TheLivingWorldLogic;

class Rva00318CA4Owner {
public:
    unsigned char rva00318CA4();
private:
    unsigned char pad00[0x54];
    int m_54;
};

unsigned char Rva00318CA4Owner::rva00318CA4()
{
    if (TheLivingWorldLogic->m_f4 != 0)
        return 0;
    int value = m_54;
    Rva002E071E* helper = TheLivingWorldLogic->m_98;
    return !(unsigned char)helper->rva002E0BC0(value);
}
