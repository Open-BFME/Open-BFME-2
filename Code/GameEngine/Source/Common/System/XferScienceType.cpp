// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native [0x00306232,0x003062FE), 204 bytes, cdecl, returns the Xfer pointer.
// "ScienceType" at 0x00C07D14, the four-byte enum, -1 invalid value,
// ScienceStore global at 0x00DFE0E0 and the virtual slots are retail facts.
// Saving writes the name returned by the 51-byte 0x001FF5F2 provider;
// loading resolves it through 0x001FF725 and rejects an unknown science.
// Both providers already byte-verify, including their hidden-result/ret8 ABI.
// The receiver view declares no ScienceStore fields. Its getter uses an
// address-derived spelling because its original C++ signature is unproven.
// Semantic guide: Open-BFME-1 968ca36c3265 GeneralsMD/Common/System/Xfer.cpp,
// Xfer::xferScienceType. Target uses free cdecl ABI, light-CRC enum dispatch,
// branch-local strings and XferException(0,0), instead of the donor's method.
// The original target function spelling remains unknown.
#include "ascii_string.h"

enum ScienceType { SCIENCE_0 = 0 };
class Xfer {
public:
 virtual ~Xfer();
 virtual bool IsLoading() const;
 virtual bool IsStoring() const;
 virtual bool IsCRC() const;
 virtual bool IsLightCRC() const;
 virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(); virtual void slot09(); virtual void slot10();
 virtual void slot11(); virtual void slot12(); virtual void slot13();
 virtual void slot14(); virtual void slot15(); virtual void slot16();
 virtual void slot17(); virtual void slot18(); virtual void slot19();
 virtual void slot20(); virtual void slot21(); virtual void slot22();
 virtual void slot23(); virtual void slot24(); virtual void slot25();
 virtual void slot26();
 virtual Xfer &xferAsciiString(AsciiString &value);
 virtual void slot28(); virtual void slot29(); virtual void slot30();
 virtual void slot31(); virtual void slot32(); virtual void slot33();
 virtual void slot34(); virtual void slot35(); virtual void slot36();
 virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
};
class ScienceStore {
public:
 AsciiString rva001FF5F2(ScienceType science) const;
 ScienceType getScienceFromInternalName(const AsciiString &name) const;
};
extern ScienceStore *TheScienceStore;
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

Xfer *Rva00306232XferScience(Xfer *xfer, ScienceType *science)
{
 if (xfer->IsLightCRC()) {
  xfer->XferEnum("ScienceType", science, 4);
 } else if (xfer->IsStoring()) {
  AsciiString scienceName = TheScienceStore->rva001FF5F2(*science);
  xfer->xferAsciiString(scienceName);
 } else {
  AsciiString scienceName;
  xfer->xferAsciiString(scienceName);
  *science = TheScienceStore->getScienceFromInternalName(scienceName);
  if ((int)*science == -1)
   throw XferException(0, 0);
 }
 return xfer;
}
