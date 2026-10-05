// cl: /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// A 0x24-byte owner of nine channel pointers: the destructor at 0x0018E750
// and its vector deleting form at 0x0018E830 (which strides 0x24 and calls
// it). These were rowed as RoadType's, but W3DRoadBuffer::freeRoadBuffers
// (0x000D7753) deletes its road types through 0x000D6988 instead, and nothing
// calls 0x0018E830; the owning class is not identified, so the name is
// derived from the destructor's address.
//
// Each member is freed through the same 24B dtor body at 0x1960C0 that
// ~NodeCompressedMotionStruct uses for its Vis member (delete Vis at +0x18
// with the same esi-tail shape, matched row ?Free@MotionChannelClass@@AAEXXZ
// plus pin ??1TimeCodedBitChannelClass@@QAE@XZ): the members' true type is
// unproven, so this TU redeclares the proven-sharer locally (TU-local
// replicas mangle identically). All nine releases are direct calls.

// Declared so the array path of the vector deleting dtor releases through
// operator delete[] (0x0002FD80), as retail does; without it MSVC 7.1 falls
// back to the scalar operator delete.
void operator delete[](void *block);

class TimeCodedBitChannelClass
{
public:
	~TimeCodedBitChannelClass();
};

class Rva0018E750ChannelSet
{
public:
	~Rva0018E750ChannelSet();

private:
	TimeCodedBitChannelClass *m_slot00;
	TimeCodedBitChannelClass *m_slot01;
	TimeCodedBitChannelClass *m_slot02;
	TimeCodedBitChannelClass *m_slot03;
	TimeCodedBitChannelClass *m_slot04;
	TimeCodedBitChannelClass *m_slot05;
	TimeCodedBitChannelClass *m_slot06;
	TimeCodedBitChannelClass *m_slot07;
	TimeCodedBitChannelClass *m_slot08;
};

Rva0018E750ChannelSet::~Rva0018E750ChannelSet()
{
	if (m_slot00)
		delete m_slot00;
	if (m_slot01)
		delete m_slot01;
	if (m_slot02)
		delete m_slot02;
	if (m_slot03)
		delete m_slot03;
	if (m_slot04)
		delete m_slot04;
	if (m_slot05)
		delete m_slot05;
	if (m_slot06)
		delete m_slot06;
	if (m_slot08)
		delete m_slot08;
	if (m_slot07)
		delete m_slot07;
}

// Not retail code: makes this unit emit the vector deleting destructor.
// ?bfmeEmitRva0018E750VectorDtor@@YAXPAVRva0018E750ChannelSet@@@Z present-unmatched
void bfmeEmitRva0018E750VectorDtor(Rva0018E750ChannelSet *p)
{
	delete[] p;
}
