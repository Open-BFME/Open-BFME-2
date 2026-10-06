// ?rva004099CA@CreateAHeroData@@QAEEPAVAsciiString@@H@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004099CA@CreateAHeroData@@QAE_NPAVAsciiString@@H@Z @0x004099CA 172B: CreateAHeroData load from file via Rva004098A9 open plus Rva0060C5FA Xfer bind. Evidence: caller 0x0021A492 passes MyHero.dat AsciiString plus 0 with this+0xc; this+0x48 flag48 and this+0x70 flag70 plus 0x71 return match CreateAHeroData layout 0x140; next row is CreateAHeroData deleting dtor; callees all rowed.
#include <memory>
#include <vector>
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

class Xfer
{
public:
	virtual ~Xfer();
};

struct Rva0060C3C3Stream
{
	virtual void vs0();
	virtual void vs1();
	virtual void vs2();
};

struct Rva0060C3C3
{
	bool rva0060C3C3(struct Rva0060C3C3Stream *s, int *extra);
};

class Rva0060C5FA : public Xfer
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);

private:
	void *m_04;
	void *m_08;
	void *m_0c;
	bool m_isLoading;
	unsigned char m_pad11[3];
	void *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

class Rva0060C45E
{
public:
	void clear();
};

class Rva00406EBF
{
public:
	void rva00406EBF(class Xfer *x);
};

int __cdecl Rva004098A9(int a, int b);

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(class Xfer *x);
	virtual const char *typeName() const;
	virtual void xfer(class Xfer *x);
};

typedef _STL::map<int, int> IntegerMap;
struct TreeHintPayload001F8ACB
{
	unsigned int value;
};
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> StringPayloadMap;
typedef _STL::vector<bool> BitVector;
typedef _STL::map<int, _STL::vector<unsigned int> > IntegerVectorMap;
class RvaVecAscii
{
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;

public:
	~RvaVecAscii();
};
struct BfmeHeroElement005C39DE
{
	AsciiString text;
	unsigned int word4;
	unsigned int word8;
	BfmeHeroElement005C39DE();
	BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};
class CreateAHeroData : public Snapshot
{
	unsigned int word04;
	UnicodeString text08;
	unsigned int word0C;
	unsigned int word10;
	IntegerMap map14;
	IntegerMap map20;
	unsigned int word2C;
	unsigned int word30;
	unsigned int word34;
	unsigned int word38;
	RvaVecAscii strings3C;
	unsigned char flag48;
	char pad49[3];
	AsciiString text4C;
	StringPayloadMap map50;
	BitVector bits5C;
	unsigned char flag70;
	unsigned char flag71;
	unsigned short pad72;
	IntegerVectorMap map74;
	BfmeHeroElement005C39DE elements80[15];
	unsigned int word134;
	unsigned int word138;
	unsigned int word13C;

public:
	unsigned char rva004099CA(AsciiString *filename, int mode);
};

typedef char HeroLayoutSizeCheck[sizeof(CreateAHeroData) == 0x140 ? 1 : -1];

// ?rva004099CA@CreateAHeroData@@QAEEPAVAsciiString@@H@Z present-unmatched
unsigned char CreateAHeroData::rva004099CA(AsciiString *filename, int mode)
{
	if (((StringBase<char> *)filename)->isEmpty())
		return 0;
	int streamInt = Rva004098A9((int)filename, mode);
	if (streamInt == 0)
		return 0;
	Rva0060C5FA tmp((void *)0, (void *)0, (void *)0);
	struct Rva0060C3C3 *binder = (struct Rva0060C3C3 *)&tmp;
	struct Rva0060C3C3Stream *stream = (struct Rva0060C3C3Stream *)streamInt;
	int *extra = (int *)&filename;
	unsigned char ret = 0;
	if (!binder->rva0060C3C3(stream, extra))
	{
		stream->vs2();
		ret = 0;
		goto done;
	}
	if ((unsigned int)filename > 1)
	{
		stream->vs2();
		ret = 0;
		goto done;
	}
	((Rva00406EBF *)this)->rva00406EBF((Xfer *)&tmp);
	flag48 = (unsigned char)mode;
	((Rva0060C45E *)&tmp)->clear();
	stream->vs2();
	ret = flag71;
done:
	return ret;
}
