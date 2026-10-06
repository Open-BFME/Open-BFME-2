// cl: /DNDEBUG /MD
//
// BFME2StreamMotionChannel::BFME2StreamMotionChannel, retail 0x001B2138, 22
// bytes. Dedicated TU so BFME2MotionChannelFactory.cpp cannot see this body.
// Calls the base ctor then zeros the payload pointer at this+0x28.

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

class BFME2StreamMotionChannel : public BFME2MotionChannel
{
public:
	BFME2StreamMotionChannel();
	virtual ~BFME2StreamMotionChannel();
	unsigned char EncodedHeader[20];
	unsigned char *Data;
};

BFME2StreamMotionChannel::BFME2StreamMotionChannel()
	: Data(0)
{
}

// ??1BFME2StreamMotionChannel@@UAE@XZ, retail 0x001B214E, 26 bytes. Dtor
// deletes the Data payload via array delete (rowed 0x2FD80) then tail-jmps
// to the ICF-twin base dtor (pinned ??1BFME2MotionChannel at 0x001A466C,
// same 7B body as rowed apply). Vtable 0x007D7624 is DIR32. Flags match
// the ctor (/O1 /DNDEBUG /MD); throw() on array delete removes the EH
// frame to give retail's frameless push-mov-push-mov-call shape.

BFME2StreamMotionChannel::~BFME2StreamMotionChannel()
{
	delete[] Data;
}
