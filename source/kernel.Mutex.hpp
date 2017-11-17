/**
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_MUTEX_HPP_
#define KERNEL_MUTEX_HPP_

#include "os.h"
#include "kernel.Object.hpp"
#include "api.Mutex.hpp"

namespace kernel
{  
    class Mutex : public ::kernel::Object, public ::api::Mutex
    {
        typedef ::kernel::Object Parent;    
  
    public:
  
        /** 
         * Constructor.
         */    
        Mutex() : Parent(),
            isConstructed_ (getConstruct()),
            res_           (RES_VOID){
            setConstruct( construct() );  
        }        
        
        /** 
         * Destructor.
         */      
        virtual ~Mutex()
        {
            if(res_ != RES_VOID) sem_free(res_);
        }        
            
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }        

        
        /**
         * Locks the mutex.
         *
         * @return true if the mutex is lock successfully.
         */      
        virtual bool lock()
        {
            if( not isConstructed_ ) return false;
            return sem_lock(res_, SEM_INFINITY) == SEM_OK ? true : false;        
        }
        
        /**
         * Unlocks the mutex.
         */      
        virtual void unlock()
        {
            if( not isConstructed_ ) return;
            sem_unlock(res_);        
        }
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked()
        {
            if( not isConstructed_ ) return false;
            switch( sem_locked(res_) )
            {
                case SEM_LOCKED   : return true;
                case SEM_UNLOCKED : return false;
                default           : return true;
            }        
        }
  
    private:
  
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            if( not isConstructed_ ) return false;
            res_ = sem_alloc(1, NULL);
            return res_ == RES_VOID ? false : true;        
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Mutex(const Mutex& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Mutex& operator =(const Mutex& obj);      
  
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_; 
        
        /**
         * The porting OS resource.
         */
        uint32 res_;        
  
    };
}
#endif // KERNEL_MUTEX_HPP_
