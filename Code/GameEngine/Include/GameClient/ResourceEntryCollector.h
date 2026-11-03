/* Target facts (code RVAs, table VAs): constructor 0x004E5610 installs 0x00C623C4 at +0 (0x004E562D), constructs the four-byte list at +4 through 0x004E4F59 (0x004E562A/0x004E5633), and stores float 1.0 at +8 (0x004E5638/0x004E5643). Owner constructor 0x004E7D72 constructs this member at +0x1C (0x004E7DAB/0x004E7DB2); allocation 0x004E7F4F reserves 0x28 bytes for the owner, bounding the member at 0x0C bytes. Destructor 0x004E5654 restores 0x00C623C4 (0x004E5666), clears and destroys the +4 list (0x004E5678/0x004E5683), then restores the one-pure-slot base table 0x00C1C780 (0x004E568B). The base's identity is unproved; the shared pure table does not identify DieModuleInterface. Table 0x00C623C4 contains only callback 0x004E55B9, followed by non-code word 0x3F760000, so there is no virtual destructor slot. The callback's ledger row proves rva004E55B9(ObjectID,float,bool); 0x004E55BF..0x004E55EF passes the unchanged receiver to addEntry, proving the complete-object callback. Row 0x004E551E forwards this+4 to list cleanup 0x004E54ED; row 0x004E5559 copies a Coord3D, float and int into a 0x3C-byte entry and inserts it through 0x004E5526 with this+4. List constructor 0x004E4F78 stores its sentinel pointer at list+0; cleanup 0x004E54ED walks node+0 and destroys node+8, and 0x004E5542 frees the sentinel. The rowed nonvirtual ResourceOwnedEntryList destructor 0x004E560B is a five-byte tail jump to 0x004E5542. No registered complete class owns the constructor, destructor or callback table. Unproved member names remain neutral; collector lifetime methods are declarations because retail calls their bodies out of line. */
#pragma once

struct Coord3D;
enum ObjectID;
struct ResourceOwnedEntryNode;

class ResourceOwnedEntryList
{
public:
    void rva004E54ED();
    void rva004E5542();
    ~ResourceOwnedEntryList() { rva004E5542(); }

    ResourceOwnedEntryNode *m_00;
};

class ResourceEntryCollector
{
public:
    ResourceEntryCollector();
    ~ResourceEntryCollector();
    virtual void rva004E55B9(ObjectID id, float value, bool show);
    __declspec(noinline) void rva004E551E();
    void addEntry(const Coord3D *pos, float value, int index);

    ResourceOwnedEntryList m_04;
    float m_08;
};
