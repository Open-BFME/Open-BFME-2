// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B08: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0008FFC4  0x000A43C8  0x00BC7DC8#0
//   0x001F45C3  0x000E14BD  0x00BC6F2C#0
//   0x000411A0  0x000411BC  0x00BC16C4#2
//   0x00072FC5  0x00072FE1  0x00BC6568#1
//   0x000416CB  0x000416E7  0x00BC2420#0
//   0x000657E6  0x006109C0  0x00BC5C6C#0
//   0x0006F1DD  0x0006F1F9  0x00BC6244#1
//   0x00079111  0x000D089D  0x00BC6870#0
//   0x000AB0B8  0x000AB0D4  0x00BC9468#0
//   0x00256B78  0x00256B94  0x00BF3E30#0

struct EmitVtableTag;

class Rva0008FF3E
{
public:
	Rva0008FF3E(EmitVtableTag *);
public:
	virtual ~Rva0008FF3E();
};

// ?<Rva0008FF3E::Rva0008FF3E> absent-from-retail
Rva0008FF3E::Rva0008FF3E(EmitVtableTag *)
{
}

class Rva000E14BD
{
public:
	Rva000E14BD(EmitVtableTag *);
public:
	virtual ~Rva000E14BD();
};

// ?<Rva000E14BD::Rva000E14BD> absent-from-retail
Rva000E14BD::Rva000E14BD(EmitVtableTag *)
{
}

class Rva000411BC
{
public:
	Rva000411BC(EmitVtableTag *);
public:
	virtual ~Rva000411BC();
};

// ?<Rva000411BC::Rva000411BC> absent-from-retail
Rva000411BC::Rva000411BC(EmitVtableTag *)
{
}

#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
class Rva0072AED : public RefCountClass
{
public:
	__declspec(dllimport) __forceinline Rva0072AED() : m_ref(0) {}
	virtual ~Rva0072AED();
	void *m_ref;
};

class W3DShroud;

class Rva00072FE1 : public Rva0072AED
{
public:
	Rva00072FE1(EmitVtableTag *);
public:
	virtual ~Rva00072FE1();
private:
	W3DShroud *m_owner;
};

// ?<Rva00072FE1::Rva00072FE1> absent-from-retail
Rva00072FE1::Rva00072FE1(EmitVtableTag *)
{
}

class Rva000416E7
{
public:
	Rva000416E7(EmitVtableTag *);
public:
	virtual ~Rva000416E7();
};

// ?<Rva000416E7::Rva000416E7> absent-from-retail
Rva000416E7::Rva000416E7(EmitVtableTag *)
{
}

// W3DShroudMaterialPassClass's vftable (0x00BC6244) is also emitted by
// W3DScene.cpp, which constructs the class: declare the same four slots
// (Delete_This, deleting dtor, Install_Materials, UnInstall_Materials) so
// both units emit one vftable instead of competing copies.
// The canonical MaterialPassClass supplies the inherited slots and layout.
#include "../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"

class W3DShroudMaterialPassClass : public MaterialPassClass
{
public:
	W3DShroudMaterialPassClass(EmitVtableTag *);
	virtual void Install_Materials(void) const;
	virtual void UnInstall_Materials(void) const;
public:
	virtual ~W3DShroudMaterialPassClass();
};

// ?<W3DShroudMaterialPassClass::W3DShroudMaterialPassClass> absent-from-retail
W3DShroudMaterialPassClass::W3DShroudMaterialPassClass(EmitVtableTag *) : MaterialPassClass()
{
}

class Rva000D089D
{
public:
	Rva000D089D(EmitVtableTag *);
public:
	virtual ~Rva000D089D();
};

// ?<Rva000D089D::Rva000D089D> absent-from-retail
Rva000D089D::Rva000D089D(EmitVtableTag *)
{
}

class Rva000AB0D4
{
public:
	Rva000AB0D4(EmitVtableTag *);
public:
	virtual ~Rva000AB0D4();
};

// ?<Rva000AB0D4::Rva000AB0D4> absent-from-retail
Rva000AB0D4::Rva000AB0D4(EmitVtableTag *)
{
}

class Rva00256B94
{
public:
	Rva00256B94(EmitVtableTag *);
public:
	virtual ~Rva00256B94();
};

// ?<Rva00256B94::Rva00256B94> absent-from-retail
Rva00256B94::Rva00256B94(EmitVtableTag *)
{
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x000E14BD reads ??1FXShaderParameterSourceNamespace@@UAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000E14BD@@UAE@XZ=??1FXShaderParameterSourceNamespace@@UAE@XZ")
//   0x00256B94 reads ??1StructureCollapseUpdateModuleData@@UAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00256B94@@UAE@XZ=??1StructureCollapseUpdateModuleData@@UAE@XZ")
