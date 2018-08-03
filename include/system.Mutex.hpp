/**
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MUTEX_HPP_
#define SYSTEM_MUTEX_HPP_

#include "os.h"
#include "system.Object.hpp"
#include "api.Mutex.hpp"

namespace local
{
    namespace system
    {  
        class Mutex : public system::Object, public api::Mutex
        {
                typedef system::Mutex  Self;
                typedef system::Object Parent;
      
        public:
      
            /** 
             * Constructor.
             */    
            Mutex() : Parent(),
                res_ (RES_VOID){
                bool const isConstructed = construct();
                setConstructed( isConstructed );              
            }        
            
            /** 
             * Destructor.
             */      
            virtual ~Mutex()
            {
                if(res_ != RES_VOID) 
                {
                    sem_free(res_);
                }
            }        
                
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */    
            virtual bool isConstructed() const
            {
                return Parent::isConstructed();
            }        
    
            
            /**
             * Locks the mutex.
             *
             * @return true if the mutex is lock successfully.
             */      
            virtual bool lock()
            {
                if( not Self::isConstructed() ) return false;
                return sem_lock(res_, SEM_INFINITY) == SEM_OK ? true : false;        
            }
            
            /**
             * Unlocks the mutex.
             */      
            virtual void unlock()
            {
                if( not Self::isConstructed() ) return;
                sem_unlock(res_);        
            }
            
            /** 
             * Tests if this resource is blocked.
             *
             * @return true if this resource is blocked.
             */ 
            virtual bool isBlocked()const
            {
                if( not Self::isConstructed() ) return false;
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
                if( not Self::isConstructed() ) return false;
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
             * The porting OS resource.
             */
            uint32 res_;        
      
        };
    }
}
#endif // SYSTEM_MUTEX_HPP_
