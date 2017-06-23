#ifndef _SF_EVENT_H_
#define _SF_EVENT_H_

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
 */

#include <string>

namespace sf
{

class Event
{
public:
    Event ( int identifier, void *content, size_t content_size );
    ~Event();

    virtual int GetIdentifier ( );
    virtual size_t GetDetails ( void **content );

private:
    int identifier;
    void *content;
    size_t content_size;
};

}

#endif // _SF_EVENT_H_
