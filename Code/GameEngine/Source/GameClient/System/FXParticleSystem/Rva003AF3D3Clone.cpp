// cl: /EHsc

// ?clone@Rva003AF3D3@@QBEPAV1@XZ @0x003AF39C 55B: vslot 2 (offset 0x8) of vtable 0x0081CFF8
// (class of ??0Rva003AF3D3@@QAE@ABV0@@Z in ParticleModuleTemplateCopyCtors.cpp).
// Same EH new-plus-copy shape as rowed clones 0x003AEAA3 (push 0xAC) and 0x003AEF34
// (push 0xB4) and landed 0x003AF127 (push 0x40) 0x003AF1D1 (push 0x28) and 0x003AF2F2
// (push 0x34); here push 0x34 plus rowed copy Rva003AF3D3. Donor BFME1
// DefaultModuleTag1ConcreteModuleTemplateCloneThunk.cpp (clone via new plus copy).

class Rva003AF3D3
{
public:
	Rva003AF3D3(const Rva003AF3D3 &other);
	Rva003AF3D3 *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	char m_pad1C[24]; // +0x1C..0x33: makes sizeof 0x34 for new
};

Rva003AF3D3 *Rva003AF3D3::clone() const
{
	return new Rva003AF3D3(*this);
}
