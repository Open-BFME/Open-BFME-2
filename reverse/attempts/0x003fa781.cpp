// ?rva003FA781@Rva003FA835@@QAEXH@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native 003FA781..003FA7D3, RET4. The rowed caller at 00210E5B
// establishes the Rva003FA835 receiver and a full argument word; this body
// tests only its low byte. State+14 and elapsed+18 are measured fields.
// The pointer wrapper+8 calls the folded getter at 0035C95F. Its original
// template instantiation remains unknown; this is only an address-derived
// call ABI view, not another asserted identity for the folded function.
// The returned object's float+14 is measured. The constructor at 003FA745
// is a possible type lead, but no linkage to this getter is yet established.
class Rva003FA781Parameters
{
public:
    char unknown00[0x14];
    float value14;
};

class Rva0035C95FOverrideView
{
public:
    const Rva003FA781Parameters *rva0035C95F() const;
private:
    void *pointer;
};

class Rva003FA835
{
public:
    void rva003FA781(int value);
    void rva003FA705(void *object, float value);
private:
    char unknown00[8];
    Rva0035C95FOverrideView pointer08;
    unsigned int unknown0C;
    void *object10;
    bool state14;
    char unknown15[3];
    float elapsed18;
};

void Rva003FA835::rva003FA781(int value)
{
    if (state14 && !(unsigned char)value)
    {
        state14 = false;
        elapsed18 = 0.0f;
        rva003FA705(object10, pointer08.rva0035C95F()->value14);
    }
    else if (!state14 && (unsigned char)value)
    {
        state14 = true;
        elapsed18 = 0.0f;
    }
}
