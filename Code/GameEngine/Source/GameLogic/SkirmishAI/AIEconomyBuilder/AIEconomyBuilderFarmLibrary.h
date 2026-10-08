#ifndef AIECONOMYBUILDER_FARM_LIBRARY_H
#define AIECONOMYBUILDER_FARM_LIBRARY_H
// WB AIEconomyBuilder::DoXferFarmLibrary (13835F0) names static m_farmList.
// Retail4EAA4B proves three pointer-vector words at E04494/E04498/E0449C.
// 4EA124 searches its pointees by +70; ctor596EEF initializes that same field.
// This POD only describes storage. Existing startup/shutdown rows retain
// responsibility for initialization and release; no new CRT helpers are emitted.
class Rva00596F18;
struct AIEconomyFarmLibraryStorage {
 Rva00596F18 **first;
 Rva00596F18 **finish;
 Rva00596F18 **end;
};
class Xfer;
class AsciiString;
// Native4EA93F supplies scalar18/count1C/int20 and pointer storage24.
// Named getter4EA176 independently proves player14. AIBuilder4EC1D9 embeds
// this subobject at B4 followed by AIWallBuilder at E4, bounding it to30.
class AIEconomyBuilder {
public:
 static AIEconomyFarmLibraryStorage m_farmList;
 AsciiString getFarmTemplateName();
 void DoXfer(Xfer *);
 unsigned char m_prefix00[0x14];
 void *m_14;
 unsigned int value18;
 unsigned int count1c;
 int value20;
 AIEconomyFarmLibraryStorage storage;
};
typedef char AIEconomyFarmLibraryStorageIs12Bytes[sizeof(AIEconomyFarmLibraryStorage)==12?1:-1];
#endif
