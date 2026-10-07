// cl: /O1 /DNDEBUG /MD /EHsc
// Existing neutral pin used by the rowed 0x3F20E5 caller. Native complete
// boundary 0x3F076D..0x3F07CE is 97 bytes, with no stack arguments.
// The +0x170/+0x174 plot-pointer vector agrees with the named sibling
// LivingWorldRegion::GetBuildingByIndex. The method spelling is unresolved.
// Rva004FC21AOwner is the independently rowed 36-byte countdown helper:
// it observes a pointer at +0x20 and a byte flag at +0x34.

class Rva004FC21AOwner
{
public:
    void rva004FC21A();
    unsigned char prefix[0x20];
    void *building;
    unsigned char middle[0xC];
    int countdown;
    unsigned char flag;
};

struct Rva003F076DVector
{
    // ?Rva003F076DVector::size absent-from-retail
    unsigned size() const { return end - begin; }
    // ?Rva003F076DVector::operator[] absent-from-retail
    Rva004FC21AOwner *operator[](unsigned index) const { return begin[index]; }
    Rva004FC21AOwner **begin;
    Rva004FC21AOwner **end;
    Rva004FC21AOwner **storage;
};

class Rva003F076D
{
public:
    void rva003F076D();
private:
    unsigned char prefix[0x170];
    Rva003F076DVector plots;
    unsigned char middle[0x1A3 - 0x17C];
    unsigned char flag;
};

// ?rva003F076D@Rva003F076D@@QAEXXZ
void Rva003F076D::rva003F076D()
{
    for (unsigned i = 0; i < plots.size(); ++i)
    {
        Rva004FC21AOwner *plot = plots[i];
        if (plot->flag && plot->building)
        {
            plot->rva004FC21A();
            if (plot->flag && plot->building)
                flag = 1;
            break;
        }
    }
}
