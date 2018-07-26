/** 
 * The operating system class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"
#include "Program.hpp"
#include "os.h"

namespace local
{
    namespace system
    {
        /** 
         * Calls the operating system kernel.
         *
         * @return the operating system syscall interface.
         */         
        api::System& syscall()
        {
            return System::call();
        }    
    
        /** 
         * Constructor.
         */    
        System::System() : Parent(),
            heap_    (){
            bool const isConstructed = construct();
            setConstructed( isConstructed );
        }
        
        /** 
         * Destructor.
         */
        System::~System()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        bool System::isConstructed() const
        {
            return Parent::isConstructed();
        }
        
        /**
         * Returns the operating system heap memory.
         *
         * @return the heap memory.
         */
        api::Heap& System::getHeap() const
        {
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return heap_;
        }    
        
        /**
         * Returns running time of the operating system in nanoseconds.
         *
         * @return time in nanoseconds.
         */
        int64 System::getTime() const
        {
            int64 const time = static_cast<int64>( time_core_n() );
            return time;
        }
        
        /**
         * Creates a new interrupt resource.
         *
         * @param handler - user class which implements an interrupt handler interface.
         * @param source  - available interrupt source number.
         * @return a new interrupt resource, or NULL if an error has been occurred.
         */
        api::Interrupt* System::createInterrupt(api::Task& handler, int32 source)
        {
            return NULL;
        }

        /**
         * Terminates the operating system execution.
         *
         * @param status a termination status.
         */
        void System::terminate() const
        {
            terminate(ERROR_USER_TERMINATION);
        }
        
        /**
         * Executes the operating system.
         *
         * @return zero, or error code if the execution has been terminated.
         */
        int32 System::execute()
        {
            int32 error;
            if( not Self::isConstructed() )
            {
                error = ERROR_UNDEFINED;
            }
            else
            {
                error = Program::start();
            }
            return error;
        }
    
        /** 
         * Returns the operating system syscall interface.
         *
         * @return the operating system syscall interface.
         */   
        api::System& System::call()
        {
            if(system_ == NULL)
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return *system_;
        }
        
        /**
         * Constructs this object.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool System::construct()
        {
            bool res = Self::isConstructed();
            while(res == true)
            {
                if( system_ != NULL )
                {
                    res = false;
                    continue;
                }
                if( not heap_.isConstructed() )
                {
                    res = false;
                    continue;
                }
                // The construction completed successfully
                system_ = this;
                break;
            }
            return res;            
        }
        
        /**
         * Terminates the operating system execution.
         *
         * @param error a termination status code.
         */
        void System::terminate(Error)
        {
            // ... TODO ...
            volatile bool const isTerminate = true;
            while( isTerminate ){};
        }
        
        /**
         * The operatin system interface.
         */
        api::System* System::system_ = NULL;
    }
}

