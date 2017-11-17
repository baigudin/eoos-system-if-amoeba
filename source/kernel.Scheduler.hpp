/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SCHEDULER_HPP_
#define KERNEL_SCHEDULER_HPP_

#include "kernel.Object.hpp"
#include "api.Scheduler.hpp"
#include "kernel.GlobalThread.hpp"
#include "library.LinkedList.hpp"

namespace kernel
{
    class SchedulerThread;

    class Scheduler : public ::kernel::Object, public ::api::Scheduler
    {
        typedef ::kernel::Object Parent;   
  
    public:
  
        /** 
         * Constructor.
         */
        Scheduler();
      
        /** 
         * Destructor.
         */
        virtual ~Scheduler();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;
      
        /**
         * Creates a new thread.
         *
         * @param task an user task which main method will be invoked when created thread is started.
         * @return a new thread.
         */
        virtual ::api::Thread* createThread(::api::Task& task);
        
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        virtual ::api::Thread& getCurrentThread();
        
        /**
         * Yields to next thread.
         */
        virtual void yield();
        
        /** 
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */ 
        virtual ::api::Toggle& toggle();
        
        /**
         * Adds a thread to execution list
         *
         * @return true if thread has been added successfully.
         */
        bool addThread(SchedulerThread* thread);
        
        /**
         * Removes the first occurrence of the specified thread.
         *
         * @param thread removing thread.
         */
        void removeThread(SchedulerThread* thread);                 
  
    private:
  
        /** 
         * Constructor.
         *
         * When first scheduler timer interrupt is occurred, 
         * default registers of parent interrupt class will be used
         * for storing the operating system context to it.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct();
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Scheduler(const Scheduler& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Scheduler& operator =(const Scheduler& obj);
        
        /** 
         * The root object constructed flag.
         */
        const bool& isConstructed_;        

        /** 
         * Global thread switching controller.
         */        
        GlobalThread globalThread_;
        
        /**
         * The tasks list.
         */
        ::library::LinkedList< SchedulerThread* > list_;        
  
    };
}
#endif // KERNEL_SCHEDULER_HPP_
