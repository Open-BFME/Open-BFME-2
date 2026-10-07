// ?rva00283033@Rva00283033@@QAE?AURva00283033Ref@@PAX@Z
// partial score=0.55 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /GX- /MD
// Native283033..283081 RET8. Eight-byte records at14/18 are scanned by
// their second word. Native factory28292B writes a single retained pointer
// and increases its +4 count; that pointer's release is native7DEEF.
// All names remain address derived; the reference holder is a layout view.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *) throw();
struct Rva00283033Node { unsigned first; int count; };
struct Rva00283033Ref
{
 Rva00283033Node *p;
 Rva00283033Ref() : p(0) {}
 Rva00283033Ref(const Rva00283033Ref &r) : p(r.p) { if (p) ++p->count; }
 ~Rva00283033Ref() throw() { if (p) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)p); }
};
struct Rva00283033Entry { unsigned first; void *key; };
class Rva00283033
{
public:
 Rva00283033Ref rva00283033(void *key);
 Rva00283033Ref rva0028292B(Rva00283033 *owner, unsigned index);
private:
 char pad[0x14]; Rva00283033Entry *m_begin; Rva00283033Entry *m_end;
};
Rva00283033Ref Rva00283033::rva00283033(void *key)
{
 Rva00283033Ref empty;
 for (unsigned index = 0; index < (unsigned)(m_end - m_begin); ++index)
  if (m_begin[index].key == key)
   return rva0028292B(this, index);
 return empty;
}
