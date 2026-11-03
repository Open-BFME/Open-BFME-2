// Target facts: operator() at RVA 0x005E4300 (137 bytes) loads the pointer at this+0 (0x005E4303), uses its +0x78 index (0x005E4305) and +0x18 string (0x005E4316), returns AL and pops two by-value integers (0x005E4386). Its ledger spelling is ??RRva005E4300Cmp@@QBEDHH@Z.
// Retail passes the comparator as one four-byte word at 0x005E4A08; partition 0x005E4829 passes that word's address as this to 0x005E4300. The wrapper at 0x005E4523 reads the next integer at +4. The pointer exhausts the four-byte layout: no vptr or virtual functions, and no constructor, destructor or vftable rows name this class.
// Populate at 0x005E5368 passes its army pointer directly as the comparator to sort (0x005E5371); EntryAdded does the same at 0x005E4F12..0x005E4F1D. Rva005E4300Cmp and Rva005E4300Context are provisional identities; field_00 is a neutral label.
#pragma once

#ifndef BFME2_RVA005E4300CMP_H
#define BFME2_RVA005E4300CMP_H

struct Rva005E4300Context;

class Rva005E4300Cmp
{
public:
    explicit Rva005E4300Cmp(Rva005E4300Context *context) : field_00(context) {}
    char operator()(int, int) const;

private:
    Rva005E4300Context *field_00;
};

#endif
