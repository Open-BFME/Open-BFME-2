// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EEF4@Rva0020EEF4Outer@@QAEHH@Z @0x0020EEF4 74B
// Predicate search over inner vector at *(this+8)+0x2C/+0x30: skips elements
// with +0x13C == -1, runs pinned 0x003F08D7(int) on each, returns its value
// on first nonzero (preserved eax, no mov), else 0. Reload-each-iteration
// count idiom like the proven EE29 trio; int (not bool) gives retail test
// eax and xor eax.
class Rva003F08D7
{
public:
	int rva003F08D7(int v);
};
struct Rva0020EEF4Inner
{
	char m_pad[0x2C];
	Rva003F08D7 **m_begin;
	Rva003F08D7 **m_end;
};
struct Rva0020EEF4Elem
{
	char m_pad[0x13C];
	int m_13C;
};
class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int v);
private:
	char m_pad[8];
	Rva0020EEF4Inner *m_inner;
};
int Rva0020EEF4Outer::rva0020EEF4(int v)
{
	Rva0020EEF4Inner *inner = m_inner;
	if (inner != 0)
	{
		for (unsigned i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i)
		{
			Rva0020EEF4Elem *element = (Rva0020EEF4Elem *)inner->m_begin[i];
			if (element->m_13C == -1)
				continue;
			int elementResult = ((Rva003F08D7 *)element)->rva003F08D7(v);
			if (elementResult)
				return elementResult;
		}
	}
	return 0;
}

// Native20EF3E..20EFA0 RET4: search the same region vector as20EEF4,
// ignoring unowned regions, and act on the first found plot with a building.
// Lookup3F083A is independently rowed in LivingWorldRegion.cpp. The second
// call3F1CA2 consumes the region in ECX and two stack arguments; reload it
// from the vector after the lookup, since the vector may have changed.
// Former bank's stdcall declaration omitted this receiver and six bytes.
// Names are measured ABI views; the original search method is unproven.
class CreateAHeroData { public: char prefix[0x20]; int field20; };
class Rva003F1093 { public:
 CreateAHeroData *rva003F083A(void *);
 void rva003F1CA2(CreateAHeroData *,bool);
};
class Rva0060EF3E { public: bool rva0060EF3E(int v); private: char prefix[8]; Rva0020EEF4Inner *inner; };
bool Rva0060EF3E::rva0060EF3E(int v) {
 if(inner) {
  Rva0020EEF4Inner *p=inner;
  for(unsigned i=0;i<(unsigned)(((char*)p->m_end-(char*)p->m_begin)>>2);++i) {
   Rva0020EEF4Elem *element=(Rva0020EEF4Elem*)p->m_begin[i];
   if(element->m_13C==-1)continue;
   CreateAHeroData *createAHeroData=((Rva003F1093*)element)->rva003F083A(reinterpret_cast<void *>(v));
   if(createAHeroData && createAHeroData->field20) {((Rva003F1093*)p->m_begin[i])->rva003F1CA2(createAHeroData,0); return 1;}
  }
 }
 return 0;
}
