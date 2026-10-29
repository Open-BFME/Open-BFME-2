// cl: /O1 /DNDEBUG /MD
//
// Pointer-field forwarders: each body loads a pointer from a fixed field of
// its own object and tail-jumps a rowed member of the pointee
// (mov ecx, [ecx+<field>]; jmp). The targets are only declared here, so the
// call is not inlined as it would be beside their definitions. Owners are
// unknown; names are address-derived and no referencing site was found for
// these in this pass.
class Rva0030812E { public: void *getTextureName(int i); };
class Rva002C9400ByteField { public: unsigned char get() const; };
class Rva002C9407ByteField { public: unsigned char get() const; };
class Rva005E3266 { public: void rva005E3266(); };
class Rva0013EDC0DwordField { public: int get() const; };

// 0x0007E0C6: [ecx+0x40] -> Rva0030812E::getTextureName(int)
class Rva0007E0C6Owner
{
public:
	void *rva0007E0C6(int i);
private:
	char m_pad00[0x40];
	Rva0030812E *m_target;
};
void *Rva0007E0C6Owner::rva0007E0C6(int i) { return m_target->getTextureName(i); }

// 0x0026237F: [ecx+4] -> Rva002C9400ByteField::get
class Rva0026237FOwner
{
public:
	unsigned char rva0026237F() const;
private:
	char m_pad00[0x4];
	Rva002C9400ByteField *m_target;
};
unsigned char Rva0026237FOwner::rva0026237F() const { return m_target->get(); }

// 0x0033F9C2: [ecx+4] -> Rva002C9407ByteField::get
class Rva0033F9C2Owner
{
public:
	unsigned char rva0033F9C2() const;
private:
	char m_pad00[0x4];
	Rva002C9407ByteField *m_target;
};
unsigned char Rva0033F9C2Owner::rva0033F9C2() const { return m_target->get(); }

// 0x005CC7DC: [ecx+8] -> Rva005E3266::rva005E3266
class Rva005CC7DCOwner
{
public:
	void rva005CC7DC();
private:
	char m_pad00[0x8];
	Rva005E3266 *m_target;
};
void Rva005CC7DCOwner::rva005CC7DC() { m_target->rva005E3266(); }

// 0x006C0830: [ecx+0x10] -> Rva0013EDC0DwordField::get
class Rva006C0830Owner
{
public:
	int rva006C0830() const;
private:
	char m_pad00[0x10];
	Rva0013EDC0DwordField *m_target;
};

// 0x00262377: [ecx+4] -> the rowed false-returning const predicate folded at
// 0x0047A699 (ledger spellings include WeaponTemplate::isContactWeapon and
// the Xfer mode predicates; which one the original called is not proven).
class WeaponTemplate { public: bool isContactWeapon() const; };
class Rva00262377Owner
{
public:
	bool rva00262377() const;
private:
	char m_pad00[0x4];
	WeaponTemplate *m_target;
};
bool Rva00262377Owner::rva00262377() const { return m_target->isContactWeapon(); }

// 0x002B2964: [ecx+0xB0] -> Rva0020E3D6::rva0020E3D6(void *), passing the
// one stack argument through to the callee's ret 4.
class Rva0020E3D6 { public: void rva0020E3D6(void *arg); };
class Rva002B2964Owner
{
public:
	void rva002B2964(void *arg);
private:
	char m_pad00[0xB0];
	Rva0020E3D6 *m_target;
};
void Rva002B2964Owner::rva002B2964(void *arg) { m_target->rva0020E3D6(arg); }
