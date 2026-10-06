// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva001334A0Element { unsigned words[16];Rva001334A0Element& operator=(const Rva001334A0Element&b){words[0]=b.words[0];words[1]=b.words[1];words[2]=b.words[2];words[3]=b.words[3];words[4]=b.words[4];words[5]=b.words[5];words[6]=b.words[6];words[7]=b.words[7];words[8]=b.words[8];words[9]=b.words[9];words[10]=b.words[10];words[11]=b.words[11];words[12]=b.words[12];words[13]=b.words[13];words[14]=b.words[14];words[15]=b.words[15];return *this;}bool operator<(const Rva001334A0Element&)const;bool operator==(const Rva001334A0Element&)const; };

Rva001334A0Element& (Rva001334A0Element::*Rva001334A0Assign)(const Rva001334A0Element&)=&Rva001334A0Element::operator=;
