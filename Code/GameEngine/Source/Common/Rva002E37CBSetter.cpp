// cl: /O1 /arch:SSE /G7 /MD
// 0x002E37CB / 26 bytes. The pointer update and +0x3C field displacement
// are direct retail evidence; the class owner remains an address-based name.

class Rva002E37CB
{
public:
	void rva002E37CB(void *value);

private:
	unsigned char m_pad00[0x0C];
	void *m_current;
};

void Rva002E37CB::rva002E37CB(void *value)
{
	*(void **)m_current = value;
	m_current = value ? (char *)value + 0x3C : 0;
}
