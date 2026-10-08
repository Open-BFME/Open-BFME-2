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
class AIEconomyBuilder {public:static AIEconomyFarmLibraryStorage m_farmList;};
typedef char AIEconomyFarmLibraryStorageIs12Bytes[sizeof(AIEconomyFarmLibraryStorage)==12?1:-1];
#endif
