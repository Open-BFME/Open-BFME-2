// cl: /O1 /G7 /MD /EHsc
// Native FlashRegionsEvent record: parser4E14E8 creates the 16-byte local,
// ctor4E14CD/20 installs VA C619A0, and copy52BB9A/33 preserves fields4/8/C.
// C619A0 contains one pointer, VA8E19E7, followed by the FlashTime literal.
// Its deleting destructor4E19E7/29 restores that table and conditionally
// calls the verified scalar delete2FD60; the adjacent complete destructor
// 4E14E1/7 consists of the same vptr restoration and RET.
// This address-derived class is an ABI view of that proven local record;
// original class identity remains unknown. No copy/constructor identity is
// inferred from adjacency; existing rowed constructors remain their owners.
class Rva004E14E1FlashRecord
{
public:
    virtual ~Rva004E14E1FlashRecord();
private:
    unsigned opaque04;
    bool opaque08;
    unsigned opaque0C;
};
// ??1Rva004E14E1FlashRecord@@UAE@XZ present-unmatched
// Cleanup emits7B also covered by the existing generic apply row4E14E1;
// keep that row and claim no second function at its address.
Rva004E14E1FlashRecord::~Rva004E14E1FlashRecord()
{
}
