// cl: /O1 /DNDEBUG /MD
//
// Image::setStatus, retail 0x002D8E63, 15 bytes.
// OR bits into m_status at +0x30 and return the previous value.
// Kept out of AptMapPreviewPictureImage.cpp so that TU's caller
// cannot see this body (matching.md callee-visibility trap).

class Image
{
	unsigned char _M_layout[0x30];
	unsigned int m_status;

public:
	unsigned int setStatus(unsigned int bit);
};

unsigned int Image::setStatus(unsigned int bit)
{
	unsigned int old = m_status;
	m_status |= bit;
	return old;
}
