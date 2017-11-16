/** 
 * System class of the operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_KERNEL_HPP_
#define KERNEL_KERNEL_HPP_

#include "api.Kernel.hpp"

namespace kernel
{
    class Kernel
    {
      
    public:
      
        /** 
         * Returns the kernel factory.
         *
         * @return the kernel factory.
         */      
        static ::api::Kernel& call();

    };
}
#endif // KERNEL_KERNEL_HPP_
