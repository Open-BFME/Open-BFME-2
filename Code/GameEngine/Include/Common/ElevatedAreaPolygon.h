// ElevatedAreaPolygon: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_ELEVATEDAREAPOLYGON_H
#define CANONICAL_ELEVATEDAREAPOLYGON_H

class DataChunkInput;

class ElevatedAreaPolygon
{
public:
	void parse(DataChunkInput &file, int val);
};

#endif // CANONICAL_ELEVATEDAREAPOLYGON_H
