// cl: /O1 /MD /DNDEBUG
//
// ?setMode@Rva00785FD0Renderer@@QAIXH@Z, retail 0x001100CA, 12 bytes,
// pinned from rva00785FD0Flush (0x000AA5E1): a __fastcall member (this in
// ecx, mode in edx) that stores a new mode at +8 and raises the dirty byte
// at +0 only when the mode changes. Class identity not recovered.

class Rva00785FD0Renderer
{
public:
	void __fastcall setMode(int mode);
private:
	bool m_dirty;
	unsigned char m_pad01[0x08 - 0x01];
	int m_mode;
};

void __fastcall Rva00785FD0Renderer::setMode(int mode)
{
	if (m_mode != mode)
	{
		m_mode = mode;
		m_dirty = true;
	}
}
