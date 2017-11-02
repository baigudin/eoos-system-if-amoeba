/** 
 * Hardware global interrupts resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_GLOBAL_INTERRUPT_HPP_
#define KERNEL_GLOBAL_INTERRUPT_HPP_
    
#include "os.h"
#include "Object.hpp"
#include "api.Toggle.hpp"

namespace kernel
{
    class GlobalInterrupt : public ::Object<>, public ::api::Toggle
    {
      typedef ::Object<> Parent;
    
    public:
      
        /** 
         * Constructor.
         */
        GlobalInterrupt() : Parent(),
            isConstructed_ (getConstruct()){
        }  
        
        /** 
         * Destructor.
         */                               
        virtual ~GlobalInterrupt()
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
            return int_disable() == 0 ? false : true;
        }        
        
        /** 
         * Enables all maskable interrupts.
         *
         * @param status returned status by disable method.
         */    
        virtual void enable(bool status)
        {
            int_enable(status == true ? 1 : 0);  
        }        
      
    private:
    
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        GlobalInterrupt(const GlobalInterrupt& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        GlobalInterrupt& operator =(const GlobalInterrupt& obj);    
      
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;       
      
    }; 
}
#endif // KERNEL_GLOBAL_INTERRUPT_HPP_
