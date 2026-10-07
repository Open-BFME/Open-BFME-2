// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/moduledata
// ??1W3DModelDrawModuleData@@UAE@XZ @0x000C8BE0 292B
// Banked attempt reverse/attempts/0x000c8be0.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
//
// ??1W3DModelDrawModuleData@@UAE@XZ, retail 0x000C8BE0, 292 bytes (Ghidra FUN_004c8be0).
// W3DModelDraw ModuleData base dtor: reinstalls vtable 0xBCADE8, tears down
// the +0x160 array via ehvec 0x629110, 7 vectors, 9 strings via folded
// 0x36410, record 0x79554, then restores Snapshot base 0xBBB554.
// Anchors: 3 matched subclass dtors call base pin 0xC8BE0 (Supply 0xCAF30,
// Tank 0xCE764, Truck 0xCB28E) + matched deleting wrapper 0xC8DC3 (slot 0
// of 0xBCADE8, calls 0xC8BE0 + 0x2FD60). Primary guide: clean BFME1
// W3DModelDrawModuleDataDestructorThunk.cpp (empty dtor shape, /DNDEBUG
// /MD /EHsc, member-then-base ordering). Ghidra 292B boundary verified:
// C9 C3 at 0xC8D03, next FUN_004c8d04 (overflow 191B) at 0xC8D04, no overlap
// with writer-12 C8EEF (599B at 0xC8EEF). Seat-51 r23 596B funclet-conflated
// extent NOT used. No fake empty provider (DeletingDtors scaffold untouched).
// 51r24 recipe unavailable (no r24 file, only through r23).

#include "Common/Snapshot.h"

#include "ascii_string.h"

// Rowed providers (declare-only, resolve to ledger rows, no definitions here).
struct Rva000C0495
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C0495();
};

struct Rva00079554Record
{
	unsigned char m_pad[0x2C];
	~Rva00079554Record();
};

// Unrowed +0x08 vector (Ghidra 63B FUN_004c7720) and +0x160 array element
// (0x14 bytes, ehvec 0x629110 with element dtor). Declared here for
// measurement; bodies are placeholders to be replaced by genuine
// RvaVectorDtorFamily-style specialization (Destroy 0xC4DEF rowed) and
// honest element identity. No donor identity claimed for these two.
// Template vector placeholders (12B each) with declared dtors so the empty
// dtor emits calls + EH states in retail order; each must resolve to its
// rowed instantiation (0xC68C2/0xC1C6A/0x2CC70/0xC8B83/0xC8216) in the final
// version via genuine element types -- this measurement TU uses opaque
// wrappers to prove offsets/states without claiming element identity.
struct Rva000C68C2Wrap
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C68C2Wrap();
};

struct Rva000C1C6AWrap
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C1C6AWrap();
};

struct Rva0002CC70Wrap
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva0002CC70Wrap();
};

struct Rva000C8B83Wrap
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C8B83Wrap();
};

struct Rva000C8216Wrap
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C8216Wrap();
};

struct Rva000C7720Vec
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C7720Vec();
};

struct W3DModelDrawArrayElement
{
	unsigned char m_pad[0x14];
	~W3DModelDrawArrayElement();
};

// Measurement note: Rva000C7720Vec and W3DModelDrawArrayElement dtors are
// intentionally left undefined here so the containing dtor emits calls +
// EH states for +0x08/+0x160 without intra-TU folding; each resolves
// through its genuine provider in the final version (C7720 via
// RvaVectorDtorFamily-style specialization on rowed Destroy 0xC4DEF;
// array element via honest identity, never a fake empty). No donor
// identity is claimed for these two.

// Full layout from retail byte decode (capstone) + rowed callee identities.
// Declaration order is increasing offset so the empty dtor tears down in
// reverse (retail states 0x11..0): +0x160 array, +0x11C vec, 4 strings
// +0x118..+0x10C, +0x8C record, +0x7C/+0x70 vecs, 4 strings +0x48..+0x3C,
// +0x30/+0x24/+0x18 vecs, +0x14 string, +0x08 vec. Scalar runs are padding;
// only member offsets matter for the dtor. Vector placeholders are 12-byte
// start/finish/end triples; each must resolve to its rowed dtor
// (0xC0495/0xC68C2/0xC1C6A/0x2CC70/0xC8B83/0xC8216/0xC7720) in the final
// version -- this measurement TU uses void triples to prove the shape.
class W3DModelDrawModuleData : public Snapshot
{
public:
	virtual ~W3DModelDrawModuleData();

private:
	unsigned char m_pad04[4]; // +0x04..+0x07 (Snapshot is vptr-only)
	Rva000C7720Vec m_08; // +0x08
	AsciiString m_14; // +0x14
	Rva000C8216Wrap m_18; // +0x18 vector via rowed 0xC8216 shape
	Rva000C8B83Wrap m_24; // +0x24 vector via rowed 0xC8B83 shape
	Rva0002CC70Wrap m_30; // +0x30 vector via rowed 0x2CC70 shape
	AsciiString m_3C; // +0x3C
	AsciiString m_40; // +0x40
	AsciiString m_44; // +0x44
	AsciiString m_48; // +0x48
	unsigned char m_pad4C[0x70 - 0x4C]; // +0x4C..+0x6F scalars
	Rva000C1C6AWrap m_70; // +0x70 vector via rowed 0xC1C6A shape
	Rva000C68C2Wrap m_7C; // +0x7C vector via rowed 0xC68C2 shape
	unsigned char m_pad88[4]; // +0x88 scalar (r17: +0x88=0)
	Rva00079554Record m_8C; // +0x8C record 0x2C
	unsigned char m_padB8[0x10C - 0xB8]; // +0xB8..+0x10B (incl opaque +0xBC 0x4C)
	AsciiString m_10C; // +0x10C
	AsciiString m_110; // +0x110
	AsciiString m_114; // +0x114
	AsciiString m_118; // +0x118
	Rva000C0495 m_11C; // +0x11C vector via rowed 0xC0495
	unsigned char m_pad128[0x160 - 0x128]; // +0x128..+0x15F scalars
	W3DModelDrawArrayElement m_160[2]; // +0x160 array[2] 0x14 (ehvec 0x629110)
};

// ??1W3DModelDrawModuleData@@UAE@XZ @0xC8BE0
W3DModelDrawModuleData::~W3DModelDrawModuleData()
{
}
