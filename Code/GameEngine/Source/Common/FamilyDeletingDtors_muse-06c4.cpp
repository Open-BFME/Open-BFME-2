// cl: /O1 /MD
// ??_GW3DProjectileStreamDrawModuleData@@UAEPAXI@Z @0x000D1354, 28B.
// Scalar deleting dtor slot 0 of vtable 0x007CDF18; calls rowed ??1 at
// 0x000D1226 plus rowed delete at 0x0002FD60.

// ??_GW3DProjectileStreamDrawModuleData@@UAEPAXI@Z @0x000D1354
class W3DProjectileStreamDrawModuleData { public: __declspec(noinline) virtual ~W3DProjectileStreamDrawModuleData(); private: int m_famgen;
  friend void famgenDelete(W3DProjectileStreamDrawModuleData *p); };
W3DProjectileStreamDrawModuleData::~W3DProjectileStreamDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DProjectileStreamDrawModuleData *p) { delete p; }

// ??_GRva008A2C80@@UAEPAXI@Z @0x006E6B10, 35B.
// Scalar deleting dtor slot 1 of vtable 0x008EC278; calls rowed ??1 at
// 0x006E5FF0 plus sized pool free via pinned 0x006DB270 with pool at
// 0x00E176E8 and class size 0x38. Same sized-pool recipe as Rva006FBA10.

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva008A2C80 { public: __declspec(noinline) virtual ~Rva008A2C80();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
	char m_pad[0x38 - 4]; };
Rva008A2C80::~Rva008A2C80() { m_pad[0] = 0; }
void deleteRva008A2C80(Rva008A2C80 *p) { delete p; }
