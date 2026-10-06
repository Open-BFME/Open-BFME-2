// cl: /MD
// ?rva002761F3@Drawable@@QAEXPBH0@Z @0x002761F3 48B: set pendingClear at +0x2A4 and pendingSet at +0x2F0 from 19-dword masks then apply with immediate true.
// Evidence: callee Drawable_rva00274176.cpp layout plus rowed 0x00274176 via caller 0x000BFC16; rep movsd 0x13.

class Rva00271C8A
{
public:
	void rva00271C8A(const int *a, const int *b);
	int m_bits[19];
};

class BfmeDrawableClientIface
{
public:
	virtual void replaceModelConditionState(const void *state, bool immediate, int effect);
};

class Drawable
{
public:
	void rva002761F3(const int *a, const int *b);
	void rva00274176(bool immediate);

private:
	unsigned char m_pad0[0x158];
	BfmeDrawableClientIface **m_ifaceBegin;
	BfmeDrawableClientIface **m_ifaceEnd;
	unsigned char m_pad1[0x258 - 0x160];
	Rva00271C8A m_conditionState;
	Rva00271C8A m_pendingClear;
	Rva00271C8A m_pendingSet;
	unsigned char m_pad2[0x443 - 0x33C];
	bool m_isModelDirty;
};

void Drawable::rva002761F3(const int *a, const int *b)
{
	m_pendingClear = *(const Rva00271C8A *)a;
	m_pendingSet = *(const Rva00271C8A *)b;
	rva00274176(true);
}
