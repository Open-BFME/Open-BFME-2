// cl: /DNDEBUG /MD
//
// BFME2Encoding0MotionChannel::BFME2Encoding0MotionChannel, retail 0x001B2E2C,
// 26 bytes. Dedicated TU so the factory and stream-ctor units cannot see this
// body. Calls the base ctor then zeros TimeCodes and Samples.

// Both derived channel dtors tail-call the 7-byte base dtor, rowed as
// ??1BFME2MotionChannel@@UAE@XZ (InlineDtorDeletingDtorsC01.cpp).

class BFME2MotionChannel
{
public:
	BFME2MotionChannel();
	virtual ~BFME2MotionChannel();
	int Type;
	int Pivot;
	int Count;
	int Components;
};

void __cdecl operator delete[](void *) throw();

class BFME2Encoding0MotionChannel : public BFME2MotionChannel
{
public:
	BFME2Encoding0MotionChannel();
	virtual ~BFME2Encoding0MotionChannel();
	unsigned short *TimeCodes;
	float *Samples;
};

BFME2Encoding0MotionChannel::BFME2Encoding0MotionChannel()
	: TimeCodes(0), Samples(0)
{
}

// ??1BFME2Encoding0MotionChannel@@UAE@XZ, retail 0x001B2E46, 35 bytes. Dtor
// deletes TimeCodes and Samples via array delete (rowed 0x2FD80 twice)
// then tail-jmps to the pinned base dtor (??1BFME2MotionChannel at
// 0x001A466C, ICF twin of apply). Vtable 0x007D7648 is DIR32. Flags match
// the ctor (/O1 /DNDEBUG /MD); throw() removes the EH frame for retail's
// frameless shape. Sibling of the Stream dtor 0x001B214E.

BFME2Encoding0MotionChannel::~BFME2Encoding0MotionChannel()
{
	delete[] TimeCodes;
	delete[] Samples;
}
