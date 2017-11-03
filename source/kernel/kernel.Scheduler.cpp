/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "os.h"
#include "kernel.Scheduler.hpp" 
#include "kernel.SchedulerThread.hpp" 
#include "kernel.Kernel.hpp"
#include "kernel.Interrupt.hpp"

namespace kernel
{
    /** 
     * Constructor.
     */
    Scheduler::Scheduler() : Parent(),
        isConstructed_ (getConstruct()),
        globalThread_  (),
        list_          (NULL){
        setConstruct( construct() );
    }
  
    /** 
     * Destructor.
     */
    Scheduler::~Scheduler()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Scheduler::isConstructed() const
    {
        return isConstructed_;
    }
    
    /**
     * Creates a new thread.
     *
     * @param task an user task which main method will be invoked when created thread is started.
     * @return a new thread.
     */
    ::api::Thread* Scheduler::createThread(::api::Task& task)
    {
        if( not isConstructed_ ) return NULL;
        SchedulerThread* thread = new SchedulerThread(task, this);
        if(thread == NULL) return NULL; 
        if(thread->isConstructed()) return thread;  
        delete thread;
        return NULL;
    }
    
    /**
     * Returns currently executing thread.
     *
     * @return executing thread.
     */
    ::api::Thread& Scheduler::getCurrentThread()
    {
        ::api::Runtime& kernel = Kernel::getKernel().getRuntime();
        if( not isConstructed_ ) kernel.terminate(-1);
        bool is = Interrupt::disableAll();
        ::api::Thread* thread = NULL;
        int64 id = static_cast<int64>( prc_id() );
        int32 length = list_.getLength();
        for(int32 i=0; i<length; i++)
        {
            thread = list_.get(i);
            if(thread == NULL) break;
            if(thread->getId() == id) break;
        }
        if(thread == NULL) kernel.terminate(-1);
        Interrupt::enableAll(is);
        return *thread;
    }
    
    /**
     * Yields to next thread.
     */
    void Scheduler::yield()
    {
        if( not isConstructed_ ) return;
        prc_yield();
    }
    
    /** 
     * Returns the toggle interface for controlling global thread switching.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Scheduler::toggle()
    {
        return globalThread_;
    }    

    /** 
     * Constructor.
     *
     * When first scheduler timer interrupt is occurred, 
     * default registers of parent interrupt class will be used
     * for storing the operating system context to it.
     *
     * @return true if object has been constructed successfully.
     */
    bool Scheduler::construct()
    {
        if( not isConstructed() ) return false;
        if( not globalThread_.isConstructed() ) return false;
        if( not list_.isConstructed() ) return false;        
        return true;      
    }
    
    /**
     * Adds a thread to execution list
     *
     * @return true if thread has been added successfully.
     */
    bool Scheduler::addThread(SchedulerThread* thread)
    {
        if( not isConstructed_ ) return false;
        bool is = Interrupt::disableAll();
        bool res = list_.add(thread);
        Interrupt::enableAll(is);
        return res;
    }    
    
    /**
     * Removes the first occurrence of the specified thread.
     *
     * @param thread removing thread.
     */
    void Scheduler::removeThread(SchedulerThread* thread)
    {
        if( not isConstructed_ ) return;
        bool is = Interrupt::disableAll();
        list_.removeElement(thread);
        Interrupt::enableAll(is);
    }    
}
    
