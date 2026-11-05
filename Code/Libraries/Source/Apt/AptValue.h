// Target facts: constructors RVA 0x006DCCC0 and 0x006DCD20 store VA 0x00CEAED0 at +0 and a dword at +4, with no base-constructor call; destructor 0x006DE350 restores that same table. Scalar constructors 0x006D84C0, 0x006D86A0 and 0x006D8860 call 0x006DCCC0 and begin their payload at +8: the root is eight bytes, with no evidenced base. The BfmeAptValue006DCD20 constructor spelling describes this root; its destructor row 0x006D6340 is the AptValueGC wrapper that jumps to 0x006DE350 without a table store.
// Target table 0x00CEAED0 has 15 slots with RVAs 006DCAC0, 006DCB20, 006CBCD0, 0065CE90, 0073B660, 0065CE90, 00180FD0, 0003FD80, 006C8770, 006CBCF0, 0069E440, 006CBD00, 0003B810, 0003B810, 006DE820; the following word at VA 0x00CEAF0C begins assertion text. AptValue ledger rows name slots 0..8 and 11; the matched AptGC::CleanAll calls at 0x006E6FB4, 0x006E6FBB and 0x006E6FFE prove PreDestroy, DestroyGCPointers and DeleteThis at 10, 11 and 9. Slots 12/13 are pure; their names IsGarbageCollected and RegisterReferences follow the donor APT 0.19.03 PDB declaration that AptObject/AptScriptFunction.h carries, and the ledger already names slot-13 overriders RegisterReferences (AptValueWithHash 0x006DCC00, AptObject 0x0070DFD0); slot 14 is deleting destruction, proved by 0x006CBCF8 and 0x006DE820.
// Target declarations: the protected enum constructor binds 0x006DCCC0; flags at +4 are read by getRefCount 0x006DBB20 and private setRefCount 0x006DBB70 (bits 6..17), getIsDefined 0x006DBB60 (bit 4), IsReleaseAtEnd 0x006DBDD0 (bit 2), setIsDefined 0x006DBC30, setGCMark 0x006DBC50 and private SetDestroyedGC 0x006DBD80 (bit 3). Other AptValue rows prove SetString 0x006CBF70, toBool 0x006DD550, toString 0x006DD6C0, rva006ddde0 0x006DDDE0, rva006DDF60 0x006DDF60, rva006DE870 0x006DE870 and findChild 0x006DF9A0. Existing symbol bindings and retail callers prove the predicate/cast API (0x006DBB30, 0x006DBFA0..0x006DC630, 0x006DCD50..0x006DD160), ClearReleaseAtEnd 0x006DBDC0, toInteger 0x006DD360 and toFloat 0x006DD460. All rowed methods remain out of line.
#pragma once

class EAStringC;
class AptArray;
class AptCIH;
class AptDate;
class AptInteger;
class AptLookup;
class AptNativeFunction;
class AptPrototype;
class AptRegister;
class AptString;
struct AptNativeHash;
enum AptVirtualFunctionTable_Indices;

class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const, const EAStringC *const, AptValue *const);
    virtual void DeleteThis();
    virtual void PreDestroy();
    virtual void DestroyGCPointers();
    virtual bool IsGarbageCollected() const = 0;
    virtual void RegisterReferences() const = 0;

    unsigned int getRefCount() const;
    bool getIsDefined() const;
    void setIsDefined(bool);
    void setGCMark(bool);
    int IsReleaseAtEnd() const;
    void ClearReleaseAtEnd();
    AptVirtualFunctionTable_Indices getVtblIndex() const;

    bool isUndefined() const;
    bool isNone() const;
    bool isLookup() const;
    bool isString() const;
    bool isBoolean() const;
    bool isInteger() const;
    bool isRegister() const;
    bool isFloat() const;
    bool isNativeFunction() const;
    bool isScriptFunction() const;
    bool isExtern() const;
    bool isArray() const;
    bool isCIH(bool = false) const;
    bool isObject() const;
    bool isPrototype() const;

    AptLookup *c_lookup() const;
    AptInteger *c_integer() const;
    AptRegister *c_register() const;
    AptString *c_string() const;
    AptNativeFunction *c_nativefunction() const;
    AptCIH *c_cih(bool = false);
    AptCIH *c_cih(bool = false) const;
    AptArray *c_array() const;
    AptPrototype *c_prototype() const;
    AptDate *c_date() const;

    int toInteger() const;
    float toFloat() const;
    bool toBool() const;
    void SetString(const char *);
    void toString(EAStringC &) const;
    void rva006DE870(char *) const;
    EAStringC rva006ddde0();
    EAStringC rva006DDF60();
    AptValue *findChild(const EAStringC *, AptValue *);

protected:
    AptValue(AptVirtualFunctionTable_Indices);
    virtual ~AptValue();
    unsigned int field04;

private:
    friend class AptGC;
    void SetDestroyedGC();
    void setRefCount(unsigned int);
};
