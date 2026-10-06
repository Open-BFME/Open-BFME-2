// cl: /MD /EHsc
// Target date dispatch key toString selects this callback at 0x006F5080.
// Original sMethod spelling/two-argument ABI are from Godfather QA PDB;
// operations, helper targets and temporary lifetime are established in retail.
// AptString factory identity: target AptString.inl assertions and matching
// donor callback call to MAP-named AptString::Create(). No full class layout.
// The EAStringC accessor retains its address name: target proves data+8 but
// cannot distinguish donor GetBuffer/c_str/ConstRawPtr spellings.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_string_callback.
class EAStringC {
    void *data;
public:
    EAStringC();
    EAStringC &clear();
    ~EAStringC();
    const char *rva00620090() const;
};
class AptValue { public: void SetString(const char *); };
class AptString { public: static AptString *Create(); };
class BfmeAptValue006DCD20 { public: BfmeAptValue006DCD20 *rva006DD160(); };
class AptDate {
public:
    void toString(EAStringC &);
    static AptValue *sMethod_toString(AptValue *,int);
};
AptValue *AptDate::sMethod_toString(AptValue *value,int argc)
{
    AptValue *result=reinterpret_cast<AptValue *>(AptString::Create());
    EAStringC text;
    reinterpret_cast<AptDate *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD160())->toString(text);
    result->SetString(text.rva00620090());
    return result;
}
