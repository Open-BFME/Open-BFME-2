// cl: /O1 /DNDEBUG /MD
//
// BFME2Encoding0MotionChannel::BFME2Encoding0MotionChannel, retail 0x001B2E2C,
// 26 bytes. Dedicated TU so the factory and stream-ctor units cannot see this
// body. Calls the base ctor then zeros TimeCodes and Samples.

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

class BFME2Encoding0MotionChannel : public BFME2MotionChannel
{
public:
	BFME2Encoding0MotionChannel();
	unsigned short *TimeCodes;
	float *Samples;
};

BFME2Encoding0MotionChannel::BFME2Encoding0MotionChannel()
	: TimeCodes(0), Samples(0)
{
}
