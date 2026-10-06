// cl: /MD
//
// Texture-stage setter next to the MaterialPassClass destructor pair at
// 0x0013EE40/0x0013EF80. Same one-word owning wrapper layout the destructor
// file documents: the stage array sits at +8 (vtable plus refcount word) and
// each stage is a single texture pointer. The incoming pointer is a wrapper
// whose first word is the texture, so the assignment addrefs the new texture,
// releases the old, then stores. Release_Ref is the pinned TextureBaseClass
// body at 0x0061ED10. Class and method names are this image's addresses.

class TextureBaseClass
{
public:
	void Add_Ref() { ++m_refs; }
	void Release_Ref();

private:
	void *m_vtable;			// +0x00
	unsigned short m_refs;		// +0x04
};

struct Rva0013EEB0Stage
{
	TextureBaseClass *Pointer;
};

class Rva0013EEB0PassClass
{
public:
	void Rva0013EEB0(Rva0013EEB0Stage *incoming, int index);

private:
	char m_pad[8];			// vtable + refcount
	Rva0013EEB0Stage Stages[8];
};

// ?Rva0013EEB0@Rva0013EEB0PassClass@@QAEXPAURva0013EEB0Stage@@H@Z @ 0x0013EEB0 (61B)
void Rva0013EEB0PassClass::Rva0013EEB0(Rva0013EEB0Stage *incoming, int index)
{
	TextureBaseClass **slot = &Stages[index].Pointer;

	if (incoming->Pointer)
		incoming->Pointer->Add_Ref();

	if (*slot)
		(*slot)->Release_Ref();

	*slot = incoming->Pointer;
}
