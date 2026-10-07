// cl: /MD
//
// ?rva00126077@Rva00126077@@QAEPAXH@Z, RVA 0x00126077, 11B.
// Indexed fetch from an inline pointer array at +0x24:
// mov eax [esp+4]; mov eax [ecx+eax*4+0x24]; ret 4.
// The masked .text search once placed RenderInfoClass::Peek_Additional_Pass
// here from rinfo.cpp's Zero Hour layout, but retail MeshClass::Render
// (0x0014BB90) reaches this build's Peek_Additional_Pass at 0x00142C30, whose
// array sits at +0x30. This body has no REL32 callers and no data references,
// so its owner is unknown; honest address name.

class Rva00126077
{
	char m_pad[0x24];
	void *m_items[16];

public:
	void *rva00126077(int index);
};

void *Rva00126077::rva00126077(int index)
{
	return m_items[index];
}
