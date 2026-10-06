// cl: /MD
// Target date setters pass local/UTC clocks at date+20/+40 and offset+60.
// Copies calendar fields, adjusts hours/date, then copies sub-hour fields.
// Preserve the retail negative-hour expression 24-offset and its single-day
// rollover behavior. Day(+0C) remains untouched. Hundredths is the donor
// field name; this routine does not establish the sub-second unit itself.
// Evidence: reverse/godfather_disk_evidence.json, apt_date_clock.
struct AptSysClock {
    int Second,Minute,Hour,Day,Date,Month,Year,Hundredths;
};
class AptDate { public: int dateGetNumDaysInMonth(int month,int year); void setDates(AptSysClock *,AptSysClock *,int); };
void AptDate::setDates(AptSysClock *source,AptSysClock *destination,int offset)
{
    destination->Year=source->Year;
    destination->Month=source->Month;
    destination->Date=source->Date;
    destination->Hour=source->Hour-offset;
    if(source->Hour-offset>23) {
        destination->Hour%=24;
        int daysInMonth=dateGetNumDaysInMonth(destination->Month,destination->Year);
        if(++destination->Date>daysInMonth) {
            destination->Date=1;
            if(++destination->Month>11) {
                destination->Month=0;
                ++destination->Year;
            }
        }
    } else if(source->Hour-offset<0) {
        destination->Hour=24-offset;
        if(--destination->Date<1) {
            if(--destination->Month<0) {
                destination->Month=11;
                --destination->Year;
            }
            destination->Date=dateGetNumDaysInMonth(destination->Month,destination->Year);
        }
    }
    destination->Minute=source->Minute;
    destination->Second=source->Second;
    destination->Hundredths=source->Hundredths;
}
