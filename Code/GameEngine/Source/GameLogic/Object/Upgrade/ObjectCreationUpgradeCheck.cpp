// cl: /MD
// ?rva004B4130@Rva004B4130@@QAE_NPAVRva00406F9C@@@Z @0x004B4130 121B: upgrade mask check.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C,
// returns false if buf80 all zero, if buf100 intersects mask via rowed
// 0x00406F9C, then dispatches on virtual +0x34 to rowed 0x002AA292 or rowed
// 0x00406F9C with mask as this and buf80 as other. Slot 2 of 0x00857660,
// class of ObjectCreationUpgrade ctor. Chain from 0x00406F9C.
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
	unsigned m_data[32];
};

class Rva002AA292
{
public:
	bool rva002AA292(const int *mask) const;
private:
	int m_bits[32];
};

class Player { public: char pad00[0x13C]; Rva00406F9C mask; };
class Object { public: Player *getControllingPlayer() const; char pad00[0x284]; Rva00406F9C mask; };
class UpgradeMux { public: void giveSelfUpgrade(); };
struct BfmeFixedStorage128 { unsigned int words[32]; BfmeFixedStorage128(const BfmeFixedStorage128 &); };
namespace _STL { template<unsigned N> struct _Base_bitset { unsigned long words[N]; void _M_do_or(const _Base_bitset &); }; }

class Rva004B4130
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02(Rva00406F9C *);
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11(void *a, void *b);
	virtual void v12();
	virtual bool v13();
	bool rva004B4130(Rva00406F9C *mask);
	void rva004B41A9();
private:
	char pad04[0x10-4]; Object *owner;
	char pad14[0x2C-0x14]; bool executed;
};

bool Rva004B4130::rva004B4130(Rva00406F9C *mask)
{
	Rva00406F9C buf100;
	Rva00406F9C buf80;
	((Rva001EAE6FHelper *)&buf80)->clear80();
	((Rva001EAE6FHelper *)&buf100)->clear80();
	v11(&buf80, &buf100);
	for (unsigned i = 0; i < 32; ++i) {
		if (buf80.m_data[i] != 0)
			goto haveBits;
	}
	return false;
haveBits:
	if (buf100.rva00406F9C(mask))
		return false;
	if (v13())
		return ((Rva002AA292 *)mask)->rva002AA292((const int *)&buf80);
	return mask->rva00406F9C(&buf80);
}

// Native4B41A9..4B4204 reads owner10/executed2C and calls vslots2/8.
// ZH UpgradeMux attempt/would/giveSelfUpgrade supplies the mask-dispatch
// purpose. This receiver's larger layout and original class name remain
// target-unidentified; preserve the existing address-derived owner view.
// Copy4548B and OR28C557 prove two 128-byte mask storages independently.
void Rva004B4130::rva004B41A9()
{
 BfmeFixedStorage128 mask(*(const BfmeFixedStorage128 *)&owner->getControllingPlayer()->mask);
 ((_STL::_Base_bitset<32> *)&mask)->_M_do_or(*(const _STL::_Base_bitset<32> *)&owner->mask);
 if (v02((Rva00406F9C *)&mask))
 {
  if (!executed) ((UpgradeMux *)this)->giveSelfUpgrade();
 }
 else v08();
}
