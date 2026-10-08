// cl: /O1 /DNDEBUG /MD
//
// Scalar deleting destructors of classes whose destructor is empty and
// inline, batch C02: the 29-byte wrapper stores the class's own vtable,
// then frees through operator delete (0x0002FD60) when bit 0 of the flags is
// set and returns this (ret 4). Each class is named after the ledger name its
// vtable already carries, else after the wrapper's address; the dummy tag
// constructors (no retail counterpart) only make this TU emit each vtable and
// with it the deleting destructor. No layout or identity beyond that is
// modelled.
//
//   wrapper     vtable
//   0x00108475  0x00BCF994  Rva00108475

struct EmitVtableTag;

class Rva00108475
{
public:
	Rva00108475(EmitVtableTag *);
	virtual ~Rva00108475();
};

// ?<Rva00108475::Rva00108475> absent-from-retail
Rva00108475::Rva00108475(EmitVtableTag *)
{
}

// ??1Rva00108475@@UAE@XZ @0x0010846E 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva00108475::~Rva00108475()
{
}

// Clean BF1 9cbfb551fe Common/Rva007AE420Table.cpp semantic donor, normal O1/SSE/G7.
// Native 001084D6..001084E4 has its own complete RET boundary and establishes
// receiver58 pointer table, entry20 float. Original owner and full array bound remain
// unresolved; this separate address-owned view models only observed accesses.
struct Rva001084D6Entry { unsigned char unknown[0x20]; float value20; };
class Rva001084D6Table {
public: float getValue(unsigned int index) const;
private: unsigned char unknown[0x58]; Rva001084D6Entry *entries[1];
};
float Rva001084D6Table::getValue(unsigned int index) const { return entries[index]->value20; }
