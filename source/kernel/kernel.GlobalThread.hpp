/** 
 * Global thread switching controller.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_GLOBAL_THREAD_HPP_
#define KERNEL_GLOBAL_THREAD_HPP_
    
#include "os.h"
#include "Object.hpp"
#include "api.Toggle.hpp"

namespace kernel
{
    class GlobalThread : public ::Object<>, public ::api::Toggle
    {
      typedef ::Object<> Parent;
    
    public:
      
        /** 
         * Constructor.
         */
        GlobalThread() : Parent(),
            isConstructed_ (getConstruct()){
        }  
        
        /** 
         * Destructor.
         */                               
        virtual ~GlobalThread()
        {
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
         * Disables all maskable interrupts.
         *
         * @return global interrupt enable bit value before method was called.
         */ 
        virtual bool disable()
        {
            return prc_disable() == 0 ? false : true;
        }        
        
        /** 
         * Enables all maskable interrupts.
         *
         * @param status returned status by disable method.
         */    
        virtual void enable(bool status)
        {
            prc_enable(status == true ? 1 : 0);  
        }        
      
    private:
    
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        GlobalThread(const GlobalThread& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        GlobalThread& operator =(const GlobalThread& obj);    
      
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;       
      
    }; 
}
#endif // KERNEL_GLOBAL_THREAD_HPP_
