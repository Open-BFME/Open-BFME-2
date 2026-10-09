// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ??0Rva00538E22@@QAE@H@Z, retail 0x00538E22, 28 bytes.
// Ctor: vector<BfmeE16> at +0 plus int at +0xc. Calls rowed _Vector_base ctor 0x00211E58 then stores arg.
// Evidence: retail lea [ebp+0xb] allocator temp plus mov [esi+0xc] plus ret 4 plus returns this.
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

struct Rva00538E43Coord : Coord2D
{
	Rva00538E43Coord() { x = 0; y = 0; }
	Rva00538E43Coord(const Rva00538E43Coord &other)
		{ x = other.x; y = other.y; }
};

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva00318B5C : public Snapshot
{
public:
	Rva00318B5C() { command = -1; }
	Rva00318B5C(const Rva00318B5C &other)
		: coordinate(other.coordinate) { command = other.command; }
	virtual ~Rva00318B5C() {}
	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
	Rva00538E43Coord coordinate;
	int command;
};

struct Rva00319F5A
{
	void rva0031A129(const Rva00318B5C &record);
};

// The range-erase callee used by 0x00538ED1 is already rowed for this 16-byte
// element view. Its true payload identity is not established by the call.
struct Elem003AF9E0
{
	virtual ~Elem003AF9E0();
	char m_body[0x0C];
	Elem003AF9E0();
	Elem003AF9E0(const Elem003AF9E0 &);
	Elem003AF9E0 &operator=(const Elem003AF9E0 &);
};

struct Rva00538E22
{
	_STL::vector<BfmeE16> m_vec;
	int m_val;
	Rva00538E22(int v);
	void rva00538ED1(int value);
	void rva00538F10(const _STL::vector<BfmeE16> &source, int value);
	void rva00538D3B(int value);
	Rva00318B5C rva00538E43();
};

// WorldBuilder names LivingWorldArmyMoveQueue::PopFront. Native 538E43
// returns a 16-byte ArmyMoveCommand through the hidden result argument.
// The shared vtable 80C7D0 has the canonical Snapshot deleting destructor,
// empty post-load, ArmyMoveCommand name getter and xfer slots. The target
// copies two floats and a command word before erasing the first record.
Rva00318B5C Rva00538E22::rva00538E43()
{
	if (m_vec.empty())
		return Rva00318B5C();
	_STL::vector<Elem003AF9E0> &records =
		*reinterpret_cast<_STL::vector<Elem003AF9E0> *>(&m_vec);
	Rva00318B5C result = *reinterpret_cast<Rva00318B5C *>(records.begin());
	records.erase(records.begin());
	return result;
}

Rva00538E22::Rva00538E22(int v) : m_vec(), m_val(v)
{
}

// The 36-byte target checks this vector's begin/finish, erases the full range
// through the rowed 0x00319B97 specialization when nonempty, then calls
// 0x00538D3B with the same this and original 32-bit argument. This class view
// is tied to the constructor at 0x00538E22 by the shared +0 vector and +0x0C
// member accessed by its helper; the original method and payload types remain
// unknown. The local element spelling selects the existing range-erase body.
// ?rva00538ED1@Rva00538E22@@QAEXH@Z
void Rva00538E22::rva00538ED1(int value)
{
	_STL::vector<Elem003AF9E0> &records =
		*reinterpret_cast<_STL::vector<Elem003AF9E0> *>(&m_vec);
	Elem003AF9E0 *first = records.begin();
	Elem003AF9E0 *last = records.end();
	if (first != last) {
		records.erase(first, last);
		rva00538D3B(value);
	}
}

// The 81-byte body walks a 16-byte source vector and appends each record to
// this object's three-pointer vector through the matched 0x0031A129 method,
// then calls the address-derived 0x00538D3B helper with the second argument.
// The callers establish the vector-reference and integer ABI; the record
// payload identity and the higher-level purpose remain unknown. BfmeE16 is
// the local 16-byte vector view; the source element's semantic type is not
// established by the target body.
void Rva00538E22::rva00538F10(const _STL::vector<BfmeE16> &source, int value)
{
	const BfmeE16 *first = source.begin();
	const BfmeE16 *last = source.end();
	if (first != last) {
		Rva00319F5A *destination = reinterpret_cast<Rva00319F5A *>(&m_vec);
		for (unsigned int i = 0; i < source.size(); ++i) {
			const Rva00318B5C &record =
				*reinterpret_cast<const Rva00318B5C *>(&source[i]);
			destination->rva0031A129(record);
		}
		rva00538D3B(value);
	}
}
