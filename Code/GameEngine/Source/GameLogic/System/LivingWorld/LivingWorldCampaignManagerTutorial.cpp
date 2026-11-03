// cl: /O1 /arch:SSE /G7 /Oy /MD /EHsc /Ireference/shims/bfme2_ascii /DBFME_ASCII_DTOR_DECL
// Native3B8F20..3B8F76 and WB1032200: tutorial-name static initialized
// once through37BA0 and passed to the campaign-vector name lookup. The
// lookup only reads pointer records and compares strings; no allocation,
// callbacks or throws. Original method name remains unknown.
#include "ascii_string.h"
#include "../../../../Include/Common/LivingWorldCampaignManager.h"
int LivingWorldCampaignManager::rva003B8F20(){
 static AsciiString tutorial("WOTRTutorial");
 return rva003B8E2B(tutorial);
}
