// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy-
// Packet CRC at retail 0x003EC8F7 (42 bytes), ported from the Open-BFME-1
// conversion (their Code/GameEngine/Source/GameNetwork/native_packet_crc.cpp,
// retail 0x00065250, same 42 bytes). Same accumulation the engine's CRC class
// uses -- rotate the running value left by one and add the byte -- as a free
// function taking and returning the running value. /Oy- keeps the ebp frame;
// without it MSVC omits the frame and the prologue/epilogue diverge.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

// The carry bit has to be written as a branch, exactly as the engine's own CRC
// class writes it, even though MSVC compiles it to a shift either way. Written
// as `crc >> 31` the compiler folds the byte and the carry together and adds
// crc*2 last; written as the branch it keeps retail's order, adding the byte to
// crc*2 first and the carry after.
UnsignedInt ComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc)
{
	if (data != 0) {
		while (length > 0) {
			Int hibit;
			if (crc & 0x80000000) {
				hibit = 1;
			} else {
				hibit = 0;
			}
			crc <<= 1;
			crc += *data;
			++data;
			crc += hibit;
			--length;
		}
	}

	return crc;
}
