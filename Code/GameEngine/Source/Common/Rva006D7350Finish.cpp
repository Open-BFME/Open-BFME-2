// cl: /MD /EHsc
// ?rva006D7350@@YAPAXPAVRva006DCE50Opaque@@@Z @0x006D7350 177B (cdecl).
//
// Apt value-to-display-string worker. Reads index 0 of the AptBasePtrStack
// singleton at 0x00E182E0 through rowed At 0x006FE580 then rowed toInteger
// 0x006DD360. A negative index, or a null result from the EAStringC lookup, or
// a null lookup result all return the default global at 0x00E18078. Otherwise
// it clears an EAStringC temporary, hands the looked-up object plus count 1 to
// the address-pinned append worker 0x006D5FE0, asks the pooled AptString::Create
// 0x006D7210, assigns the temporary into the result's EAStringC at +8
// (0x006D3030) and returns it after the temporary destructor 0x006D3010.
class BfmeAptValue006DCD20
{
public:
	int toInteger() const;
};

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int index);
};

extern AptBasePtrStack g_aptValueStackAtE182E0; // 0x00E182E0

class Rva006DCE50Opaque
{
public:
	void *rva006DCE50();
};

class Rva006D5E70String
{
public:
	void *rva006d5e70ptr(int count);
private:
	char *m_pData;
};

class EAStringC
{
	void *m_pData;
public:
	EAStringC();
	EAStringC &clear();
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	EAStringC &rva006D5FE0(void *payload, int count);
};

class AptString
{
public:
	static AptString *Create();
	char m_pad[8];
	EAStringC m_str;
};

extern void *g_bfmeAptDefaultValueAtE18078; // 0x00E18078

void *rva006D7350(Rva006DCE50Opaque *source)
{
	int index = g_aptValueStackAtE182E0.At(0)->toInteger();
	void *data = source->rva006DCE50();
	Rva006D5E70String *str = (Rva006D5E70String *)((char *)data + 8);
	if (index < 0) {
		return g_bfmeAptDefaultValueAtE18078;
	} else {
		void *looked = str->rva006d5e70ptr(index);
		if (looked == 0) {
			return g_bfmeAptDefaultValueAtE18078;
		} else {
			EAStringC temp;
			temp.rva006D5FE0(looked, 1);
			AptString *result = AptString::Create();
			result->m_str = temp;
			return result;
		}
	}
}
