// cl: /MD
// ?Rva0041BB26Check@@YGEPAVRva0041BB26Obj@@HH@Z @0x0041BB26 35B
// Free function at 0x0041BB26 (35B): null-check then MaterialPassClass::Peek_Texture.
// Evidence: rowed callee ?Peek_Texture@MaterialPassClass@@QBEPAVTextureClass@@H@Z; caller 0x0029CE57; ret 0xc with third arg unused like neighbours Rva0041B8D2 and Rva0041BB87.
class TextureClass;
class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int i) const;
};
class Rva0041BB26Obj
{
public:
	char m_pad[0x330];
	MaterialPassClass m_pass;
};
unsigned char __stdcall Rva0041BB26Check(Rva0041BB26Obj *a, int b, int unused)
{
	if (a == 0)
		return 0;
	return a->m_pass.Peek_Texture(b) != 0;
}
