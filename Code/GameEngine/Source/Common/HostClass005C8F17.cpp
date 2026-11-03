// cl: /MD
// ?rva005C8F17@HostClass005C8E0A@@QAEXXZ @0x005C8F17 57B
// Void method on HostClass005C8E0A sharing layout with rva005C8E2C: if pool
// ref at +8 is non-null notify TheAudio slot 0x6c removeAudioEvent with the
// handle at holder+0xc then clear via 0x519BD adjust via LargeGroupAudioGridCell(false)
// and method_005C8E0A then clear byte +0x46. Evidence: same +8/+0x46 layout
// and callee trio as 0x005C8E2C callers 0x005C8FBD/0x005C901B/0x005C908B.

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct BfmePoolHolder
{
public:
	char m_pad00[0xC];
	unsigned int m_audioHandle0C; // +0x0C
	char m_pad10[0x78];
	OpaqueRefCounted m_ref; // +0x88
};

class BfmePoolRef10
{
public:
	BfmePoolHolder *m_target;
	void rva000519BD();
};

class LargeGroupAudioGridCell
{
public:
	void setOverlappedLocking(bool flag);
};

typedef unsigned int AudioHandle;

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

struct Element005C8E0A;
class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	void method_005C9069();
	void rva005C8F17();
	BfmePoolRef10 rva005C8E2C();
	char m_pad00[0x8];
private:
	BfmePoolRef10 m_pool08; // +0x08
	char m_pad0C[0x2C];
public:
	Element005C8E0A *m_start; // +0x38
	Element005C8E0A *m_finish; // +0x3C
	char m_pad40[0x6];
private:
	unsigned char m_byte46; // +0x46
	char m_pad47[0x1];
};

void HostClass005C8E0A::rva005C8F17()
{
	if (m_pool08.m_target != 0) {
		TheAudio->removeAudioEvent(m_pool08.m_target->m_audioHandle0C);
		m_pool08.rva000519BD();
		((LargeGroupAudioGridCell *)this)->setOverlappedLocking(false);
		method_005C8E0A();
	}
	m_byte46 = 0;
}
