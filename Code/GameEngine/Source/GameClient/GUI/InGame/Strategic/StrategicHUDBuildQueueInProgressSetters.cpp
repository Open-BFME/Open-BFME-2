// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native5F74F7..5F7512 RET4, WB162E2D0, and C797F4 slot7 establish
// this quantity update on InProgressIconSlot. The constructor5F775E and
// rowed setters5F6CA8/5F6D2C/5F6E01/5F6E85 establish the class and fields.
// The retail table has thirteen methods; its first slot is the byte getter
// at4C9990 and its last is the existing progress updater5F7512, not a dtor.
// Keep that order. Names remain neutral where original spellings are unknown.
// Image pointer types follow the rowed setters. Other scalar types are
// structural ABI views, independently justified by the word/byte accesses.
class Image;
namespace StrategicHUD {class BuildQueueDetailsMovieClip {public:class Impl;};}
class StrategicHUD::BuildQueueDetailsMovieClip::Impl {public:class InProgressIconSlot;};
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot {
public:
 virtual unsigned char rva004C9990()const;
 virtual void rva002B230F(void*);
 virtual const Image*rva0030F45F()const;
 virtual void rva005F6CA8(const Image*);
 virtual const Image*rva001DB0A8()const;
 virtual void rva005F6D2C(const Image*);
 virtual int rva001DB09D()const;
 virtual void rva005F74F7(int);
 virtual int rva0057E556()const;
 virtual void DoSetState(int);
 virtual int rva0030D377()const;
 virtual int rva00091A56()const;
 virtual void rva005F7512(int,int);
 void SetQuantityString(int);
private:
 void*listener;const Image*portrait;const Image*typeImage;int quantity,state;
 bool hover;char pad19[3];Impl*owner;int total,remaining;bool turnsHover;
};
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::rva005F74F7(int value){
 if(value!=quantity){SetQuantityString(value);quantity=value;}
}
typedef char InProgressSlotHas44Bytes[sizeof(StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot)==44?1:-1];
