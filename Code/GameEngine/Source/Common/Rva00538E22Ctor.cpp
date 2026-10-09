// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /EHsc /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ??0Rva00538E22@@QAE@H@Z, retail 0x00538E22, 28 bytes.
// Ctor: vector<BfmeE16> at +0 plus int at +0xc. Calls rowed _Vector_base ctor 0x00211E58 then stores arg.
// Evidence: retail lea [ebp+0xb] allocator temp plus mov [esi+0xc] plus ret 4 plus returns this.
#include <vector>
#include "Coord2D.h"
#include <cstring>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(memcpy)
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"

struct Rva00538E43Coord : Coord2D
{
	Rva00538E43Coord() { x = 0; y = 0; }
	Rva00538E43Coord(const Rva00538E43Coord &other)
		{ x = other.x; y = other.y; }
};

struct Rva00538CB4Input
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28(bool *flags) = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50(void *out) = 0;
};

struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *object, void *out);

// The return record vtable at VA C0C7D0 names ArmyMoveCommand through
// slot2 at318B7D. Its cleanup at7978D9 tail-calls Snapshot dtor49B47C.
// Field accesses establish coordinates at4/8 and a signed tag atC;
// their higher-level roles are not established.
struct Rva00318E4ACoord { float x, y; };
struct Rva00538E43Pair
{
	float x, y;
	Rva00538E43Pair() : x(0), y(0) {}
	Rva00538E43Pair(float a, float b) : x(a), y(b) {}
	Rva00538E43Pair(const Rva00318E4ACoord &that) { memcpy(this, &that, sizeof(that)); }
	Rva00538E43Pair(const Rva00538E43Pair &that) : x(that.x), y(that.y) {}
	~Rva00538E43Pair() {}
};
struct Rva00538E43Result : Snapshot
{
	Rva00538E43Pair position;
	int tag;
	Rva00538E43Result() : position(), tag(-1) {}
	Rva00538E43Result(const Rva00318E4ACoord &point, int value);
	Rva00538E43Result(const Rva00538E43Result &that) : Snapshot(that), position(that.position), tag(that.tag) {}
	virtual ~Rva00538E43Result() {}
	virtual void loadPostProcess() {}
	// ?Rva00538E43Result::GetSnapshotName present-unmatched
	virtual const char *GetSnapshotName() const { return "ArmyMoveCommand"; }
	virtual void xfer(Xfer *xfer);
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
	bool hasRecords() const { return m_vec.size() > 0; }
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

// Rehomed from the isolated 0x538CB4 ABI view. The vtable at C0C7D0
// and matching field offsets tie that transfer method to this result.
void Rva00538E43Result::xfer(Xfer *stream)
{
	Rva00538CB4Input *input = reinterpret_cast<Rva00538CB4Input *>(stream);
	bool flags[2];
	flags[0] = 1;
	flags[1] = 1;
	input->slot28(flags);
	input->slot50(&position);
	Rva003EFE82Get((Rva003EFE82Obj *)input, &tag);
}

Rva00538E43Result::Rva00538E43Result(const Rva00318E4ACoord &point, int value) : position(point), tag(value)
{
}

// The caller at 0x3FE1DB holds this queue at+3C and copies the returned
// coordinate bits into+50/+54; an empty queue clears its byte at+5C.
class Rva003FE1DBOwner
{
public:
 void rva003FE1DB();
private:
 char m_pad0[0x3C];
 Rva00538E22 m_queue;
 char m_pad4C[4];
 Rva00318E4ACoord m_position;
 char m_pad58[4];
 unsigned char m_active;
};
void Rva003FE1DBOwner::rva003FE1DB()
{
 if (m_queue.hasRecords()) {
  Rva00538E43Result front = m_queue.rva00538E43();
  memcpy(&m_position, &front.position, sizeof(m_position));
 } else {
  m_active = 0;
 }
}

extern "C" double __cdecl sqrt(double);
class Rva003FE13E
{
	float m_pad00[6];
	float m_18;
	float m_1C;
	char m_pad20[0x50 - 0x20];
	float m_50;
	float m_54;
	float m_58;

public:
	float rva003FE13E();
};


class LivingWorldArmyIcon
{
public:
	void continueMoving(Coord2D *out);
private:
	char m_unknown0[0x18];
	Coord2D current;
	char m_unknown20[0x30];
	Coord2D destination;
};

// Complete native 229B RET4 and WB1074010 establish this movement step.
// The speed helper and queue advance retain their address-derived names.
// Ordered current reads preserve retail's loads after displacement construction.
// The output barrier retains the native x reload; newY stays a local because
// the native subtraction reuses its value rather than loading out->y again.
void LivingWorldArmyIcon::continueMoving(Coord2D *out)
{
	Coord2D d;
	d.x = destination.x - current.x;
	d.y = destination.y - current.y;
	float squared = d.x * d.x + d.y * d.y;
	if (squared > 0.001) {
		float inverse = 1.0f / (float)sqrt(squared);
		d.x *= inverse;
		d.y *= inverse;
	}
	float step = ((Rva003FE13E *)this)->rva003FE13E();
	Rva00538E43Pair displacement(step * d.x, step * d.y);
	out->x = *reinterpret_cast<const volatile float *>(&current.x) + displacement.x;
	float newY = *reinterpret_cast<const volatile float *>(&current.y) + displacement.y;
	out->y = newY;
	_ReadWriteBarrier();
	d.x = destination.x;
	d.y = destination.y;
	d.x -= out->x;
	d.y -= newY;
	if (d.length() < 1.0f)
		((Rva003FE1DBOwner *)this)->rva003FE1DB();
}
