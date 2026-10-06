// cl: /EHsc /MD /DNDEBUG
//
// BfmeFontCharsBuffer::BfmeFontCharsBuffer at 0x001541E0 (65 bytes).
//
// The 12-byte font glyph buffer: BufferMax takes the requested size,
// BufferPosition resets, and the uint16 Buffer array is array-allocated and
// zero-filled. Retail-measured layout is Buffer at +0, BufferMax at +4,
// BufferPosition at +8; the sibling Update_Current_Buffer body (retail
// 0x00156490, reconstructed from the BFME1 donor but scheduler-walled on one
// register choice) allocates through this constructor and is banked in
// reverse/attempts until the lever lands.

#include <string.h>

typedef unsigned short uint16;

void *__cdecl operator new[](unsigned int size);

struct BfmeFontCharsBuffer
{
	BfmeFontCharsBuffer(int buffer_size);

	uint16 *Buffer;		// +0x00
	int BufferMax;		// +0x04
	int BufferPosition;	// +0x08
};

BfmeFontCharsBuffer::BfmeFontCharsBuffer(int buffer_size)
{
	BufferMax = buffer_size;
	BufferPosition = 0;
	Buffer = new uint16[buffer_size];
	if (Buffer != 0) {
		memset(Buffer, 0, buffer_size * sizeof(uint16));
	}
}
