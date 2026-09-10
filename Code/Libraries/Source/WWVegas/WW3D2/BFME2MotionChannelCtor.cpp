// cl: /O1 /DNDEBUG /MD
//
// BFME2MotionChannel::BFME2MotionChannel, retail 0x001A465B, 17 bytes.
// Dedicated TU so the derived channel ctors cannot inline this body.
// Type and Pivot are or-assigned -1; Count and Components stay uninit.

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

BFME2MotionChannel::BFME2MotionChannel()
	: Type(-1), Pivot(-1)
{
}
