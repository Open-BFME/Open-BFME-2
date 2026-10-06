// cl: /O2 /MD
// ?bfmeErase1279@BfmeLookup1279@@QAEXAAUBfmeKey1279@@@Z @0x0070B2C0 191B BfmeLookup erase.
// Retail erases hash entry via rva0070AF90 then clears magic slots +0xC/+0x8.
// Layout and magic ids (0x699/0x6bbd via GetString 0x78/0) mirror rowed lookup
// Rva0070B380::lookup in Rva0070B380Cluster.cpp. Evidence: linkbody lane;
// LINK BONUS name; callees rowed plus pin rva0070AF90; caller 0x006F7275.
class EAStringC
{
public:
	bool IsEmpty() const;
	unsigned short rva006D3D10() const;
	void rva006D3470();
	bool rva006D3560(const EAStringC *other) const;
};
struct AptHashItem;
class BfmeLookup1279;
class AptNativeHash
{
// Rowed provider at 0x0070AF90:
// ?HashFindKey@AptNativeHash@@ABEPAUAptHashItem@@QBVEAStringC@@@Z (private const).
// Same ABI as the pinned spelling (this in ecx, 4B key address on stack,
// pointer return in eax); friend grants this TU's private-view access.
	AptHashItem *HashFindKey(const EAStringC *const) const;
	friend class BfmeLookup1279;
};
EAStringC *Rva0070B4F0GetString(int index);
void Rva0070A6D0Release(void *p);
struct BfmeKey1279
{
	EAStringC m_key;
};
class AptRefCounted
{
public:
	virtual void v0();
	virtual void v1();
};
class BfmeLookup1279
{
	char m_pad0[4];
	void *m_map;
	AptRefCounted *m_8;
	AptRefCounted *m_c;
public:
	void bfmeErase1279(BfmeKey1279 &key);
};
void BfmeLookup1279::bfmeErase1279(BfmeKey1279 &key)
{
	EAStringC &skey = (EAStringC &)key;
	if (skey.IsEmpty())
		return;
	unsigned int id = skey.rva006D3D10();
	if (m_map != 0) {
		void *found = (void *)((const AptNativeHash *)this)->HashFindKey(&skey);
		if (found != 0) {
			((EAStringC *)found)->rva006D3470();
			Rva0070A6D0Release(found);
			return;
		}
	}
	if (id == 0x699) {
		if (skey.rva006D3560(Rva0070B4F0GetString(0x78))) {
			if (m_c != 0) {
				m_c->v1();
				m_c = 0;
			}
		}
	}
	else if (id == 0x6bbd) {
		if (skey.rva006D3560(Rva0070B4F0GetString(0))) {
			if (m_8 != 0) {
				m_8->v1();
				m_8 = 0;
			}
		}
	}
}
