// cl: /O1 /DNDEBUG /MD
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

class BFME2StreamMotionChannel : public BFME2MotionChannel
{
public:
	BFME2StreamMotionChannel();
	unsigned char EncodedHeader[20];
	unsigned char *Data;
};

BFME2StreamMotionChannel::BFME2StreamMotionChannel()
	: Data(0)
{
}
