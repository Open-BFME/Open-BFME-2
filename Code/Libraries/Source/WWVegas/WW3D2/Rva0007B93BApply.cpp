// cl: /O1 /MD /EHsc /DNDEBUG
// Retail 0x0007B93B..0x0007B9EE (179B), whole body through RET 8.
// Identity remains address-derived. Target virtual slot +0x24 supplies a holder;
// its matched 0x0007B9EE getter returns a four-byte owning AssetReference by value.
// The first temporary lives only through the short-circuit null test; the second
// through the matched 0x001514D0 index-zero lookup. Their natural destructors call
// the existing CountedAsset::Release_Ref at 0x0061ED10, including exception cleanup.
// Retail independently proves holder state +0x20, receiver previous state +0x0C,
// and optional step pointer +0x08 with a bool two-int virtual call at slot +0x08.
// BFME 1 donor 874e38488 game/.../WW3D2/dxwrapper.cpp asset walk is the semantic
// lead for owning temporaries, not evidence of this wrapper's original name.
class CountedAsset { public: void Release_Ref(); };
class Rva001514D0 { public: void *rva001514D0(int); };
class AssetReference {
public:
 AssetReference(const AssetReference &);
 ~AssetReference() { if(m_object) m_object->Release_Ref(); }
 bool IsNull() const { return m_object == 0; }
 Rva001514D0 *View() { return reinterpret_cast<Rva001514D0*>(this); }
private: CountedAsset *m_object;
};
class Rva0007B9EE {
public: AssetReference rva0007B9EE();
 char m_pad00[0x20]; void *m_state20;
};
class Rva0007B93BStep {
public: virtual void slot0(); virtual void slot4(); virtual bool Apply(int,int);
};
class Rva0007B93B {
public:
 virtual void slot0(); virtual void slot4(); virtual void slot8();
 virtual void slotC(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual Rva0007B9EE *holder();
 bool rva0007B93B(int,int);
private: int m_pad04; Rva0007B93BStep *m_step08; void *m_previous0C;
};
bool Rva0007B93B::rva0007B93B(int a, int b)
{
 Rva0007B9EE *h = holder();
 if(!h || h->rva0007B9EE().IsNull()) return false;
 void *result = h->rva0007B9EE().View()->rva001514D0(0);
 if(!result) return false;
 m_previous0C = h->m_state20;
 h->m_state20 = result;
 if(!m_step08) return false;
 return m_step08->Apply(a,b);
}
