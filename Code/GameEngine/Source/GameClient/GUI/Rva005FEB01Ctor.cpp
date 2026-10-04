// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Native 0x5FEB01..0x5FEBC8 (Ghidra199B, RET12) constructs three
// AsciiString members at +0/+4/+8 from argument2, stores argument1 at +C,
// initializes +10/+14/+18 to -1/0/false, then forms the four literal keys.
// The copy, concat, destruction and APT text-setter callees are all recovered.
// Target literal keys establish the timer-display role; the original class
// name and the scalar fields' full meanings are unknown. The queue's
// setUnignoreText identity is refuted by this constructor ABI and call chain.
// Reuses the canonical strings and the verified AptPlayerNameSet.cpp manager
// interface. Native title-key lifetime requires the observed EH cleanup.
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager {
public:
    void bfmeSetText(const AsciiString &,const UnicodeString &,bool);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva005FEB01 {
public:
    Rva005FEB01(int value,const AsciiString &prefix,const UnicodeString &title);
private:
    AsciiString show;
    AsciiString seconds;
    AsciiString minutes;
    int word0C;
    int word10;
    int word14;
    bool flag18;
};
Rva005FEB01::Rva005FEB01(int value_,const AsciiString &prefix,const UnicodeString &title)
: show(prefix),seconds(prefix),minutes(prefix),word0C(value_),word10(-1),word14(0),flag18(false)
{
    show.concat("Show");
    seconds.concat(":Seconds");
    minutes.concat(":Minutes");
    AsciiString titleKey(prefix);
    titleKey.concat(":Title");
    g_bfmeAptWindowManager->bfmeSetText(titleKey,title,false);
}
