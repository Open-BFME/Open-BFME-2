// cl: /O1 /MD
// Scalar deleting destructors that retail reaches only through vtable slots,
// for classes with a virtual base. All six share the 35B shape: call the
// complete dtor, test the delete flag, then reset the virtual base's vptr at
// [this+VBOFF] to its own vftable (the inlined trivial ~VBase of ??_D) before
// the conditional scalar delete through pinned ??3@YAXPAX@Z 0x0002FD60.
// Target facts: the wrapper bytes, its REL32 callee at +4, the vbase store
// offset and the stored vftable address (0x00C6EE28 or 0x00BC6F20). The
// layout is a structural inference: one vbptr at +0, an opaque member block,
// then the virtual base at VBOFF; members, owners and the vbase's identity
// are not recovered and names are addresses. Each dtor is declared but not
// defined here and resolves through an address-derived pin in
// reverse/symbols.csv. The vbase classes need distinct names per vftable
// because one symbol may carry only one address. Emitted via delete anchors
// that are never called.
//  0x002E424F via dtor 0x002E4049, vbase +0x60 vft 0x00C6EE28
//  0x005381B9 via dtor 0x00538133, vbase +0x30 vft 0x00C6EE28
//  0x005CDB6C via dtor 0x005CD9C0, vbase +0x20 vft 0x00BC6F20
//  0x005CDF49 via dtor 0x005CDCEE, vbase +0x28 vft 0x00BC6F20
//  0x005E5628 via dtor 0x005E54F7, vbase +0x1C vft 0x00BC6F20
//  0x005E7003 via dtor 0x005E6F9D, vbase +0x24 vft 0x00BC6F20
// A disp32 vbase offset (0x80 and up) does not inline ??_D under /O1 in this
// non-virtual model, so the 38B members of this family are not here.

class VBase00C6EE28
{
public:
	virtual void slot00() = 0;
	~VBase00C6EE28() {}
};

class VBase00BC6F20
{
public:
	virtual void slot00() = 0;
	~VBase00BC6F20() {}
};

class Rva002E4049 : public virtual VBase00C6EE28
{
public:
	~Rva002E4049();
private:
	char m_unknown[0x5C];
};

class Rva00538133 : public virtual VBase00C6EE28
{
public:
	~Rva00538133();
private:
	char m_unknown[0x2C];
};

class Rva005CD9C0 : public virtual VBase00BC6F20
{
public:
	~Rva005CD9C0();
private:
	char m_unknown[0x1C];
};

class Rva005CDCEE : public virtual VBase00BC6F20
{
public:
	~Rva005CDCEE();
private:
	char m_unknown[0x24];
};

class Rva005E54F7 : public virtual VBase00BC6F20
{
public:
	~Rva005E54F7();
private:
	char m_unknown[0x18];
};

class Rva005E6F9D : public virtual VBase00BC6F20
{
public:
	~Rva005E6F9D();
private:
	char m_unknown[0x20];
};

void operator delete(void *p);

void Rva002E4049_DeleteAnchor(Rva002E4049 *p) { delete p; }
void Rva00538133_DeleteAnchor(Rva00538133 *p) { delete p; }
void Rva005CD9C0_DeleteAnchor(Rva005CD9C0 *p) { delete p; }
void Rva005CDCEE_DeleteAnchor(Rva005CDCEE *p) { delete p; }
void Rva005E54F7_DeleteAnchor(Rva005E54F7 *p) { delete p; }
void Rva005E6F9D_DeleteAnchor(Rva005E6F9D *p) { delete p; }
