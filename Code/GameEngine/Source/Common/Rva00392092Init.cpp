// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva00392092@Rva00392092Target@@QAEXXZ 101B @0x00392092: array init allocating Rva00391FC4 array sized GlobalData count stride 0x1C via new[]. Layout count at +0 array at +8 from dtor row at 0x0039205C. Evidence: dtor call at 0x003920A2 plus GlobalData+0xA94 plus UU at 0x0002FDE0 plus LL at 0x00629512 plus LINK BONUS 5 files.
// The iterator's constructor callback is the rowed 0x00391FC4, not the
// unrelated forty-byte record constructor at 0x000AF215. Its owned provider
// establishes four floats, a byte at +0x10, AsciiString at +0x14 and int +0x18.
// The implicit string cleanup reproduces the shared +0x14 tail destructor;
// sharing cleanup code does not establish a shared constructor identity.
#include "ascii_string.h"
extern class GlobalData *TheWritableGlobalData;

// Without these MSVC routes new T[n] to scalar ??2 (0x0002FDA0); retail uses array ??_U (0x0002FDE0).
#include <new>

class GlobalData
{
public:
	char m_pad00[0xA68];
	float m_minDistFromEdgeOfMapForBuild; // +0xA68 +0xA68
	float m_supplyBuildBorder; // +0xA6C +0xA6C
	float m_allowedHeightVariationForBuilding; // +0xA70 +0xA70
	char m_padA74[0x20];
	int m_maxLineBuildObjects; // +0xA94 +0xA94
	char m_padA98[0xFC];
	float m_sellPercentage; // +0xB94 +0xB94
	char m_padB98[0x688];
	float m_1220; // +0x1220 +0x1220
};

// The element ctor retail hands the vector-new iterator, 0x00391FC4, is rowed
// as ??0Rva004D9A3C (GapBodiesGE14.cpp).
class Rva004D9A3C
{
public:
	Rva004D9A3C();
	~Rva004D9A3C();
public:
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	unsigned char m_byte10;
	AsciiString m_name;										// +0x14
	int m_18;
};

class Rva00391FC4
{
public:
	Rva00391FC4() { ((Rva004D9A3C *)this)->Rva004D9A3C::Rva004D9A3C(); }
private:
	float m_float00, m_float04, m_float08;
	float m_0C;
	unsigned char m_byte10;
	char m_pad11[3];
	AsciiString m_string14;
	int m_18;
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

class Rva00392092Target
{
public:
	void rva00392092();
private:
	int m_count00; // +0x00
	char m_pad04[0x4];
	Rva00391FC4 *m_array08; // +0x08
};

void Rva00392092Target::rva00392092()
{
	((Rva0039205C *)this)->~Rva0039205C();
	unsigned int count = TheWritableGlobalData->m_maxLineBuildObjects;
	m_array08 = new Rva00391FC4[count];
}

