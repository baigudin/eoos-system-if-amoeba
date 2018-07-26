/** 
 * The main entery point.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"

/**
 * Executes a user application main process.
 *
 * @param args - an application arguments.
 */
int os_main(void* const args)
{
    ::local::system::System eoos;
    return eoos.execute();
}
