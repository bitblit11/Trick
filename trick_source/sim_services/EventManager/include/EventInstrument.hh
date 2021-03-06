#ifndef _EVENTINSTRUMENT_HH_
#define _EVENTINSTRUMENT_HH_

#include <string>
#include "sim_services/EventManager/include/Event.hh"
#include "sim_services/SimObject/include/InstrumentBase.hh"
#include "sim_services/SimObject/include/JobData.hh"

namespace Trick {

/**
  This class encapsulates an event into an instrument class.  Instrument classes
  may be attached to jobs.  When this instrument class is called, the event is
  processed.

  @author Alex Lin, Danny Strauss
*/

class EventInstrument : public Trick::InstrumentBase {

    public:
        /**
         @brief constructor that takes an event and the target job it will be attached
        */
        EventInstrument(Trick::Event * in_event, Trick::JobData * in_target_job) ;

        /**
         @brief call() routine inherited from InstrumentBase.  This class will execute
          the event.
        */
        virtual int call() ;

        /**
         @brief returns the event contained in this instrument.
        */
        Trick::Event * get_event() { return event ; } ;

    protected:

        /**
         @brief the event contained in this instrument.
        */
        Trick::Event * event ;

} ;

}

#endif
