// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// ?Update_Current_Buffer@FontCharsClass@@AAEXH@Z @0x00156490 164B
// FontChars glyph-buffer rotation: when the buffer list is empty or the
// scaled advance would pass the tail buffer's BufferMax, grows a new
// BfmeFontCharsBuffer clamped to 0x8000 and appends it via DynamicVector Add.
// Evidence: BFME1 donor FontCharsClass::Update_Current_Buffer in
// reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp
// plus rowed callees operator new 0x0002FDA0 and BfmeFontCharsBuffer ctor
// 0x001541E0 and DynamicVector Add 0x001A3A60; LINK BONUS via 0x00156A60.

typedef unsigned short uint16;

class FontCharsBuffer
{
public:
	uint16 *Buffer;
};

class BfmeFontCharsBuffer
{
public:
	BfmeFontCharsBuffer(int buffer_size);
	uint16 *Buffer;		// +0
	int BufferMax;		// +4
	int BufferPosition;	// +8
};

template <typename T>
class DynamicVectorClass
{
public:
	bool Add(const T &item);
	T &operator[](int index) { return _vector[index]; }
	int Count() const { return _count; }
public:
	int _pad0;
	T *_vector;	// +4 -> absolute +0x14 when list at +0x10
	int _pad8;
	int _padC;
	int _count;	// +0x10 -> absolute +0x20 when list at +0x10
	int _pad14;
};

class FontCharsClass
{
	char _pad00[0x10];
public:
	DynamicVectorClass<FontCharsBuffer *> m_bufferList;	// +0x10
	int m_currPixelOffset;	// +0x28
	int m_charHeight;	// +0x2C
private:
	void Update_Current_Buffer(int char_width);
};

void FontCharsClass::Update_Current_Buffer(int char_width)
{
	bool needs_new_buffer = (m_bufferList.Count() == 0);
	int buffer_size = m_charHeight * char_width;
	if (!needs_new_buffer) {
		BfmeFontCharsBuffer *current_buffer = reinterpret_cast<BfmeFontCharsBuffer *>(m_bufferList[m_bufferList.Count() - 1]);
		if ((m_currPixelOffset + buffer_size) > current_buffer->BufferMax)
			needs_new_buffer = true;
	}
	if (needs_new_buffer) {
		if (buffer_size < 0x8000)
			buffer_size = 0x8000;
		BfmeFontCharsBuffer *new_buffer = new BfmeFontCharsBuffer(buffer_size);
		m_bufferList.Add(reinterpret_cast<FontCharsBuffer *>(new_buffer));
		m_currPixelOffset = 0;
	}
}
