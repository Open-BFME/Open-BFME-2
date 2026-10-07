// cl: /O1 /Ob0 /EHsc /MD
// Reference-derived float comparison. Target preceding RET boundary and exact
// bytes establish the access at +0 and comparison; remaining layout is unknown.
struct Rva0058722AElement
{
    float key;
    bool operator<(const Rva0058722AElement &b) const;
};
bool Rva0058722AElement::operator<(const Rva0058722AElement &b) const
{
    return key < b.key;
}
