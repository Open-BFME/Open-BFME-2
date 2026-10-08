// cl: /DNDEBUG /MD /EHsc
// RVA 0x008A5360: extract bits 2-9 of the last packed key, offset by two.
class AptValue;
class AptInteger
{
public:
    static AptValue *Create(int value);
};

extern unsigned int Rva008A5250LastKey;

AptInteger *aptPackedKeyFieldAt008A5360()
{
    return (AptInteger *)AptInteger::Create(((Rva008A5250LastKey >> 2) & 0xff) - 2);
}
