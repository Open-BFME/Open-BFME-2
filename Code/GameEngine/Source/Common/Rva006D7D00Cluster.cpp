// cl: /MD
// ?rva006D7D00@@YAPAVAptString@@PAVRva006DD6C0@@@Z @0x006D7D00 118B (cdecl).
// Apt string-value conversion callback: builds an EAStringC temporary with
// clear() 0x006D2F90, has the source object (arg, ecx) fill it through the
// address-pinned helper 0x006DD6C0, post-processes it through 0x006D6170, asks
// the pooled AptString::Create 0x006D7210 for a result, assigns the temporary
// into the result's EAStringC at +8 with the rowed operator= 0x006D3030, and
// returns the AptString after the temporary destructor 0x006D3010. The source
// object type, the helper at 0x006DD6C0 and the post-processor at 0x006D6170
// are all address-derived (the latter two pinned only for this call site).
class EAStringC
{
public:
	EAStringC();
	EAStringC &clear();
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	EAStringC &rva006D6170();
};

class Rva006DD6C0;

class AptValue
{
public:
	void toString(EAStringC&)const;
	void SetString(const char *);
	unsigned int getRefCount()const;
	virtual void AddRef();
};

class AptString
{
public:
	static AptString *Create();
};

struct ScopedStringText {unsigned char prefix[8];EAStringC text;};

AptString *rva006D7D00(Rva006DD6C0 *source)
{
	EAStringC temp;
	((const AptValue *)source)->toString(temp);
	temp.rva006D6170();
	AptString *result = AptString::Create();
	reinterpret_cast<ScopedStringText *>(result)->text = temp;
	return result;
}
