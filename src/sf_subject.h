#ifndef SUBJECT_H
#define SUBJECT_H

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
 * @details    C++ does not allow C++ Member functions as C-Callbacks.
 * However, callback functions are needed by interrupt handlers or
 * event handlers. The problem can be solved by applying the Observer pattern:
 *
 *
 * The "Subject" passes pointers to its static methods as callback functions.
 * Whenever one of those callbacks are called, the "Subject" notifies all
 * attached "Observers".
 *
 * @code
 *                                  +-----------------------------------------+
 *                                  |  Subject                                |
 * +--------------------------+     |                                         |
 * |                          |     +-----------------------------------------+
 * |  Observer                +---<>|                                         |
 * |                          |     | +ObserverCollection                     |
 * +--------------------------+     |                                         |
 * |                          |     +-----------------------------------------+
 * +--------------------------+     |                                         |
 * |                          |     | +Attach ( Observer *observer )          |
 * | +Update ( Event *event ) |     |                                         |
 * |                          |     | +Detach ( Observer *observer )          |
 * +--------------------------+     |                                         |
 *                        /_\       | +Notify ( Event *event, Filter filter ) |
 *                         |        |                                         |
 *                         |        +-----------------------------------------+
 *                         |
 *             +-----------+---------------------+
 *             |                                 |
 *             |                                 |
 *             |                                 |
 * +-----------+--------------+     +------------+-------------+
 * |                          |     |                          |
 * |  ConcreteObserverA       |     |  ConcreteObserverB       |
 * |                          |     |                          |
 * +--------------------------+     +--------------------------+
 * |                          |     |                          |
 * +--------------------------+     +--------------------------+
 * |                          |     |                          |
 * | +Update ( Event *event ) |     | +Update ( Event *event ) |
 * |                          |     |                          |
 * +--------------------------+     +--------------------------+
 * @endcode
 *
 * This is a generic C++ implementation of this pattern.
 */


namespace sf
{

class Observer;
class Event;

class Subject
{

public:
    Subject();
    ~Subject();

            virtual void Attach ( Observer *observer ) = 0;
            virtual void Detach ( Observer *observer ) = 0;
            static void Notify ( Observer *observer, Event *event);
        };

}
#endif // SUBJECT_H
