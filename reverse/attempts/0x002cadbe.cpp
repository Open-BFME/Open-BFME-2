// ?Rva002CADBE@WeaponStore@@QBEPBUWeaponTemplate@@H@Z
// partial score=0.85 date=2026-09-26
// cl: /O1 /DNDEBUG /MD /GX-
struct WeaponTemplate { unsigned char m_pad[0xC]; int m_key; };
struct Base12 { unsigned char m_pad[0xC]; };
class WeaponStoreH : public Base12 {
public: const WeaponTemplate *findByKey(int key) const;
private: unsigned char *m_begin; unsigned char *m_end;
};
const WeaponTemplate *WeaponStoreH::findByKey(int key) const
{
	int i = 0;
	if (((m_end - m_begin) >> 2) != 0) {
		WeaponTemplate **slot = (WeaponTemplate **)m_begin;
		WeaponTemplate **base = (WeaponTemplate **)m_begin;
		while (i < (int)((m_end - m_begin) >> 2)) {
			if ((*slot)->m_key == key)
				return base[i];
			++slot;
			++i;
		}
	}
	return 0;
}
