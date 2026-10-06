// cl: /DNDEBUG /MD
// ?rva0028F518@Object@@QAEEXZ @ 0x0028F518 16B: chain from 0x0028F4EF landed
// this session; returns (rva0028F4EF() != 2) as unsigned char via setne.
// Same Object class and flags as neighbour ObjectRva0028F4EF.cpp. Unblocks 13.
class Object
{
public:
	int rva0028F4EF();
	bool rva0028F518();
};

bool Object::rva0028F518()
{
	return rva0028F4EF() != 2;
}
