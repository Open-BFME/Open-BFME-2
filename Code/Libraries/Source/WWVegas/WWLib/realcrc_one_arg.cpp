// cl: /O1 /MD
// One-argument CRC-32 string hash at retail 0x003EC922 (49 bytes). Same
// table-driven accumulation as the two-argument family in realcrc.cpp, sharing
// its CRC32_Table, but a standalone one-shot wrapper: a null or empty input
// returns 0, otherwise the seed is 0xFFFFFFFF and the result is inverted. The
// index is the raw ((char)crc ^ c) xor with no 0xFF mask. /O1 keeps the retail
// inc-edx pointer step; /O2 widens it to add edx,1.
extern unsigned long CRC32_Table[256];

unsigned long CRC_String(char const *string)
{
  unsigned long crc = 0;
  char c;
  if (string != 0 && (c = *string) != 0) {
    crc = 0xFFFFFFFF;
    do {
      ++string;
      crc = (crc >> 8) ^ CRC32_Table[(char)crc ^ c];
      c = *string;
    } while (c != 0);
    crc = ~crc;
  }
  return crc;
}
