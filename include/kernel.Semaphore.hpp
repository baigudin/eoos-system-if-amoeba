/**
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SEMAPHORE_HPP_
#define KERNEL_SEMAPHORE_HPP_

#include "os.h"
#include "Object.hpp"
#include "api.Semaphore.hpp"
#include "kernel.Interrupt.hpp"

namespace kernel
{
    class Semaphore : public ::Object<>, public ::api::Semaphore
    {
        typedef ::Object<> Parent;

    public:

        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.   
         */      
        Semaphore(int32 permits) : Parent(),
            isConstructed_ (getConstruct()),
            res_           (RES_VOID),
            isFair_        (false){
            setConstruct( construct(permits) );  
        }   

        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         */      
        Semaphore(int32 permits, bool isFair) : Parent(),
            isConstructed_ (getConstruct()),  
            res_           (RES_VOID),
            isFair_        (isFair){
            setConstruct( construct(permits) );  
        }        

        /** 
         * Destructor.
         */
        virtual ~Semaphore()
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
         * Acquires one permit from this semaphore.
         *
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire()
        {
            if( not isConstructed_ ) return false;        
            return sem_lock(res_, SEM_INFINITY) == SEM_OK ? true : false;
        }        

        /**
         * Acquires the given number of permits from this semaphore.
         *
         * @param permits the number of permits to acquire.
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire(int32 permits)
        {
            if( not isConstructed_ ) return false;
            uint32 error = SEM_OK;
            bool is = Interrupt::disableAll();
            for(int32 i=0; i<permits; i++)
            {
                error |= sem_lock(res_, SEM_INFINITY);
            }
            Interrupt::enableAll(is);
            return error == SEM_OK ? true : false;
        }

        /**
         * Releases one permit.
         */
        virtual void release()
        {
            if( not isConstructed_ ) return;        
            sem_unlock(res_);
        } 

        /**
         * Releases the given number of permits.
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits)
        {
            if( not isConstructed_ ) return;
            bool is = Interrupt::disableAll();
            for(int32 i=0; i<permits; i++)
            {
                sem_unlock(res_);
            }
            Interrupt::enableAll(is);
        }         

        /**
         * Tests if this semaphore is fair.
         *
         * @return true if this semaphore has fairness set true.
         */  
        virtual bool isFair() const
        {
            return isFair_;
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
         * @param permits the initial number of permits available.            
         * @return true if object has been constructed successfully.     
         */    
        bool construct(int32 permits)
        {
            if( not isConstructed_ ) return false;
            res_ = sem_alloc(permits, NULL);
            return res_ == RES_VOID ? false : true;
        }          

        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Semaphore(const Semaphore& obj);     

        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Semaphore& operator =(const Semaphore& obj);     

        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;

        /**
         * The porting OS resource.
         */
        uint32 res_;

        /**
         * Semaphore fair flag.
         */    
        bool isFair_;

    };  
}
#endif // KERNEL_SEMAPHORE_HPP_
