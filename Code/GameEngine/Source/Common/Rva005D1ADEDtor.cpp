// cl: /O1 /DNDEBUG /MD
// ??1Rva005D1ADE@@UAE@XZ, 0x005D1ADE, 11B. Virtual dtor stores derived vptr then tail-jumps to pinned base ??1Rva005CCDDD@@UAE@XZ at 0x005CCDDD. Evidence: deleting dtor caller 0x005D1B85 in OpaqueScalarDeletingDtorsB16; vtable 0x00C75694.
class Rva005CCDDD
{
public:
	virtual ~Rva005CCDDD();
};
class Rva005D1ADE : public Rva005CCDDD
{
public:
	virtual ~Rva005D1ADE();
};
Rva005D1ADE::~Rva005D1ADE()
{
}
