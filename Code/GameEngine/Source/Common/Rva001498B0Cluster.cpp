// cl: /DNDEBUG /MD
// Two one-off bodies in the Disp8ByteFieldGetters.cpp page of
// Code/GameEngine/Source/Common.  Both act on the same object pointer slot at
// +0xC4 (a MeshModelClass-family model in 0x00149F20), so they are kept in one
// address-named cluster file.  The near getters file carries no `// cl:` line,
// but 0x001498B0's add dword [ecx+4],-1 decrement only comes out of /G7, so the
// Pentium-4 setting is carried here (0x00149F20 is unaffected by it).
//
// 0x001498B0 (35B): release the +0xC4 pointer: decrement its refcount at +4,
//   call virtual slot 0 when it reaches zero, then clear the slot.
// 0x00149F20 (26B): RAM-size query returning the fixed 0x324-byte overhead plus
//   MeshModelClass::Compute_Ram_Size (rowed 0x001880E0) when the slot is set.

class MeshModelClass
{
public:
	int Compute_Ram_Size();
};

class Rva001498B0Object
{
public:
	virtual void ReleaseRef();
	int m_refCount;	// +0x04
};

class Rva001498B0Holder
{
public:
	void releaseModel();

private:
	char m_pad00[0xC4];
	Rva001498B0Object *m_model;	// +0xC4
};

void Rva001498B0Holder::releaseModel()
{
	Rva001498B0Object *model = m_model;
	if (model != 0) {
		if (--model->m_refCount == 0)
			model->ReleaseRef();
		m_model = 0;
	}
}

class Rva00149F20Holder
{
public:
	int get() const;

private:
	char m_pad00[0xC4];
	MeshModelClass *m_model;	// +0xC4
};

int Rva00149F20Holder::get() const
{
	int size = 0x324;
	if (m_model != 0)
		size += m_model->Compute_Ram_Size();
	return size;
}
