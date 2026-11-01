// cl: /MD
// ?rva00392CAC@Rva0039205C@@QAEXXZ 25B @0x00392CAC: init-style setter zeroing +0 +4 +0C +0D plus -1 at +0x10 plus 0 at +0x14 then tail-jmp to array init. Layout +0 count +8 array from dtor at 0x0039205C. Evidence: shared init pin at 0x00392092 plus callers at 0x003935FC 0x00393E6D.
class Rva00391FC4;
class Rva00392092Target
{
public:
	void rva00392092();
private:
	int m_count00; // +0x00
	char m_pad04[0x4];
	Rva00391FC4 *m_array08; // +0x08
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
enum ObjectID { INVALID_OBJECT_ID = 0 };
class AsciiString;
struct Rva003920F7Src;
class Rva004D9A3C;
class Rva003920F7
{
public:
	void rva003920F7(UnsignedInt index, const Rva003920F7Src *src);
};
class Rva0039205C : public Rva003920F7
{
public:
	void rva00392129(UnsignedInt index, Real angle);
	void rva0039215F(UnsignedInt index, const AsciiString &name);
	void rva00392196(UnsignedInt index, Int status);
	void rva003921C8(UnsignedInt index, unsigned char value);
	void rva00392CAC();

	union { unsigned count; Int m_count; };         // +0x00
	union { unsigned cost; Int m_cost; };           // +0x04
	Rva004D9A3C *array;                             // +0x08
	union { bool flagC; Bool m_0C; };               // +0x0C
	union { bool flagD; Bool m_0D; };               // +0x0D
	short padE;
	union { int status; Int m_status; };            // +0x10
	ObjectID objectID;                              // +0x14

	Rva0039205C()
	{
		status = -1;
		count = 0;
		array = 0;
		flagC = false;
		flagD = false;
		cost = 0;
		objectID = INVALID_OBJECT_ID;
	}
	~Rva0039205C();
	void *rva00392CC5(unsigned index);
	Rva004D9A3C *rva00392CF9(unsigned index);
	float rva00392D1D(unsigned index);
	unsigned char rva00392D49(unsigned index);
	int rva00392D71(int index);
};

void Rva0039205C::rva00392CAC()
{
	m_count = 0;
	status = -1;
	flagC = 0;
	flagD = 0;
	m_cost = 0;
	objectID = INVALID_OBJECT_ID;
	((Rva00392092Target *)this)->rva00392092();
}
