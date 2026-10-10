// ?rva0043DC40@AptMpGameSetup@@QAEXH@Z
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc
// Native43DC40..43DC75 (53B); current callback owner AptMpGameSetup.
// Target and current home agree on dirty2BC and sort3AC/previous3B0.
// These are the witnessed fields only; full private class layout is unknown.
class AptMpGameSetup { public:void rva0043DC40(int);char pad[0x2bc];bool dirty;char gap[0x3ac-0x2bd];int column,previous;};
void AptMpGameSetup::rva0043DC40(int selected){int old=column;int next=selected+1;if(old==selected)column=next;else {if(old!=next)previous=old;column=selected;}dirty=true;}
