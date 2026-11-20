// cl: /DNDEBUG /MD /ICode/Libraries/Include
// Retail 0x006BE9A0 (47 B, RET12, no caller left in retail): constructor of
// a 0x34-byte entry holding the 36-byte shape record whose out-of-line copy
// is 0x00063BE4, then a position (+0x24) and one word (+0x30). The position
// argument comes first and the record second, as the argument loads show.
// The position copies member-wise through retail Coord3D's user copy
// constructor (three dword moves at fixed offsets; the canonical POD
// Coord3D's implicit copy goes through a base register instead). Region
// flags are /O2 here. Owner and field meanings are unrecovered: the record
// keeps its existing address-derived row name, the entry an address name.
#include "Lib/Coord3DCtorView.h"

struct BfmeStringRecord00063BE4
{
	int words[7];
	void *text;
	unsigned char tail[2];
	BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &);
};

class Rva006BE9A0
{
public:
	Rva006BE9A0(const Coord3D &position, const BfmeStringRecord00063BE4 &record, int value);
private:
	BfmeStringRecord00063BE4 m_record;
	Coord3D m_position;
	int m_value;
};

Rva006BE9A0::Rva006BE9A0(const Coord3D &position, const BfmeStringRecord00063BE4 &record, int value)
	: m_record(record), m_position(position), m_value(value)
{
}
