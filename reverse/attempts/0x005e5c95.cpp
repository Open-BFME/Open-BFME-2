// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /GX- /MD /DNDEBUG
// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z @0x005E5C95 50B factory news 0x14 Rva005E59C2 and stores with refcount inc.
// Evidence: calls rowed new 0x0002FDA0 and rowed ctor 0x005E59C2; twin of 0x005E5C63 shape; unblocks 0x005E62F1.
class Rva005E59C2
{
public:
	struct Payload { int v[3]; };
	Rva005E59C2(const Payload *src);
	virtual ~Rva005E59C2();
	int m_ref;
	Payload m_data;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z present-unmatched
Rva005E59C2 **__cdecl rva005E5C95(Rva005E59C2 **holder, const Rva005E59C2::Payload *src)
{
	volatile int _keep = 0;
	_ReadWriteBarrier();
	Rva005E59C2 *obj = new Rva005E59C2(src);
	*holder = obj;
	if (obj)
		++obj->m_ref;
	return holder;
}
