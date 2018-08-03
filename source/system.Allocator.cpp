/** 
 * The operating system memory allocator.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Allocator.hpp"
#include "os.h"

namespace local
{
    namespace system
    {
        /**
         * Allocates memory.
         *
         * @param size - number of bytes to allocate.
         * @return allocated memory address or a null pointer.
         */    
        void* Allocator::allocate(size_t const size)
        {
            return heap_alloc(NULL, size, HEAP_ALIGN_8);
        }
        
        /**
         * Frees an allocated memory.
         *
         * @param ptr address of allocated memory block or a null pointer.
         */      
        void Allocator::free(void* const ptr)
        {
            heap_free(NULL, ptr);
        }
        
    }
}
