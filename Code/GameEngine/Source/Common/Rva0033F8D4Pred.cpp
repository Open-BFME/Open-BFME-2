// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0033F8D4@AIUpdateInterface@@QBE_NXZ, retail 0x0033F8D4, 28 bytes.
// Returns m_1A0 != FLT_MAX (pool 0x007BB8E0). Called from 0x00342572 on the
// Object+0x258 AIUpdateInterface which returns -1 when false else copies the
// float bits. Layout is pad to +0x1A0 then float. Identity is the caller
// Object+0x258 chain (AIGroup precedent) plus FLT_MAX pool; method name
// stays honest rva like Object::rva0028AF76.

#include <cfloat>

class AIUpdateInterface
{
public:
	bool rva0033F8D4() const;

private:
	char m_pad00[0x1A0];
	float m_1A0;
};

bool AIUpdateInterface::rva0033F8D4() const
{
	return m_1A0 != FLT_MAX;
}
