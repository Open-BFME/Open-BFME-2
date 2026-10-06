// cl: /DNDEBUG /MD
// ?rva005DB023@Rva005DB023@@QAEXXZ 0x005DB023 16B
// Calls 0x39B246 then tail-jmps to 0x5DB004 copy.
// Evidence: caller 0x59B2AA; unblocks 0x59B1EC.
class Rva0039B20C
{
public:
	void rva0039B246();
};

class Rva005DB004
{
public:
	void rva005DB004();
};

class Rva005DB023
{
public:
	void rva005DB023();
};

void Rva005DB023::rva005DB023()
{
	((Rva0039B20C*)this)->rva0039B246();
	((Rva005DB004*)this)->rva005DB004();
}
