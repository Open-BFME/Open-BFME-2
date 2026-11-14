// cl: /Ireference/shims/bfme2_ascii
// Zero Hour's UnicodeString.cpp defines the shared empty string; retail keeps it
// in .bss at VA 0x00E0C898, the address every reader in the ledger loads
// (GadgetTextEntryGetText, GameInfo::clearSlotList, ...). The export
// ?TheEmptyString@UnicodeString@@2V1@B makes it const.
//
// Retail builds it only through this definition's own dynamic initializer:
// native 007B6740..007B6756 (_$E1) calls the out-of-line default constructor
// at 00326BE6 and passes the cleanup 007B9C10..007B9C1A (_$E2), which calls the
// rowed destructor at 005B804E, to atexit. Neither constructor nor destructor
// is expanded inline in retail's copy, hence inline_depth(0).
#include "unicode_string.h"

#pragma inline_depth(0)
const UnicodeString UnicodeString::TheEmptyString;
#pragma inline_depth()
