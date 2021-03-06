/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      Generic implementation of the Oberserver pattern.
 *
 */

#include "sf_observer.h"
#include "sf_subject.h"
#include "sf_event.h"

namespace sf {

    Subject::Subject()
    {

    }

    Subject::~Subject()
    {

    }

    void Subject::Notify (  Observer *observer, Event *event) {
        observer->Update ( event );
    }
}
