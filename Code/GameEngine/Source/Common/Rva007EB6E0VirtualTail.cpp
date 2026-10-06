// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Donor: Open-BFME-1 game/GameEngine/Source/Common/Rva007EB6E0VirtualTail.cpp
// (verified BFME 1 pointer; source identity remains address-derived).
// Target evidence: BFME 2 body at 0x00658670 has the same 16 bytes; its
// surrounding bytes show a preceding routine and three int3 bytes before it.
// The target has no named direct callers, so class and method labels remain
// provisional. Only the virtual calls and +0x6A8 access are byte-supported.
class Rva007EB6E0Object
{
public:
    virtual Rva007EB6E0Object *unused0(void);
    virtual Rva007EB6E0Object *advance(void);
    void invoke(void);
private:
    char m_pad0[0x6A4];
    Rva007EB6E0Object *m_next;
};

void Rva007EB6E0Object::invoke(void)
{
    Rva007EB6E0Object *result = advance();
    result->m_next->advance();
}
