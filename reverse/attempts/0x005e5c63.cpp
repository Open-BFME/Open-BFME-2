// ?Rva005E5C63Create@@YAPAPAVRva005E59A5@@PAPAV1@PBUPayload@1@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /GX- /MD /DNDEBUG
// ?Rva005E5C63Create@@YAPAPAVRva005E59A5@@PAPAV1@PBUPayload@1@@Z @0x005E5C63 50B factory news 0x14 Rva005E59A5 and stores with refcount inc.
// Evidence: calls rowed new 0x0002FDA0 and rowed ctor 0x005E59A5; shape twins caller 0x005CE3F9 pattern for Rva005CE327; unblocks 0x005E62F1.
class Rva005E59A5
{
public:
	struct Payload { int v[3]; };
	Rva005E59A5(const Payload *src);
	virtual ~Rva005E59A5();
	int m_ref;
	Payload m_data;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// ?Rva005E5C63Create@@YAPAPAVRva005E59A5@@PAPAV1@PBUPayload@1@@Z present-unmatched
Rva005E59A5 **__cdecl Rva005E5C63Create(Rva005E59A5 **holder, const Rva005E59A5::Payload *src)
{
	volatile int _keep = 0;
	_ReadWriteBarrier();
	Rva005E59A5 *obj = new Rva005E59A5(src);
	*holder = obj;
	if (obj)
		++obj->m_ref;
	return holder;
}
