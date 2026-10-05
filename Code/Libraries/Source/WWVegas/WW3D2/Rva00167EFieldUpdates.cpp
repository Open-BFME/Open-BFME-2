// cl: /O1 /arch:SSE /MD
struct Rva00167EWords { unsigned a,b,c; 
// ?Rva00167EWords::operator= present-unmatched
Rva00167EWords&operator=(const Rva00167EWords&x){a=x.a;b=x.b;c=x.c;return *this;} };
class Rva00167EFields {
 char head[0x12]; unsigned char flags;
 char gap[0xEC-0x13]; float bound;
 Rva00167EWords words;
 public: void setBound(float); void setWords(const Rva00167EWords&);
};
void Rva00167EFields::setBound(float n) {
 float value=n>0.0f ? n:0.0f;
 flags &= 0xFD;
 bound=value;
}
void Rva00167EFields::setWords(const Rva00167EWords&x) {words=x;}

// Native 00167ED8 ret4: COMISS input against zero, ordered-positive
// values pass through, otherwise +0; clear bit1 of byte+12 and store+EC.
// Native 00167EF8 ret4: copy three raw 32-bit words to +F0/+F4/+F8.
// Only the storage widths/offsets and first function's float comparison
// are established; no application class or coordinate identity inferred.
