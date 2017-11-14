/** 
 * Kernel class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Kernel.hpp"
#include "kernel.Main.hpp"

namespace kernel
{
    /** 
     * Returns a kernel factory.
     *
     * @return a kernel factory.
     */      
    ::api::Kernel& Kernel::call()
    {
        return Main::getKernel();
    } 
}
