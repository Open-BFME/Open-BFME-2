// Target facts: ObjectFilter is a plain, nonvirtual four-byte pool-index handle with no base. RVA 0x00360CED reads a signed index at +0; 0x0036229A tests it against -1 and 0x003622C8 multiplies it by 0x94. The constructor at 0x003623E5 writes only +0 (0x003623F8/0x00362421), and the destructor at 0x00360D26 forwards to 0x00360CB0, which resets that word. Neither installs a vtable. The 12-byte category stride at 0x00220D79/0x00220DAE and filter at category+8 (0x00220D9B) bound its extent to four bytes.
// Target methods (RVAs): isValid 0x00360CED, rva00360D2E 0x00360D2E, isForbidden 0x00361817, testTemplate 0x003618B9, testKindOf 0x00361B12, DoXfer 0x00362255, DoNamesXfer 0x00361533, DoTemplatesXfer 0x00360DB9 and static rva003611EFResolveNames 0x003611EF have ledger rows with these declarations. Constructor/destructor rows use Rva003623E5Member/Rva00360D26Member, so no ObjectFilter special-member symbol is asserted here. The field's source name is unknown.
// Target record distinction: 0x003623E5 constructs/destroys a separate 0x94-byte stack record through 0x00360F55/0x00360FDB and interns it at 0x00362411. The static resolver's argument is that record, as 0x0036235B/0x0036235C prove; its ObjectFilter pointer spelling preserves the ledger ABI and does not describe a handle's layout.
#pragma once

#ifndef __BFME2_OBJECTFILTER_H_
#define __BFME2_OBJECTFILTER_H_

class AsciiString;
class Player;
class ThingTemplate;
class Xfer;
enum KindOfType;
template<int N> class BitFlags;
namespace _STL {
template<class T> class allocator;
template<class T, class Allocator> class vector;
}

class ObjectFilter
{
public:
    bool isValid() const;
    void rva00360D2E(AsciiString &out) const;
    bool isForbidden(KindOfType);
    bool testTemplate(const ThingTemplate *, const Player *, const Player *);
    bool testKindOf(const BitFlags<218> *, const Player *, const Player *);
    void DoXfer(Xfer *);
    void DoNamesXfer(Xfer *, _STL::vector<AsciiString, _STL::allocator<AsciiString> > *);
    void DoTemplatesXfer(Xfer *, _STL::vector<ThingTemplate *, _STL::allocator<ThingTemplate *> > *,
                         _STL::vector<ThingTemplate *, _STL::allocator<ThingTemplate *> > *);
    static void rva003611EFResolveNames(ObjectFilter *);

    int m_objectFilterSlot00;
};

#endif
