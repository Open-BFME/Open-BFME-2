#pragma once
// BFME2 LAN peer address; LANAPI::LookupPlayer (0x0044998E) passes player+0x14 to the compare 0x00248CBF
// at 0x004499A2, then tests the word at +4 (0x004499AB) and compares the dword at +0 (0x004499B2/0x004499B4).
struct BfmeNetAddress {
 bool Rva00248CBF(const BfmeNetAddress *) const;
 unsigned int ip;
 unsigned short port;
};
