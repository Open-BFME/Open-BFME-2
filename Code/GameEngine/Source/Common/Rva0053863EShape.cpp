// cl: /O1 /MD /DNDEBUG /arch:SSE
//
// The 19-byte getter at 0x00538661 checks the dirty byte at +0x20, calls the
// existing pin spelling Rva0053863ESub::rva0053856F at 0x0053856F when set,
// then returns the float at +0x1C. The helper's identity remains unproven.

class Rva0053863ESub
{
public:
	void rva0053856F();
};

class Rva0053863EShape
{
public:
	float rva00538661() const;
private:
	unsigned char m_pad00[0x0C];
	unsigned char m_bounds[0x10]; // +0x0C..+0x1B
	float m_value1C; // +0x1C
	bool m_dirty20; // +0x20
};
float Rva0053863EShape::rva00538661() const
{
	if (m_dirty20)
		reinterpret_cast<Rva0053863ESub *>(const_cast<Rva0053863EShape *>(this))->rva0053856F();
	return m_value1C;
}
