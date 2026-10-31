// Replaces reference/open-bfme-1/inputs/reference/shims/stringbaseascii/Common/AsciiString.h.
// BFME 2: scope exits call releaseBuffer 0x00036410 directly (RiderInfo dtor 0x0047E3AC), which
// is the registered AsciiString header's shape; Zero Hour headers reach it through this name.
#pragma once
#include "../../bfme2_ascii/ascii_string.h"
#define ASCIISTRING_H
