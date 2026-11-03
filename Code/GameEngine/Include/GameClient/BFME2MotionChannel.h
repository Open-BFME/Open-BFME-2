// Target facts: addresses below are retail RVAs unless marked VA; the class name is descriptive.
// Constructor 0x001A465B sets dwords +4/+8 to -1 and the primary vptr to VA 0x00BD6CB4; destructor 0x001A466C and deleting destructor 0x001A4697 restore that same table, with no base calls.
// Table RVA 0x007D6CB4 has seven slots up to the next constructor-owned table 0x007D6CD0: slots 0/2/3/4/5/6 are __purecall (0x0003B810), slot 1 is 0x001A4697. The factory 0x001A46B4 calls Load at +0 and destruction at +4. Tables 0x007D6CD0/0x007D6CEC/0x007D7648 identify the derived ledger methods UnknownSlot2 through UnknownSlot6 and their signatures. At 0x001A4777/477E/4785/478C the factory stores four dwords at +4/+8/+0xC/+0x10; loader 0x00190210 uses +8 as a node index and 0x00190218 dispatches on +4. Loads 0x001B2168/0x001B2E69 use +0xC and +0x10 to size payloads. The stream Load at 0x001B2172 and encoding-0 constructor at 0x001B2E34 place the first derived storage at +0x14; factory allocations 0x2C/0x1C contain derived payloads of 24/8 bytes, establishing the 0x14-byte base layout.

#pragma once

class ChunkLoadClass;
class Vector3;
class Quaternion;

class BFME2MotionChannel
{
public:
	BFME2MotionChannel();
	virtual bool Load(ChunkLoadClass &) = 0;
	virtual ~BFME2MotionChannel();
	virtual int UnknownSlot2() = 0;
	virtual void UnknownSlot3(float frame, float *value, unsigned char **cursor) = 0;
	virtual void UnknownSlot4(float frame, Vector3 *value, unsigned char **cursor) = 0;
	virtual void UnknownSlot5(float frame, Quaternion *value, unsigned char **cursor) = 0;
	virtual int UnknownSlot6() = 0;

	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};
