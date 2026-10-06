// cl: /MD
// Switch predicate at RVA 0x006DCA60 (32 bytes + tables).
// Evidence: same this as rowed ?isUndefined@BfmeAptValue006DCD20@@QBE_NXZ via
// caller at 0x00706A94 (tests isUndefined then this body); reads flags at +4
// with signed type extraction (sar 0x19); jump table at 0x006DCA80 and byte
// table at 0x006DCA88 select mov al,1 vs xor al,al; true types
// 1/9/21/22/26/27/29/30/33/35/36/41/42/43/44 measured from retail tables.
class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
public:
    bool rva006DCA60() const;
};
bool BfmeAptValue006DCD20::rva006DCA60() const
{
    int type = static_cast<int>(m_flags) >> 25;
    switch (type) {
    case 1:
    case 9:
    case 21:
    case 22:
    case 26:
    case 27:
    case 29:
    case 30:
    case 33:
    case 35:
    case 36:
    case 41:
    case 42:
    case 43:
    case 44:
        return true;
    default:
        return false;
    }
}
