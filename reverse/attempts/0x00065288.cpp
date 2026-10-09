// ??1Rva0065288@@UAE@XZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class W3DModelDrawModuleData {
public: virtual ~W3DModelDrawModuleData();
private: char fields04[0x188-4];
};
class Rva0065288 : public W3DModelDrawModuleData {
public: virtual ~Rva0065288();
private: AsciiString strings[4];
};
Rva0065288::~Rva0065288() {}
