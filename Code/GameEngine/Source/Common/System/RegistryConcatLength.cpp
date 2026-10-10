// Native238C27..238C34: base length20F0D3 plus trailing pair length14.
// Existing RegistryAsciiPath writer238C34/materializer238C59 prove layout.
// cl: /O1 /G7 /arch:SSE /MD
class AsciiString;
struct Rva000B3F84Pair {const char*m_ptr;int m_len;};
struct Rva0020F58E {const AsciiString*first;Rva000B3F84Pair text;const AsciiString*second;int length()const;};
struct Rva00238C34:Rva0020F58E {Rva000B3F84Pair m_text2;int length()const;};
int Rva00238C34::length()const{return Rva0020F58E::length()+m_text2.m_len;}
