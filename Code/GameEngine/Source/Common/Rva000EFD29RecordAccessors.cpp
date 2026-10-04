// Donor1281192f68 Rva007B80D0Arr.cpp third indexed accessor, offset54->8.
// Native EFD29/13 reads pointer+8 and returns index*12 with ret4.
// Boundaries: complete preceding ret4 and following seven-byte getter.
// Original receiver/element names unknown; record fields opaque.
// cl: /O1 /G7 /arch:SSE2 /GX- /MD
struct Rva000EFD29Record12 { unsigned char opaque[12]; };
class Rva000EFD29IndexedRecords {
public: Rva000EFD29Record12 *rva000EFD29(int index);
private: unsigned char m_unknown00[8]; Rva000EFD29Record12 *m_records;
};
Rva000EFD29Record12 *Rva000EFD29IndexedRecords::rva000EFD29(int index) { return m_records + index; }

// Donor1281192f68 Rva007B80D0Arr.cpp indexed accessor as structural lead.
// Native EFD3D/14 indexes an INLINE52B array at+14, not a donor pointer.
// F1E48/114 independently constructs160 records with stride52 at+14.
// Record fields and original class identity remain unknown.
// cl: /O1 /G7 /arch:SSE2 /GX- /MD
struct Rva000EFD3DRecord52 { unsigned char opaque[52]; };
class Rva000EFD3DInlineRecords {
public: Rva000EFD3DRecord52 *rva000EFD3D(int index);
private: unsigned char m_unknown00[0x14]; Rva000EFD3DRecord52 m_records[160];
};
// ?rva000EFD3D@Rva000EFD3DInlineRecords@@QAEPAURva000EFD3DRecord52@@H@Z present-unmatched
Rva000EFD3DRecord52 *Rva000EFD3DInlineRecords::rva000EFD3D(int index) { return m_records + index; }
