// WaterArea: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_WATERAREA_H
#define CANONICAL_WATERAREA_H

class AsciiString;
class DataChunkInput;

class WaterArea
{
public:
	void parse(DataChunkInput &file, void *userData);
	void rva00537F74(const AsciiString &);
	void rva00537FA0(const AsciiString &);
};

#endif // CANONICAL_WATERAREA_H
