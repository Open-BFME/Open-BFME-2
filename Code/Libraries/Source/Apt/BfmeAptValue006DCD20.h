// Target facts: constructors RVA 0x006DCCC0 and 0x006DCD20 install VA 0x00CEAED0 at +0 and access one dword at +4; scalar constructors 0x006D84C0, 0x006D86A0 and 0x006D8860 put their first payload at +8, bounding this AptValue base to eight bytes, with no evidenced base class.
// The table has 15 slots: RVAs 006DCAC0, 006DCB20, 006CBCD0, 0065CE90, 0073B660, 0065CE90, 00180FD0, 0003FD80, 006C8770, 006CBCF0, 0069E440, 006CBD00, 0003B810, 0003B810, 006DE820. Slots 12/13 are pure; slot 14 is deleting destruction. Destructor 0x006DE350 restores the same table. The placeholder's row 0x006D6340 only jumps there and represents the derived AptValueGC wrapper, not another root table. Slot names below are proven by the AptValue ledger rows; unnamed slots stay neutral.
// Nonvirtual declarations follow the BfmeAptValue006DCD20 ledger rows: predicates 006DBDE0..006DC770, 006DCA60, 006DCC60, 006CBEE0, 006E01A0..006E03A0; casts 006DCD50..006DD320; conversions 006DD360/006DD460; GC roots 006DBB50/006DBC70/006DBCC0/006DBD30; array helpers 006D8A50/006D8AD0/006D94A0/006D95E0/006D9780; CIH helpers 006E04A0/006E0510/006E0F40/006E1540; type setter 006DBBC0. The setter proves type bits 25..31 and the root getter proves bits 18..24 at +4. Accessor 006E04A0 reads a CIH extension at +4C and its pointee +10; checkedString 006DCE50 selects this or an extension at +20. Those extensions are not base fields. Existing symbol spellings factorySetString and rva006DD6C0 call rowed 006CBF70 and 006DD6C0 from 006EAB6F/006EABAB and 006D7512/006D7541/006D7CB1/006DA0F4. AptLinker at 006D199F and AptXml at 006F2153/006F216B call the private setter.
#pragma once

class EAStringC;
class AptValue;
struct AptNativeHash;

class BfmeAptValue006DCD20
{
public:
    BfmeAptValue006DCD20(int type);
    BfmeAptValue006DCD20(int type, unsigned int unused);

    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const, const EAStringC *const, AptValue *const);
    virtual void vslot09();
    virtual void vslot10();
    virtual void DestroyGCPointers();
    virtual bool vslot12() const = 0;
    virtual void vslot13() const = 0;
    virtual ~BfmeAptValue006DCD20();

    unsigned int getGCRootCount() const;
    void setGCRootCount(unsigned int);
    void incrementGCRootCount();
    void decrementGCRootCount();
    bool isUndefined() const;
    int isLookup() const;
    int isInteger() const;
    int isRegister() const;
    int isFloat() const;
    int isString() const;
    int isBoolean() const;
    int isNativeFunction() const;
    int isScriptFunction() const;
    int isDate() const;
    int isKey() const;
    int isMath() const;
    int isScriptColour() const;
    int isObject() const;
    int isPrototype() const;
    int isTextFormat() const;
    int isMovieClip() const;
    int isStage() const;
    int isArray() const;
    int isSound() const;
    int isCharacterInst() const;
    int isXmlNode() const;
    int isXml() const;
    int isXmlAttributes() const;
    int isLoadVars() const;
    bool isCIH(bool = false) const;
    int rva006DC300() const;
    int rva006DC350() const;
    int rva006DC490() const;
    int rva006DCC60(bool = false) const;
    int rva006CBEE0(bool = false) const;
    int rva006E01A0(bool = false) const;
    int rva006E02B0() const;
    int rva006E0260() const;
    int rva006E0300() const;
    int rva006E0350() const;
    int rva006E03A0() const;
    int rva006DBFA0() const;
    bool rva006DCA60() const;
    int toInteger() const;
    void factorySetString(const char *);
    void rva006DD6C0(EAStringC &);
    void rva006DD6C0(EAStringC *);
    float rva006DD460();
    void *rva006E04A0() const;
    int rva006E0510() const;
    void *rva006E0F40() const;
    void rva006E1540();
    BfmeAptValue006DCD20 *rva006D8A50(int);
    void SetAt(int, BfmeAptValue006DCD20 *);
    void rva006D94A0();
    void rva006D95E0(int, BfmeAptValue006DCD20 *);
    bool rva006D9780(BfmeAptValue006DCD20 *, EAStringC *, BfmeAptValue006DCD20 *);
    BfmeAptValue006DCD20 *checkedLookup();
    BfmeAptValue006DCD20 *checkedInteger();
    BfmeAptValue006DCD20 *checkedRegister();
    BfmeAptValue006DCD20 *checkedFloat();
    BfmeAptValue006DCD20 *checkedString();
    BfmeAptValue006DCD20 *rva006DCEA0();
    BfmeAptValue006DCD20 *rva006DCEE0();
    BfmeAptValue006DCD20 *rva006DCF20();
    BfmeAptValue006DCD20 *rva006DCF60(bool = false);
    BfmeAptValue006DCD20 *rva006DCFA0();
    BfmeAptValue006DCD20 *rva006DCFE0();
    BfmeAptValue006DCD20 *rva006DD020();
    BfmeAptValue006DCD20 *rva006DD060();
    BfmeAptValue006DCD20 *rva006DD0A0();
    BfmeAptValue006DCD20 *rva006DD0E0();
    BfmeAptValue006DCD20 *rva006DD120();
    BfmeAptValue006DCD20 *rva006DD160();
    BfmeAptValue006DCD20 *rva006DD1A0();
    BfmeAptValue006DCD20 *rva006DD1E0();
    BfmeAptValue006DCD20 *rva006DD220();
    BfmeAptValue006DCD20 *rva006DD260();
    BfmeAptValue006DCD20 *rva006DD2A0();
    BfmeAptValue006DCD20 *rva006DD2E0();
    BfmeAptValue006DCD20 *rva006DD320();

    unsigned int field04;

private:
    friend class AptLinker;
    friend class AptXml;
    friend void bfmeAnchorAptValueSetType(BfmeAptValue006DCD20 *, int);
    void setTypeAt006DBBC0(int);
};
