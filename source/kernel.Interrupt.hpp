/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_INTERRUPT_HPP_
#define KERNEL_INTERRUPT_HPP_

#include "kernel.Object.hpp"
#include "api.Task.hpp"
#include "api.Interrupt.hpp"

namespace kernel
{
    class Interrupt : public ::kernel::Object, public ::api::Interrupt
    {
        typedef ::kernel::Object Parent;
  
    public:
        
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         */     
        Interrupt(::api::Task& handler, int32 source);
        
        /** 
         * Destructor.
         */
        virtual ~Interrupt();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;
        
        /**
         * Jumps to interrupt hardware vector.
         */      
        virtual void jump();    
        
        /**
         * Clears an interrupt status of this source.
         */     
        virtual void clear();
        
        /**
         * Sets an interrupt status of this source.
         */    
        virtual void set();
        
        /**
         * Locks this interrupt source.
         *
         * This method cannot definitely get state status bit of this vector before 
         * the method was called. That is why it returns true if the vector interrupting 
         * has been disabled successfully. Therefore, it does not work exactly how 
         * EOOS API demands, and you must not use the method in nested loops.
         *
         * For solving the problem, probably we should write a interrupt module of 
         * each CPU that is ported to the OS.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        virtual bool disable();
        
        /**
         * Unlocks this interrupt source.
         *
         * @param status returned status by lock method.
         */
        virtual void enable(bool status);
        
        /**
         * Disables all maskable interrupts.
         *
         * @return global interrupts enable bit value before method was called.
         */
        static bool disableAll();
        
        /**
         * Enables all maskable interrupts.
         *
         * The true passed argument directly turns all maskable interrupts on, 
         * and the false does nothing, the interrupts stay in the current state.     
         *
         * @param status the returned status by disable method.
         */
        static void enableAll(bool status=true);        
        
        /**
         * Initialization.
         *
         * @return true if no errors.
         */
        static bool initialize();
        
        /**
         * Deinitialization.
         */
        static void deinitialize();
  
    private:
      
        /**
         * Constructor.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.   
         * @param source  available interrupt source.     
         * @return true if object has been constructed successfully.     
         */    
        bool construct(::api::Task* handler, int32 source);
        
        /**
         * Tests if the module has been initialized.
         *
         * @return true if the module has been initialized successfully.
         */    
        static bool isInitialized();
        
        /** 
         * Interrupt hanlder vector number 0.
         */
        static void handler00();
        
        /** 
         * Interrupt hanlder vector number 1.
         */
        static void handler01();
        
        /** 
         * Interrupt hanlder vector number 2.
         */
        static void handler02();
        
        /** 
         * Interrupt hanlder vector number 3.
         */        
        static void handler03();           
        
        /** 
         * Interrupt hanlder vector number 4.
         */        
        static void handler04();
        
        /** 
         * Interrupt hanlder vector number 5.
         */       
        static void handler05();
        
        /** 
         * Interrupt hanlder vector number 6.
         */
        static void handler06();
        
        /** 
         * Interrupt hanlder vector number 7.
         */        
        static void handler07();
        
        /** 
         * Interrupt hanlder vector number 8.
         */        
        static void handler08();
        
        /** 
         * Interrupt hanlder vector number 9.
         */        
        static void handler09();
        
        /** 
         * Interrupt hanlder vector number 10.
         */        
        static void handler10();
        
        /** 
         * Interrupt hanlder vector number 11.
         */        
        static void handler11();                 
                
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Interrupt(const Interrupt& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Interrupt& operator =(const Interrupt& obj);

        /**
         * The number of interrupt vector methods.
         */        
        static const int32 HANDLERS_NUMBER = 12;        
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x98753af7;    
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;

        /**
         * The module initialization stage (no boot).
         */
        static int32 stage_;

        /**
         * Interrupt handlers (no boot).
         */        
        static ::api::Task* handler_[HANDLERS_NUMBER];
        
        /**
         * An interrupt resource is called jump method (no boot).
         */        
        static bool isJumping_[HANDLERS_NUMBER];        
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;    
        
        /**
         * The porting OS resource.
         */
        uint32 res_;         

        /**
         * An index of this resource in interrupt handlers table.
         */        
        int32 index_;
  
    };
}
#endif // KERNEL_INTERRUPT_HPP_
