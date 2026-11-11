// DataChunkParser: canonical declarations for the members 11 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_DATACHUNKPARSER_H
#define CANONICAL_DATACHUNKPARSER_H

class AsciiString;
class DataChunkInput;

class DataChunkParser
{
public:
	DataChunkParser(DataChunkInput *input, const AsciiString *label, const AsciiString *parentLabel);
};

#endif // CANONICAL_DATACHUNKPARSER_H
