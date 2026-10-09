// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class Rva004362B0StrideAdd {
public:
    static void add(int *value, int index);
};

void Rva004362B0StrideAdd::add(int *value, int index)
{
    *value += index * 8;
}

// BF1 9cbfb551fe Rva002DF9B0Advance/Rva002DFC10Advance and
// Rva002E3220Advance/Rva002E3F50Advance are current clean donor leads.
// Native33174B..331759 and333366..333374 are independently complete
// cdecl leaves after RET. Stackarg4 points to an address slot; arg8 is
// multiplied by12 or20 and added to that slot. Original helper names and
// pointed element types remain unknown; byte-pointer arithmetic preserves
// the independently measured strides without inventing an element layout.
void Rva0033174BAdvance(unsigned char **slot, int count)
{
    *slot += count * 12;
}
void Rva00333366Advance(unsigned char **slot, int count)
{
    *slot += count * 20;
}

// f989 BF1 OnlineShellShutdown.cpp O2/x87/G6 emits an iterator-advance lead.
// Native6CFEA0..6CFEA6 is independently complete after INT3 padding and
// before more padding: it advances receiver's raw address slot by4 and
// returns that receiver. Original container/element/owner identity remains
// unknown; this prefix view transfers only the witnessed byte stride.
class Rva006CFEA0Iterator
{
public:
    Rva006CFEA0Iterator &advance();
private:
    unsigned char *position;
};
Rva006CFEA0Iterator &Rva006CFEA0Iterator::advance()
{
    position += 4;
    return *this;
}
