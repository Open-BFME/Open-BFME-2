// ?rva002B3A9C@Rva002B3A9C@@QAEHXZ
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct Rva002B3A9CResult
{
    unsigned char pad00[0x0C];
    int value0C;
    int getValue() const { return value0C; }
};

struct Rva002B3A9CHandle
{
    Rva002B3A9CResult *value;
    ~Rva002B3A9CHandle()
    {
        if (value)
            ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)value + 0xAC));
    }
};

class Rva002B3A9CItem
{
public:
    Rva002B3A9CHandle rva0031996D(void *key);
    unsigned char pad00[0x18];
    int key18;
};

inline const int &Rva002B3A9CMax(const int &a, const int &b)
{
    return a < b ? b : a;
}

class Rva002B3A9C
{
public:
    int rva002B3A9C();
private:
    unsigned char pad00[8];
    Rva002B3A9CItem **begin;
    Rva002B3A9CItem **end;
    unsigned size() const { return (unsigned)(end - begin); }
};

// Native 0x002B3A9C..0x002B3B07, ret: maximum of result +0x0C
// over the +8/+C pointer vector. Each lookup uses the item's +0x18 key;
// its returned non-null handle releases the embedded reference at +0xAC.
// Boundaries, layouts and calls are target evidence; identities are unknown.
int Rva002B3A9C::rva002B3A9C()
{
    int maximum = 0;
    for (unsigned i = 0; i < size(); ++i)
    {
        Rva002B3A9CItem *item = begin[i];
        Rva002B3A9CHandle result = item->rva0031996D(&item->key18);
        Rva002B3A9CResult *found = result.value;
        if (found)
        {
            maximum = Rva002B3A9CMax(maximum, found->getValue());
        }
    }
    return maximum;
}
