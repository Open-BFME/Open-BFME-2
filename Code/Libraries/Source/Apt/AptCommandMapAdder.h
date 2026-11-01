// Target facts (code addresses are RVAs): AptCommandMapAdder has no virtual functions. Its constructor is the 19-byte fold at 0x001F81BF, called on the command-map member at 0x00510BA2 (+0x14) and 0x0057C18D (+0x0C); the latter owner writes its following flag at +0x18 (0x0057C196), bounding the helper to 0x0C bytes. The constructor calls the vector-base constructor 0x00211E58 without adjusting this; that constructor clears +0/+4 and initializes +8 through 0x0014F3C4. Neither helper lifetime body stores a vptr. The table stores at 0x00510B9C (VA 0x00C65670) and 0x0057C176 (VA 0x00C6F2D4) target their enclosing objects, outside the helper.
// The rowed nonvirtual destructor 0x0052413E calls clear 0x00523F22 at 0x00524150 and vector<AsciiString> destruction 0x0002CC70 at 0x0052415C, both with unchanged this. HUD::Impl calls that destructor on its +0x0C member at 0x0042D9D1. Clear compares +0/+4 at 0x00523F4E..0x00523F50, removes four-byte names through AptPlayer::RemoveCommandMap (0x00224455) at 0x00523F3D, and decrements +4 by four at 0x00523F42. There is no destructor table or virtual slot belonging to this class.
// AddCommandMap is rowed at 0x0052458E with (const AsciiString &, AptRef<AptCommandMap>) and ret 8. It forwards to AptPlayer::AddCommandMap (0x002243E3), then calls vector<AsciiString>::push_back (0x0002DBE6) on unchanged this at 0x005245CF. That vector compares +4/+8 at 0x0002DBEC..0x0002DBEF and advances +4 by four at 0x0002DBFD. These accesses establish a string vector at +0 with begin/finish/allocation-end words at +0/+4/+8; its original member name is unproven. field00 is opaque, four-byte-aligned vector storage; the lifetime methods remain declarations so callers use their existing out-of-line bodies.
#ifndef BFME2_APT_APTCOMMANDMAPADDER_H
#define BFME2_APT_APTCOMMANDMAPADDER_H

class AsciiString;
class AptCommandMap;
template <class T> class AptRef;

class AptCommandMapAdder
{
public:
    AptCommandMapAdder();
    ~AptCommandMapAdder();
    void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
    unsigned int field00[3];
};

#endif
