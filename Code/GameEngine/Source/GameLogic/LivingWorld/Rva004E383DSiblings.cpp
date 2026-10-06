// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ParseEyeTowerPointData, retail RVA 0x004E383D (123 bytes), recovered from the
// ParseForceBattle recipe at 0x004E16D9. Same operand-masked shape: null-check
// INI and instance, construct a stack record, INI::initFromINI it against the
// type's FieldParse table, then append it to the owner, else throw
// INIException(3) with the type's literal. Only the record (a 0x0C-byte
// _STL::vector<BfmePod8>, ctor 0x004E364F / clear 0x004E366E), the table, the
// append thunk and the "ParseEyeTowerPointData::Invalid data passed in."
// literal differ from the template. Evidence: the retail literal at
// 0x00C62004 names the type; the 0x0C record size is read from sub esp,0x14
// with the record at ebp-0x20 and the exception buffer at ebp-0x14.
typedef int Int;

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
	void initFromINI( void *what, const FieldParse *parseTable );
};

// The record is the EyeTower temp built at ebp-0x20: a 0x0C-byte vector whose
// ctor row lives at 0x004E364F. Its destructor spelling is a new pin at the
// rowed clear body 0x004E366E (?rva004E366E@Rva004E366E@@QAEXXZ).
class Rva004E364F
{
public:
	Rva004E364F();
	~Rva004E364F();

private:
	char m_body[ 0x0C ];
};

class Rva005669B7Owner
{
public:
	void append( Rva004E364F *record );
};

extern const FieldParse g_00C62034;

void ParseEyeTowerPointData( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva004E364F record;
		ini->initFromINI( &record, &g_00C62034 );
		((Rva005669B7Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseEyeTowerPointData::Invalid data passed in." );
}
