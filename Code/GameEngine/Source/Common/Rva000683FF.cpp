// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000683FF@Rva000683FF@@QAEXQAVVector3@@W4ObjectID@@_N@Z retail 0x000683FF 11B unlock lane.
// Evidence: mov ecx,[ecx+0x385C] then tail-jmp to rowed
// ?addBib@W3DBibBuffer@@QAEXQAVVector3@@W4ObjectID@@_N@Z; unblocks 0x00092DD8.
class Vector3
{
public:
	float x, y, z;
};

enum ObjectID
{
	OID_0 = 0
};

class W3DBibBuffer
{
public:
	void addBib(Vector3 corners[4], ObjectID id, bool highlight);
};

class Rva000683FF
{
public:
	void rva000683FF(Vector3 corners[4], ObjectID id, bool highlight);
private:
	unsigned char m_pad[0x385C];
	W3DBibBuffer *m_bib;
};

void Rva000683FF::rva000683FF(Vector3 corners[4], ObjectID id, bool highlight)
{
	return m_bib->addBib(corners, id, highlight);
}
