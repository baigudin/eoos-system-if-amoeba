/** 
 * The configuration of a target processor.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_CONFIGURATION_HPP_
#define KERNEL_CONFIGURATION_HPP_

#include "os.h"
#include "Configuration.hpp"

namespace kernel
{
    struct Configuration : public ::Configuration
    {
        typedef ::Configuration Parent;
    
    public:
    
        /** 
         * Copy constructor.
         *
         * @param obj a source object.
         */    
        Configuration(const ::Configuration& obj) : Parent(obj),
            isAllocated_  (false){
            if(heapAddr == NULL)
            {
                heapAddr = heap_alloc(NULL, heapSize, HEAP_ALIGN_8);        
                isAllocated_ = true;
            }
        }
            
        /** 
         * Destructor.
         */
       ~Configuration()
        {
            if( isAllocated_ )
            {
                heap_free( NULL, heapAddr );
            }
        }
      
    private:
    
        /**
         * The heap has beed allocated.
         */      
        bool isAllocated_;
      
    };
}
#endif // CONFIGURATION_HPP_
