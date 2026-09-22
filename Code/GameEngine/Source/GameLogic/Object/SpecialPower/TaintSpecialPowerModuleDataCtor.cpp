// cl: /O1 /MD /DNDEBUG /arch:SSE
// ??0TaintSpecialPowerModuleData@@QAE@XZ at retail 0x004C4AB8 (51 bytes,
// frameless): base call into the opaque intermediate 0x004930A0 (pinned),
// explicit vtable store at +0, zeros at +0x7C/+0x84/+0x88, 10.0f at +0x80
// matching the Taint table (TaintObject at +0x7C, TaintRadius at +0x80,
// TaintFX at +0x84, TaintOCL at +0x88). Factory at 0x00251EE4 is the sole
// caller. Row supersedes the ctor pin.
class Rva004930A0
{
public:
	Rva004930A0();

protected:
	unsigned char m_pad[0x7C];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class TaintSpecialPowerModuleData : public Rva004930A0
{
public:
	TaintSpecialPowerModuleData();

	int m_taintObject;
	float m_taintRadius;
	int m_taintFX;
	int m_taintOCL;
};

TaintSpecialPowerModuleData::TaintSpecialPowerModuleData()
	: Rva004930A0()
{
	int *taintObject = &m_taintObject;
	*(unsigned int *)this = 0x00C5D608;
	*taintObject = 0;
	m_taintFX = 0;
	m_taintOCL = 0;
	m_taintRadius = 10.0f;
}
