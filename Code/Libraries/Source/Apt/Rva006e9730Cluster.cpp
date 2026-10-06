// cl: /MD /EHsc
// Address-derived recovery of 0x006E9730 (102B), an Apt string-factory helper.
// Retail: AptString::Create() 0x006D7210, then the first argument's by-value
// EAStringC toString 0x006DDDE0 (373B, unrowed; hidden return pointer is the
// pushed local), the accessor 0x00620090 on the returned EAStringC, then
// AptValue::SetString 0x006CBF70. The SEH frame belongs to the EAStringC
// temporary's destructor 0x006D3010. Layout/flags match the sibling
// AptDateStringCallback.cpp factory body at 0x006F5080.
// Identity of the class and method names is not proven; they are
// address-derived on the target addresses.

class EAStringC
{
    void *data;
public:
    ~EAStringC();
    const char *rva00620090() const;
};

class AptValue
{
public:
    EAStringC rva006ddde0();
    void SetString(const char *text);
};

class AptString : public AptValue
{
public:
    static AptString *Create();
};

AptValue *rva006e9730(AptValue *value)
{
    AptValue *result = AptString::Create();
    result->SetString(value->rva006ddde0().rva00620090());
    return result;
}
