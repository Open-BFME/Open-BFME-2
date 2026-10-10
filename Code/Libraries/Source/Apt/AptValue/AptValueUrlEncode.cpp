// cl: /O2 /MD /EHsc
// Original EA AptValue.cpp230e7c503b5dbf7e urlEncode source1631..1677.
// Native373B6DDDE0 and paired unnamed WB176E6C0 independently agree on
// flags4, hash slot3, hash-key/value offsets0/4 and two scoped EAStringC
// lifetimes. Preserve the existing neutral owner name; urlEncode is the
// original EA donor method name, not a name established by WB.
// Partial caller views only: no AptValue or hash object is constructed.
// The default string ctor is the established real16B empty-root/refcount
// body, ICF-folded with rowed clear6D2F90 using the actual singleton owner.
class AptNativeHash;
class EAStringC {public:class StringDataC {public:unsigned short m_uRefCount,m_uSize,m_uMaxSize,m_uHash;};private:StringDataC *data;public:EAStringC();EAStringC(const EAStringC &);~EAStringC();bool rva006D3560(const EAStringC *)const;EAStringC &Rva006D4F00Append(const EAStringC &);EAStringC &Rva006D50A0Append(const char *);bool rva006D5DA0(const char *);};
extern EAStringC::StringDataC g_eaEmptyStringData;
__declspec(noinline) inline EAStringC::EAStringC(){data=&g_eaEmptyStringData;++data->m_uRefCount;}

class AptValue {unsigned int flags;public:virtual void slot0();virtual void slot1();virtual void slot2();virtual AptNativeHash *GetNativeHashVirtual();bool getIsDefined()const{return (flags>>4)&1;}void toString(EAStringC &)const;EAStringC rva006ddde0();};
struct AptHashItem {EAStringC key;AptValue *value;};
class AsciiString;
class AptNativeHash {public:struct Entry;AsciiString *rva0070AA40();Entry *rva0070AAA0(Entry *);};
EAStringC *Rva0070B4F0GetString(int);
EAStringC AptValue::rva006ddde0()
{
 EAStringC properties;
 if(!getIsDefined())return properties;
 AptNativeHash *hash=GetNativeHashVirtual();
 if(!hash)return properties;
 EAStringC valueBuf;
 for(AptHashItem *item=reinterpret_cast<AptHashItem *>(hash->rva0070AA40());item;item=reinterpret_cast<AptHashItem *>(hash->rva0070AAA0(reinterpret_cast<AptNativeHash::Entry *>(item)))) {
  if(item->key.rva006D3560(Rva0070B4F0GetString(0))||item->key.rva006D3560(Rva0070B4F0GetString(0x78)))continue;
  item->value->toString(valueBuf);
  properties.Rva006D4F00Append(item->key);
  properties.Rva006D50A0Append("=");
  properties.Rva006D4F00Append(valueBuf);
  properties.Rva006D50A0Append("&");
 }
 properties.rva006D5DA0("&");
 return properties;
}
