/**
 * Thread class of this scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SCHEDULER_THREAD_HPP_
#define KERNEL_SCHEDULER_THREAD_HPP_

#include "os.h"
#include "kernel.Object.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "kernel.Semaphore.hpp"
#include "kernel.Interrupt.hpp"

namespace kernel
{      
    class SchedulerThread : public ::kernel::Object, public ::api::Thread
    {
        typedef ::kernel::Object Parent;
    
    public:
    
        /** 
         * Constructor of not constructed object.
         *
         * @param task a task interface whose main method is invoked when this thread is started.         
         */
        SchedulerThread(::api::Task& task, Scheduler* scheduler) : Parent(),
            isConstructed_ (getConstruct()),
            start_         (0),
            task_          (&task),
            scheduler_     (scheduler),            
            id_            (-1),
            res_           (-1),
            status_        (NEW),
            this_          (this){
            setConstruct( construct() );
        }    
        
        /** 
         * Destructor.
         */
        virtual ~SchedulerThread()
        {       
            scheduler_->removeThread(this);
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
         * Causes this thread to begin execution.
         */
        virtual void start()
        {
            if( not isConstructed_ ) return;
            if( status_ != NEW ) return;
            bool is = Interrupt::disableAll();
            scheduler_->addThread(this);
            status_ = RUNNABLE;                     
            Interrupt::enableAll(is);            
            start_.release();
        }       
        
        /**
         * Waits for this thread to die.
         */  
        virtual void join()
        {
            if( not isConstructed_ ) return;             
            prc_join(res_);
        }
        
        /**
         * Causes this thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual void sleep(int64 millis, int32 nanos)
        {
            if( not isConstructed_ ) return;
            if(millis == 0)
            {
                int32 micros = nanos / 1000;            
                // The sleep_u OS call does not cause switching threads
                // and uses all system time quant. Therefore, use the call
                // only for nanosecond requests
                sleep_u( static_cast<uint32>(micros) );
            }
            else
            {
                sleep_m( static_cast<uint32>(millis) );
            }
        }
        
        /**
         * Blocks this thread on given resource and yields the task.
         *
         * @param res a resource.
         */  
        virtual void block(::api::Resource& res)
        {
            if( not isConstructed_ ) return;
        }        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier, or -1 if an error has been occurred.
         */
        virtual int64 getId() const
        {
            return id_;
        }
        
        /**
         * Returns this thread priority.
         *
         * @return priority value, or -1 if an error has been occurred.
         */  
        virtual int32 getPriority() const
        {
            return NORM_PRIORITY;
        }
        
        /**
         * Sets this thread priority.
         *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
         */  
        virtual void setPriority(int32 priority)
        {     
        }

        /**
         * Returns a status of this thread.
         *
         * @return this thread status.
         */  
        virtual Status getStatus() const
        {
            return isConstructed_ ? status_ : DEAD;
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
            if( not task_->isConstructed() ) return false;
            if( not start_.isConstructed() ) return false;
            // Create new thread of the porting OS
            s_prc_attr attr;
            // Set size of thread stack
            attr.stack = task_->getStackSize();
            // Set default OS heap
            attr.heap = 0;
            // Set default priority for this thread
            attr.priority = 0;
            // Set default address of .bss section
            attr.bss = 0;
            // Set no exit vector
            attr.exit_vector = NULL;
            res_ = prc_create(&mainThread, &this_, sizeof(SchedulerThread*), &attr);            
            id_ = static_cast<int64>(res_);
            return id_ >= 0 ? true : false;
        }
        
        /**
         * Runs a method of Runnable interface start vector.
         */  
        void run()
        {
            // Wait for calling start method
            start_.acquire();
            // Call user main method
            task_->main();
            // Kill the thread
            bool is = Interrupt::disableAll();
            status_ = DEAD;            
            scheduler_->removeThread(this);
            Interrupt::enableAll(is);        
        }        
        
        /**
         * Runs a method of Runnable interface start vector.
         */         
        static int mainThread(void* argument)
        {
            if(argument == NULL) return -1;
            SchedulerThread* thread = *reinterpret_cast<SchedulerThread**>(argument);
            if(thread == NULL || not thread->isConstructed() ) return -1;
            // Invoke the member function through the pointer
            thread->run();            
            return 0;
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        SchedulerThread(const SchedulerThread& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        SchedulerThread& operator =(const SchedulerThread& obj); 

        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;

        /**
         * The semaphore gives the started thread main method to start user task main method.
         */        
        Semaphore start_;
        
        /**
         * User executing runnable interface.
         */        
        ::api::Task* task_;

        /**
         * The scheduler resource.
         */
        Scheduler* scheduler_;        
        
        /**
         * Current identifier.
         */        
        int64 id_;        
        
        /**
         * Current identifier is a resource of porting OS process.
         */        
        int32 res_;

        /**
         * Current status.
         */        
        Status status_; 

        /**
         * This class pointer.
         */
        SchedulerThread* this_;       
        
    };
}
#endif // KERNEL_SCHEDULER_THREAD_HPP_
