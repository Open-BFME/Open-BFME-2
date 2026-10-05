// ?ParseAudioEventBlock@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
//
// ParseAudioEventBlock, retail 0x004E18B5 (129B), and its append thunk
// 0x0056654F (8B). Target evidence: the LivingWorld event callback table
// registers the proc (error literal "ParseAudioEventBlock::Invalid data passed
// in." at VA 0x00C61C34); the 0x10-byte record (vtable 0x00C61C30, rowed
// virtual dtor 0x004E18A2) is built inline, filled through initFromINI with the
// table at VA 0x00C61C68 and handed to the owner's append thunk, which adds
// 0x78 and tail-jumps to the rowed vector<Rva004E18A2>::push_back 0x005663A8.
// Same shape as ParseForceBattle.cpp; the record and owner names stay
// address-derived.

struct FieldParse;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class Rva004E18A2
{
public:
	Rva004E18A2() : m_04(0), m_08(0), m_0C(false) {}
	virtual ~Rva004E18A2();
private:
	int m_04;
	void *m_08;
	bool m_0C;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva004E18A2, allocator<Rva004E18A2> >
{
public:
	void push_back(const Rva004E18A2 &x);
private:
	Rva004E18A2 *m_start;
	Rva004E18A2 *m_finish;
	Rva004E18A2 *m_endOfStorage;
};
}

class Rva0056654FOwner
{
public:
	void append(const Rva004E18A2 &record);
private:
	unsigned char m_unreconstructed_00[0x78];
	_STL::vector<Rva004E18A2, _STL::allocator<Rva004E18A2> > m_audioEvents;	// +0x78
};

extern const FieldParse g_00C61C68[];

// ?append@Rva0056654FOwner@@QAEXABVRva004E18A2@@@Z
void Rva0056654FOwner::append(const Rva004E18A2 &record)
{
	m_audioEvents.push_back(record);
}

// ?ParseAudioEventBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseAudioEventBlock(INI *ini, void *instance, void *, const void *)
{
	if (ini && instance)
	{
		Rva004E18A2 record;
		ini->initFromINI(&record, g_00C61C68);
		((Rva0056654FOwner *)instance)->append(record);
	}
	else
		throw INIException(3, "ParseAudioEventBlock::Invalid data passed in.");
}
