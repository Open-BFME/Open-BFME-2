// cl: /DNDEBUG /MD
//
// ?rva002D7BB7@Radar@@QAEXPBX@Z @0x002D7BB7 28B Radar copy draw rect and set dirty.
// Evidence: copies 16B from arg to +0x144C via 4x movsd then byte 1 at +0x145C;
// same offsets as sibling rva002D7BD3 invalidate; caller 0x002D3275 passes
// this+0x68 rect with global Radar this; prev newMap and next rva002D7BD3 share class.

struct RadarRect16
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Radar
{
public:
	void rva002D7BB7(void const *src);
private:
	char m_pad[0x144C];
	RadarRect16 m_rect; // +0x144C 16B copied from arg
	unsigned char m_dirty; // +0x145C
};

void Radar::rva002D7BB7(void const *src)
{
	m_rect = *(RadarRect16 const *)src;
	m_dirty = 1;
}
