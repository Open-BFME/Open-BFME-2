// cl: /O1 /MD
// One-argument CRC-32 string hash at retail 0x003EC922 (49 bytes). Same
// table-driven accumulation as the two-argument family in realcrc.cpp, but a
// standalone one-shot wrapper: a null or empty input
// returns 0, otherwise the seed is 0xFFFFFFFF and the result is inverted. The
// index is the raw ((char)crc ^ c) xor with no 0xFF mask. /O1 keeps the retail
// inc-edx pointer step; /O2 widens it to add edx,1.
// Not WWLib's CRC32_Table (.data 0x00DD5A90): both bodies here read the
// identical-content .rdata copy at 0x00C35BD0, so it gets its own
// address-derived name (owner unknown).
extern unsigned long Rva00835BD0Crc32Table[256];

unsigned long CRC_String(char const *string)
{
  unsigned long crc = 0;
  char c;
  if (string != 0 && (c = *string) != 0) {
    crc = 0xFFFFFFFF;
    do {
      ++string;
      crc = (crc >> 8) ^ Rva00835BD0Crc32Table[(char)crc ^ c];
      c = *string;
    } while (c != 0);
    crc = ~crc;
  }
  return crc;
}

unsigned long CRC_Stringi(char *string)
{
  unsigned long crc = 0;
  char c;
  if (string != 0 && (c = *string) != 0) {
    crc = 0xFFFFFFFF;
    do {
      ++string;
      if (c >= 'a' && c <= 'z')
        c &= 0xDF;
      crc = (crc >> 8) ^ Rva00835BD0Crc32Table[(char)crc ^ c];
      c = *string;
    } while (c != 0);
    crc = ~crc;
  }
  return crc;
}
