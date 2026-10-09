// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native41926B..4192A4 57B constructs an AsciiString key and a20B record.
// The caller4193E5 allocates24B and uses the key at0/data at4, then calls
// existing Rva0022D214 destructor22D214. The record copy4191E5 is already
// owned; constructor and destructor names remain honest address-derived views.
// The AutoResolveCombatChain registration7B00C7 and Target parser tableC3A9A8
// establish this family, without recovering the original pair template name.
#include "ascii_string.h"
struct Rva004191E5 {Rva004191E5(const Rva004191E5&);unsigned char data[20];};
class Rva0022D214 {
public:Rva0022D214(const AsciiString&,const Rva004191E5&);~Rva0022D214();
private:AsciiString key;Rva004191E5 value;
};
Rva0022D214::Rva0022D214(const AsciiString &n,const Rva004191E5 &v):key(n),value(v){}
