// Target facts (addresses are RVAs): 0x001F458B reads four-byte pointers at +0 and +4, subtracts the former from the latter, and passes the start and byte count to File::write at vtable +0x10; that vptr belongs to File, not this text view.
// 0x0055FCCF calls ostringstream::str (0x001FA473); 0x0055FCDC passes its returned temporary to 0x001F458B, and 0x0055FCEF-0x0055FCF2 frees its first pointer. This struct covers only the eight-byte range prefix, not the complete owning string.
// The view has no virtual functions, bases or owned lifetime. The ledger spells its argument ABURva001F458BText@@ and has no member, constructor or destructor rows for it; the only rowed operation is the out-of-line free function below.

#pragma once

#ifndef __BFME2_RVA001F458BTEXT_H_
#define __BFME2_RVA001F458BTEXT_H_

struct Rva001F458BText
{
    const char *field00;
    const char *field04;
};

class File;
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);

#endif
