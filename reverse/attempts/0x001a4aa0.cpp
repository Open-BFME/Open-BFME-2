// ?Release@Animatable3DObjClass@@IAEXXZ
// partial score=0.92 date=2026-09-10
// cl: /O2 /G7 /MD
//
// Animatable3DObjClass::Release, retail 0x001A4AA0, 137 bytes.
// Dedicated TU. Protected thiscall; dword REF_PTR_RELEASE. vslot 0 is a
// no-arg Destroy not a deleting destructor. Do not edit animobj.cpp.
//
// Near miss: switch dispatch matches (sub 2 / jz SINGLE / sub 1 / jnz).
// Slave at +0xFC is released from both SINGLE and DOUBLE via a shared tail.
// Remaining: retail hoists `mov edi,0; mov ebx,-1` between `push edi` and
// the first jz so flags from `sub eax,2` stay live; this compile sinks
// `xor edi,edi; or ebx,-1` into each case instead.

class HAnimClass
{
public:
	virtual void Destroy();
	int Refs;
};

class Animatable3DObjClass
{
protected:
	void Release();

	enum {
		NONE = 0,
		BASE_POSE,
		SINGLE_ANIM,
		DOUBLE_ANIM,
		MULTIPLE_ANIM,
	};

	char Pad[0xFC];
	HAnimClass *Slave;
	int CurMotionMode;
	HAnimClass *Motion;
	HAnimClass *Motion1;
};

void Animatable3DObjClass::Release()
{
	HAnimClass *z = 0;
	int n = -1;
	HAnimClass *p;
	switch (CurMotionMode) {
	case SINGLE_ANIM:
		if ((p = Motion) != z) {
			if (!(p->Refs += n))
				p->Destroy();
			Motion = z;
		}
		if ((p = Slave) != z) {
			if (!(p->Refs += n))
				p->Destroy();
			Slave = z;
		}
		break;
	case DOUBLE_ANIM:
		if ((p = Motion) != z) {
			if (!(p->Refs += n))
				p->Destroy();
			Motion = z;
		}
		if ((p = Motion1) != z) {
			if (!(p->Refs += n))
				p->Destroy();
			Motion1 = z;
		}
		if ((p = Slave) != z) {
			if (!(p->Refs += n))
				p->Destroy();
			Slave = z;
		}
		break;
	}
}
