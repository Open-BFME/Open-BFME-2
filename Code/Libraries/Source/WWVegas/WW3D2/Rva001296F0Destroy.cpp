// cl: /O2 /G7 /DNDEBUG /MD
// ?Rva001296F0Destroy@@YAXXZ, retail 0x001296F0, 10 bytes.
// Evidence: mov ecx textureStatisticsString 0x009EE91C then jmp pinned dtor
// ??1Rva001880D0Dtor@@UAE@XZ 0x001880D0; caller unclaimed at 0x0004A155;
// neighbours Rva00129640Cluster /O2 /G7 and part_buf.
class Rva001880D0Dtor
{
public:
	virtual ~Rva001880D0Dtor();
};

extern "C" Rva001880D0Dtor textureStatisticsString;

void __cdecl Rva001296F0Destroy()
{
	textureStatisticsString.~Rva001880D0Dtor();
}
