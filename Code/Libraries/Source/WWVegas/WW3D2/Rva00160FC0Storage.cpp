// ?rva00160FC0@Rva00160FC0@@QAEXPAVRva00160FC0Input@@@Z
// cl: /O2 /G7 /DNDEBUG /MD /EHsc
// Native00160FC0..0016104E RET4. Input+58 holds six-pointer records;
// visit five pointers in each record after the first. Virtual slots34/8
// provide the record count and byte counts. Receiver28/2C/30 holds the input
// cache and byte storage/capacity. Original class and method identities unknown.
// Volatile record-pointer access preserves the native repeated loads; the
// original source qualifier is unknown. Explicit array allocation preserves
// the target array operators rather than VC7.1 trivial-array scalar lowering.
#include <string.h>
void *operator new[](unsigned int);
void operator delete[](void *);
class Rva00160FC0Item
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual unsigned int bytes() = 0;
};
class Rva00160FC0Input
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2C() = 0;
    virtual void slot30() = 0;
    virtual int count() = 0;
    char unknown04[0x54];
    Rva00160FC0Item **records;
};
class Rva00160FC0
{
    char unknown00[0x28];
    Rva00160FC0Input *input;
    unsigned char *storage;
    unsigned int capacity;
public:
    void rva00160FC0(Rva00160FC0Input *next);
};
void Rva00160FC0::rva00160FC0(Rva00160FC0Input *next)
{
    if (next != input)
    {
        input = next;
        unsigned int size = 0;
        Rva00160FC0Item *volatile *record = next->records + 6;
        int left = next->count() - 1;
        for (; left > 0; --left)
        {
            for (int i = 0; i < 5; ++i)
                if (record[i])
                    size += record[i]->bytes();
            record += 6;
        }
        if (size > capacity)
        {
            operator delete[](storage);
            capacity = size;
            storage = static_cast<unsigned char *>(operator new[](size));
        }
        memset(storage, 0xFF, size);
    }
}
