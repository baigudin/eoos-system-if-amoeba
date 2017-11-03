/**
 * The resources factory of the operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_RESOURCE_HPP_
#define KERNEL_RESOURCE_HPP_

#include "Object.hpp"
#include "api.Kernel.hpp"
#include "kernel.Runtime.hpp"
#include "kernel.Time.hpp"
#include "kernel.Mutex.hpp"
#include "kernel.Semaphore.hpp"
#include "kernel.Interrupt.hpp"
#include "kernel.Scheduler.hpp"
#include "kernel.GlobalInterrupt.hpp"

namespace kernel
{
    class Resource : public ::Object<>, public ::api::Kernel
    {
        typedef ::Object<> Parent;
      
    public:
    
        /** 
         * Constructor.
         *
         * @param scheduler a kernel scheduler.
         */    
        Resource() : Parent(),
            isConstructed_ (getConstruct()),
            time_          (),
            global_        (),
            runtime_       (),
            scheduler_     (){
            setConstruct( construct() );    
        }        
  
        /** 
         * Destructor.
         */
        virtual ~Resource(){}
        
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
         * Returns a kernel runtime environment.
         *
         * @return a kernel runtime environment.
         */      
        virtual ::api::Runtime& getRuntime()
        {
            return runtime_;
        }
        
        /** 
         * Returns a value of the kernel running time in nanoseconds.
         *
         * @return the running time in nanoseconds.
         */      
        virtual ::api::Value<int64>& getExecutionTime()
        {
            return time_;
        }
        
        /** 
         * Returns a kernel scheduler.
         *
         * @return a kernel scheduler.
         */      
        virtual ::api::Scheduler& getScheduler()
        {
            return scheduler_;
        }
        
        /** 
         * Returns a global interrupt resource.
         *
         * @return a global interrupt resource.
         */      
        virtual ::api::Toggle& getGlobalInterrupt()
        {
            return global_;
        }
        
        /** 
         * Creates new mutex resource.
         *
         * @return new mutex resource, or NULL if error has been occurred.
         */      
        virtual ::api::Mutex* createMutex()
        {
            ::api::Mutex* res = new Mutex();
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL;   
        }
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.   
         * @return new semaphore resource, or NULL if error has been occurred.
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits)
        {
            ::api::Semaphore* res = new Semaphore(permits);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL;   
        }
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         * @return new semaphore resource, or NULL if error has been occurred.         
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits, bool isFair)
        {
            ::api::Semaphore* res = new Semaphore(permits, isFair);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL; 
        }        
        
        /**
         * Creates new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return new interrupt resource.
         */
        virtual ::api::Interrupt* createInterrupt(::api::Task& handler, int32 source)
        {
            ::api::Interrupt* res = new Interrupt(handler, source);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL;       
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
            if( not scheduler_.isConstructed() ) return false;
            if( not time_.isConstructed() ) return false;
            if( not global_.isConstructed() ) return false;            
            if( not runtime_.isConstructed() ) return false;            
            return true;   
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Resource(const Resource& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Resource& operator =(const Resource& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
        
        /**
         * Kernel time.
         */        
        Time time_;

        /**
         * Global interrupt resource.
         */                
        GlobalInterrupt global_;
        
        /**
         * Runtime kernel execution.
         */        
        Runtime runtime_;
        
        /**
         * Kernel scheduler.
         */
        Scheduler scheduler_;        
        
    };
}
#endif // KERNEL_RESOURCE_HPP_
