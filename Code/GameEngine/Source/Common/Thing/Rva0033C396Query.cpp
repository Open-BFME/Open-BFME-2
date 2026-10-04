// cl: /O1 /DNDEBUG /MD /EHsc
// BFME1 donor: Open-BFME/Open-BFME-1@1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv975.cpp, bfmeGo975D; adapted call names
// to the existing BFME2 definitions. The donor's wrapper name is synthetic.
// Target evidence: Ghidra entry0x0033C396/38B; entry call0x004763D5;
// global VA0x00DFF000, lookup0x002D06CA, equivalence0x0033BB04, ret4.
// The known lookup accepts an AsciiString pointer and returns the template
// consumed by the rowed ThingTemplate::isEquivalentTo. The unchanged receiver
// is used as that comparison's ThingTemplate. The original wrapper name and
// its complete receiver layout are unknown. Const/bool are C++ expression
// choices supported by the comparison, not recovered original spellings.
class AsciiString;
class ThingFactory;
class ThingTemplate
{
public:
    bool isEquivalentTo(const ThingTemplate *other) const;
};
class Rva002D06CA
{
public:
    void *rva002D06CA(const AsciiString *key);
};
extern ThingFactory *TheThingFactory;
class Rva0033C396
{
public:
    bool test(const AsciiString &name) const;
};
bool Rva0033C396::test(const AsciiString &name) const
{
    const ThingTemplate *other = static_cast<const ThingTemplate *>(
        reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(&name));
    if (other)
        return reinterpret_cast<const ThingTemplate *>(this)->isEquivalentTo(other);
    return false;
}