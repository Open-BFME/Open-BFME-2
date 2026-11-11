// AptFileTransferPopup: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTFILETRANSFERPOPUP_H
#define CANONICAL_APTFILETRANSFERPOPUP_H

class AsciiString;
class UnicodeString;

class AptFileTransferPopup
{
public:
	void ProcessProgress(int player, int percent, UnicodeString text);
	void rva005830AE(int percentage);
	void rva00583202(int totalSeconds);
	void rva005832D0(const AsciiString &path);
};

#endif // CANONICAL_APTFILETRANSFERPOPUP_H
