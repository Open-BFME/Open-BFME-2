// cl: /MD
// ?rva000CE147@W3DTankDraw@@UAEX_N@Z @0x000CE147 35B: vtable slot 35 of W3DTankDraw; if arg differs from byte at +0x49 and nonzero call enable-emitters 0xCE0EA then base setFullyObscuredByShroud 0xB6FFE; chain from just-landed 0xCE0EA
class W3DModelDraw {
public:
	virtual void setFullyObscuredByShroud(bool v);
};
class W3DTankDraw : public W3DModelDraw {
public:
	virtual void rva000CE147(bool v);
	void rva000CE0EA();
	char m_pad0[0x49 - 4];
	bool m_flag49;
};
void W3DTankDraw::rva000CE147(bool v)
{
	if (v != m_flag49 && v)
		rva000CE0EA();
	W3DModelDraw::setFullyObscuredByShroud(v);
}
