// cl: /DNDEBUG /MD

// ?rva00276B95@Drawable@@QAEXXZ, RVA 0x00276B95, 20B. Unlock lane: flag
// byte at +0x43C via lea plus cmp-je early-out then clear plus tail-jmp to
// rowed Drawable::rva00275545 0x00275545. Caller 0x0029F371 in 0x0029F34F.
// Same Drawable class as neighbours 0x0027656F and 0x00278689.
class Drawable
{
public:
	void rva00276B95();
	void rva00275545();

private:
	char m_pad00[0x43c];
	bool m_43c;
};

void Drawable::rva00276B95()
{
	if (!m_43c)
		return;
	m_43c = false;
	return rva00275545();
}
