// Address-named constructor at retail 0x006587C0 (27B).
// The BFME1 constructor body is an ICF-shared lead, not an identity claim.
// Retail establishes these fields and values directly; the owning class
// remains unidentified, so this uses an address-derived layout view.

// The vftable at VA 0x00CE157C and the 13-byte printf("%s") callback at
// 0x006587B0 are the globals the matched rows already name.
extern void *g_bfmeVftTDA[];
void printText(void *context, const char *text);

struct Rva006587C0View
{
	void *m_vtable;
	void (*m_callback)(void);
	unsigned int m_fields[ 3 ];

	Rva006587C0View();
};

Rva006587C0View::Rva006587C0View()
{
	m_vtable = g_bfmeVftTDA;
	m_callback = reinterpret_cast<void (*)(void)>( &printText );
	m_fields[ 0 ] = 0;
	m_fields[ 1 ] = 0;
	m_fields[ 2 ] = 0;
}
