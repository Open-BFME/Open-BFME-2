// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004074B6@Rva004074B6@@QAEXABVAsciiString@@@Z retail 0x004074B6 25B
// Evidence: unlock lane; NameKey at +0x30 via TheNameKeyGenerator 0x00DF36A4 nameToKey 0x0009FA65 precedent NameKeyGeneratorRvaLowercaseKey plus memory findWeaponTemplate; caller 0x00408150; prev StringRecordCopy same /O1.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
class AsciiString;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva004074B6
{
public:
	void rva004074B6(const AsciiString &name);
private:
	char m_pad[0x30];
	NameKeyType m_key;
};

void Rva004074B6::rva004074B6(const AsciiString &name)
{
	m_key = TheNameKeyGenerator->nameToKey(name);
}
