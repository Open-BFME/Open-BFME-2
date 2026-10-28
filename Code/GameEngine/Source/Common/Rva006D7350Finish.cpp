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
	// 0x006DCE50, rowed in Apt/AptValue/Rva006DCE50Finish.cpp: the value's
	// string payload.
	BfmeAptValue006DCD20 *checkedString();
};

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int index);
};

struct AptActionInterpreter { AptBasePtrStack stack; };
extern AptActionInterpreter g_aptDateInterpreter;	// VA 0x00E182E0 (AptDate.cpp); its value stack is the first member

class Rva006DCE50Opaque;

class Rva006D5E70String
{
public:
	void *rva006d5e70(int count);
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

class AptValue;
extern AptValue *gpUndefinedValue;	// 0x00E18078, the rowed AptBuiltinValues.cpp global

void *rva006D7350(Rva006DCE50Opaque *source)
{
	int index = g_aptDateInterpreter.stack.At(0)->toInteger();
	void *data = ((BfmeAptValue006DCD20 *)source)->checkedString();
	Rva006D5E70String *str = (Rva006D5E70String *)((char *)data + 8);
	if (index < 0) {
		return (void *)gpUndefinedValue;
	} else {
		void *looked = str->rva006d5e70(index);
		if (looked == 0) {
			return (void *)gpUndefinedValue;
		} else {
			EAStringC temp;
			temp.rva006D5FE0(looked, 1);
			AptString *result = AptString::Create();
			result->m_str = temp;
			return result;
		}
	}
}
