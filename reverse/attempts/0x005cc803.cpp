// ??1Rva005CC803@@QAE@XZ
// partial score=1.0 date=2026-10-04
// ??1Rva005CC803@@QAE@XZ
// Revised2026-10-04: native scalar-deleting entry5CC7E4 adjusts ECX-8,
// calls this body and optionally deletes the complete object. The old
// constructor identity caused its extra EAX=this return; destructor emits
// the full28B exactly. Original class/member spelling remains unknown.
// Primary C74E6C and secondary C74E68 table definitions remain unavailable;
// do not land this body until they have real linked providers. BC6F20 uses
// an existing folded vtable alias and adds no new table identity.
// cl: /O1 /MD
// ??1Rva005CC803@@QAE@XZ @0x005CC803 28B evidence: stores g_00C74E6C at +0 g_00C74E68 at [off+this+4] where off from [m_04+4] and g_00BC6F20 at +8; caller 0x005CC7EA in 0x005CC788 family
// Ctor inits +0 and +8 plus variable-located slot via offset held at m_04+4.
extern const void *const g_00C74E6C[];
extern const void *const g_00C74E68[];
extern "C" const void *const vtbl_00BC6F20[];
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
struct Rva005CC803Off {
	char m_pad[4];
	int m_off04;
};
class Rva005CC803 {
public:
	~Rva005CC803();
	void *m_00;
	Rva005CC803Off *m_04;
	void *m_08;
};
// ??1Rva005CC803@@QAE@XZ present-unmatched
Rva005CC803::~Rva005CC803()
{
	m_00 = (void *)g_00C74E6C;
	Rva005CC803Off *p = m_04;
	int off = p->m_off04;
	*(void **)((char *)this + off + 4) = (void *)g_00C74E68;
	m_08 = (void *)vtbl_00BC6F20;
}
