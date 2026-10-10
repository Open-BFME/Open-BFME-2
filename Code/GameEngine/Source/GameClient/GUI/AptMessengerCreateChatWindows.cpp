// cl: /O1 /MD /EHsc /DNDEBUG
// WB1514DD0 and1515610 name the LAN/online CreateChatWindow factories.
// Retail5AE31F..5AE37F and5AE68F..5AE6EF are each96B RET4; virtual
// pointers8726E0 and8727A0 prove dispatch. The online scanner's105B
// interval includes a separate9B vector-size helper after the return.
// The selector and returned pointer stay opaque: WB names the methods
// but does not establish an original enum or the common return type.
// Each external constructor already has its own verified provider name.
// Only allocation extent36 is needed here; no member layout is invented.
class Rva005D50E3 {
public: Rva005D50E3();
private: unsigned char storage[36];
};
class Rva005D50C4 {
public: Rva005D50C4();
private: unsigned char storage[36];
};
class Rva005D5802 {
public: Rva005D5802();
private: unsigned char storage[36];
};
class Rva005D5828 {
public: Rva005D5828();
private: unsigned char storage[36];
};
class AptMessengerLan {
public: virtual void *CreateChatWindow(int selector);
};
class AptMessengerOnline {
public: virtual void *CreateChatWindow(int selector);
};
void *AptMessengerLan::CreateChatWindow(int selector)
{
 switch(selector) {
 case 0: return new Rva005D50E3;
 case 1: return new Rva005D50C4;
 default: return 0;
 }
}
void *AptMessengerOnline::CreateChatWindow(int selector)
{
 switch(selector) {
 case 1: return new Rva005D5802;
 case 0: return new Rva005D5828;
 default: return 0;
 }
}
