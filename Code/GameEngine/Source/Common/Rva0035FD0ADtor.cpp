// cl: /MD /EHsc
// ??1Rva0035FD0A@@UAE@XZ @0x0035FD0A (105B): virtual dtor storing vtable 0x008166BC.
// Zeroes +0xC, frees DisplayString at +0x34 via TheDisplayStringManager slot 0x3C,
// zeroes +0x34, destroys wide StringBase at +0x30/+0x2C via rowed releaseBuffer
// 0x00036E70, then base dtor via pinned 0x001DBAC3. Caller at 0x0035FF59 is
// deleting dtor. Prev tail dtors in FamilyTailDtors1DBAC3.cpp.
class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;

template <typename T> class StringBase {
public: StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };

class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	int m_C;
};

class Rva0035FD0A : public Rva001DBAA4
{
public:
	Rva0035FD0A();
	virtual ~Rva0035FD0A();
	int m_startFrame;
	int m_endFrame;
	char m_pad18[0x10];
	int m_drawState;
	StringBase<unsigned short> m_2C;
	StringBase<unsigned short> m_30;
	DisplayString *m_34;
};

// Native [0x0035FCD6,0x0035FD0A), 52 bytes. The two zeroed words at
// +0x2C/+0x30 are the independently rowed destructor's wide-string
// subobjects, whose inline default construction precedes the body stores.
// The 0x38-byte factory at 0x0035FD73 and its StartFrame/EndFrame table
// prove the prefix fields; vtable slot 2 points to rowed TextType update.
// Original class name remains conservatively address-derived here.
Rva0035FD0A::Rva0035FD0A()
{
	m_drawState = -1;
	m_endFrame = 30;
	m_frameLength = 30;
	m_startFrame = 0;
	m_C = 0;
	m_isForward = true;
	m_34 = 0;
}

Rva0035FD0A::~Rva0035FD0A()
{
	m_C = 0;
	if (m_34 != 0)
		TheDisplayStringManager->freeDisplayString(m_34);
	m_34 = 0;
}

// Native [0x0035FD73,0x0035FDCA), 87 bytes. Both this factory and the
// CountUp factory reference the same complete 48-byte StartFrame/EndFrame
// field table at VA 0x00C166DC, defined in CountUpTransitionDestructorThunk.cpp.
typedef char Rva0035FD0ARetailSize[(sizeof(Rva0035FD0A) == 0x38) ? 1 : -1];

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

extern const FieldParse CountUpTransitionFields[];

class Rva0035FF76;
class Rva003600D6Holder
{
public:
	void set(Rva0035FF76 *obj);
};

// Reuse the established opaque pointer-setter binding: full ten-byte
// 0x005F69CE stores only the pointer at holder+0x10, with no pointee access.
void __cdecl Rva0035FD73Parse(INI *ini, Rva003600D6Holder *holder)
{
	Rva0035FD0A *obj = new Rva0035FD0A;
	ini->initFromINI(obj, CountUpTransitionFields);
	obj->m_frameLength = obj->m_endFrame;
	holder->set((Rva0035FF76 *)obj);
}
