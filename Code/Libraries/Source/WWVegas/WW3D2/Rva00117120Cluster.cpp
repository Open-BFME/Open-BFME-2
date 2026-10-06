// cl: /DNDEBUG /MD /EHsc
//
// ?rva00117120@@YAXXZ retail 0x00117120, 131 bytes.
//
// Mesh-cache walk that shares _Invalidate_Mesh_Cache's retail TU (both use
// EH scope table 0x00B64B98 and the DX8 device lock pair 0x0011F520 /
// 0x00120F50): take the lock, walk the MeshModelClass instance list via
// 0x001718E0, and for every model call 4 on the object at [CurMatDesc+0xB8]
// when that pointer is non-null, then unlock. The caller identity is not
// proven, so the name and the 0x00152D1C callee are address-derived; the
// 131-byte body is the target evidence.

extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock {
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva00152D1CObj {
public:
	void rva152d1c(int);
};

class Rva00117120MatDesc {
public:
	char m_pad[0xb8];
	Rva00152D1CObj *m_obj;
};

class MeshModelClass {
public:
	char m_pad[0x94];
	Rva00117120MatDesc *m_matDesc;
};

extern MeshModelClass *rva001718E0GetNextMeshModel(MeshModelClass *);

void rva00117120()
{
	BFMEDX8DeviceLock lock;
	for (MeshModelClass *model = rva001718E0GetNextMeshModel(0);
	     model != 0;
	     model = rva001718E0GetNextMeshModel(model)) {
		Rva00117120MatDesc *matDesc = model->m_matDesc;
		if (matDesc->m_obj)
			matDesc->m_obj->rva152d1c(4);
	}
}
