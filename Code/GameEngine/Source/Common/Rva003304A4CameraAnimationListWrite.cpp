// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?writeDataChunk@Rva003304A4CameraAnimationList@@QAEXPAVDataChunkOutput@@@Z
// Retail 0x003304A4..0x00330528 (132 bytes).
// Writes the CameraAnimationList chunk: opens chunk "CameraAnimationList"
// version 3 and writes the element count of the STLport pointer vector at +0x10
// then for each element runs a scoped type-tag visitor through the element's
// slot 1 and lets the element write itself through its slot 5 (+0x14) before
// closing the chunk.
// Evidence (target): literal CameraAnimationList at 0x0080DB44 (also used by
// the CameraAnimationList parser binding Rva00330528); callees
// DataChunkOutput::openDataChunk 0x00307C76 / writeInt 0x00306CFF /
// closeDataChunk 0x00306C88 are matched rows. The visitor is the 8-byte
// object built at 0x00330472 (vtable 0x00C0DB34 plus DataChunkOutput* at +4)
// whose slots 0 and 2 (0x00330494 / 0x00330484) write the tags 'look' and
// 'free'; its base (vtable 0x00C0DB24 ctor 0x00330447 dtor 0x00330440) has
// empty slots 0/2 and forwarding slots 1/3. The neighbouring getter
// 0x00330450 indexes the same vector. The STLport vector (not a raw begin/end
// pair) is what gives retail its esi/edi assignment. Class names are
// address-derived.

#include <vector>

typedef int Int;

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short version);
	void writeInt(Int value);
	void closeDataChunk();
};

class Rva003304A4Animation;

class Rva003304A4AnimationVisitor
{
public:
	Rva003304A4AnimationVisitor() {}
	~Rva003304A4AnimationVisitor() {}
	virtual void visitLookAt(Rva003304A4Animation *animation);
	virtual void visitLookAtConst(Rva003304A4Animation *animation);
	virtual void visitFree(Rva003304A4Animation *animation);
	virtual void visitFreeConst(Rva003304A4Animation *animation);
};

class Rva003304A4TypeTagWriter : public Rva003304A4AnimationVisitor
{
public:
	Rva003304A4TypeTagWriter(DataChunkOutput *out) : m_out(out) {}
	virtual void visitLookAt(Rva003304A4Animation *animation);
	virtual void visitFree(Rva003304A4Animation *animation);
private:
	DataChunkOutput *m_out;
};

class Rva003304A4Animation
{
public:
	virtual void slot0();
	virtual void accept(Rva003304A4AnimationVisitor *visitor);
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void writeDataChunk(DataChunkOutput *out);
};

class Rva003304A4CameraAnimationList
{
public:
	void writeDataChunk(DataChunkOutput *out);
private:
	char m_pad00[0x10];
	_STL::vector<Rva003304A4Animation *> m_animations;
};

void Rva003304A4CameraAnimationList::writeDataChunk(DataChunkOutput *out)
{
	out->openDataChunk("CameraAnimationList", 3);
	out->writeInt(m_animations.size());
	for (_STL::vector<Rva003304A4Animation *>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		{
			Rva003304A4TypeTagWriter writer(out);
			(*it)->accept(&writer);
		}
		(*it)->writeDataChunk(out);
	}
	out->closeDataChunk();
}
