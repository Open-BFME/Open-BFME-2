// cl: /DNDEBUG /MD
// ?rva004031C9@AttributeModifierPoolUpdate@@QAEHH@Z retail 0x004031C9 20B
// Index-checked int fetch from +0x6c array of 15: if index>=15 return 0 else
// return m_array[index]. Evidence: mov eax-esp+4 cmp 0xf jge mov
// ecx-eax-4-0x6c xor else; caller 0x0040327B passes this+0xc and dec-cmp-clamp
// uses int return; unblocks 2; Class proven via findAttributeModifierPoolUpdate.
class AttributeModifierPoolUpdate
{
public:
	int rva004031C9(int index);
private:
	char _pad[0x6C];
	int m_array[15];
};
int AttributeModifierPoolUpdate::rva004031C9(int index)
{
	if (index < 15)
		return m_array[index];
	return 0;
}
