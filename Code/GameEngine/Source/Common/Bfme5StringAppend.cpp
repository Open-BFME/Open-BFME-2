// cl: /O1 /Ireference/shims/bfme2_ascii
// Donor: Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76,
// game/GameEngine/Source/Common/Bfme5StringAppend.cpp, compiled /O1.
// Retail 0x00358957 is a complete 38B body: copy the 32-bit argument to a
// local, append one wide character through the matched StringBase worker,
// then call virtual slot +0x10. The owner and virtual method names remain
// unknown; the donor supplies the widget interpretation only.
#include "string_base.h"

class Rva00358957
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    void append(int value);

private:
    void *text;
};

void Rva00358957::append(int value)
{
    int character = value;
    reinterpret_cast<StringBase<unsigned short> *>(&text)->concat(
        reinterpret_cast<const unsigned short *>(&character), 1);
    slot4();
}
