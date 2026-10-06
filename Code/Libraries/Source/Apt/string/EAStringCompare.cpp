// cl: /DNDEBUG /MD
// EA Apt comparisons reconstructed from target operations using the existing
// EAStringCFind layout. Original identities/const signatures: Godfather QA PDB.
// Target stores a representation pointer at +0 and characters at rep+8.
// Original target source family: Apt/string/EAString.cpp (nearby Find assert).
// No confirmed callers for these retained bodies; reachability is unproven.
// Evidence: reverse/godfather_disk_evidence.json, eastring_comparisons.
extern "C" int __cdecl strcmp(const char *,const char *);
#pragma intrinsic(strcmp)
class EAStringC {
    struct StringDataC {
        unsigned short refCount,size,maxSize,hash;
    };
    StringDataC *data;
    const char *buffer() const { return reinterpret_cast<const char *>(data)+8; }
public:
    bool operator<(const EAStringC &) const;
    bool operator<=(const EAStringC &) const;
    bool operator<(const char *) const;
    bool operator<=(const char *) const;
    bool operator>(const char *) const;
    bool operator>=(const char *) const;
    int Compare(const EAStringC &) const;
};
// ??MEAStringC@@QBE_NABV0@@Z
bool EAStringC::operator<(const EAStringC &other) const
{
    if(data==other.data) return false;
    if(strcmp(buffer(),other.buffer())<0) return true;
    return false;
}
// ??NEAStringC@@QBE_NABV0@@Z
bool EAStringC::operator<=(const EAStringC &other) const
{
    if(data==other.data) return true;
    if(strcmp(buffer(),other.buffer())<=0) return true;
    return false;
}
// ??MEAStringC@@QBE_NPBD@Z
bool EAStringC::operator<(const char *other) const { return strcmp(buffer(),other)<0; }
// ??NEAStringC@@QBE_NPBD@Z
bool EAStringC::operator<=(const char *other) const { return strcmp(buffer(),other)<=0; }
// ??OEAStringC@@QBE_NPBD@Z
bool EAStringC::operator>(const char *other) const { return strcmp(buffer(),other)>0; }
// ??PEAStringC@@QBE_NPBD@Z
bool EAStringC::operator>=(const char *other) const { return strcmp(buffer(),other)>=0; }
// ?Compare@EAStringC@@QBEHABV1@@Z
int EAStringC::Compare(const EAStringC &other) const
{
    if(data==other.data) return 0;
    return strcmp(buffer(),other.buffer());
}
