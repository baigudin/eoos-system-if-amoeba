/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "os.h" 
#include "kernel.Interrupt.hpp"
#include "kernel.Kernel.hpp"
 
namespace kernel
{
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     */
    Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
        isConstructed_ (getConstruct()),
        index_         (-1){
        setConstruct( construct(&handler, source) );
    }
    
    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
        bool is = disableAll();      
        int_free(res_);
        res_ = RES_VOID;
        handler_[index_] = NULL;
        index_ = NULL;
        enableAll(is);    
    }
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     * @return true if object has been constructed successfully.
     */
    bool Interrupt::construct(::api::Task* handler, int32 source)
    {
        if( not isConstructed_ ) return false;    
        if( not isInitialized() ) return false;            
        bool ret = false;        
        bool is = disableAll();
        do
        {      
            void (*func)() = NULL;        
            for(int32 i=0; i<HANDLERS_NUMBER; i++)
            {
              if(handler_[i] != NULL) continue;
              switch(i)
              {
                case  0: func = handler00; break;
                case  1: func = handler01; break;
                case  2: func = handler02; break;
                case  3: func = handler03; break;                              
                case  4: func = handler04; break;
                case  5: func = handler05; break;
                case  6: func = handler06; break;
                case  7: func = handler07; break;
                case  8: func = handler08; break;
                case  9: func = handler09; break;
                case 10: func = handler10; break;
                case 11: func = handler11; break;
                default: continue;
              }
              index_ = i;
              break;
            }
            if(func == NULL) break;
            res_ = int_alloc(source, func);
            if(res_ == RES_VOID) break;
            // Do this for being sure that int_alloc has not unlock alloced vector
            if(int_lock(res_) != OSE_OK) break;  
            handler_[index_] = handler;
            ret = true;
        }
        while(false);
        enableAll(is);       
        return ret;
    }
  
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Interrupt::isConstructed() const
    {
        return isConstructed_;
    }
    
    /**
     * Jumps to interrupt HW vector.
     */  
    void Interrupt::jump()
    {
        if( not isConstructed_ ) return;
        bool is = disableAll();
        isJumping_[index_] = true;
        set();
        enableAll(is);
        while( not isJumping_ );
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
        if( not isConstructed_ ) return;
        int_clear(res_);
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
        if( not isConstructed_ ) return;
        int_set(res_);
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
        if( not isConstructed_ ) return false;
        int32 error = int_lock(res_);
        return error == OSE_OK ? true : false;
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
        if( not isConstructed_ ) return;
        if(status == false) return;
        int_unlock(res_);
    }
    
    /**
     * Disables all maskable interrupts.
     *
     * @return global interrupts enable bit value before method was called.
     */
    bool Interrupt::disableAll()
    {
        return int_disable() == 0 ? false : true;
    }
    
    /**
     * Enables all maskable interrupts.
     *
     * The true passed argument directly turns all maskable interrupts on, 
     * and the false does nothing, the interrupts stay in the current state.     
     *
     * @param status the returned status by disable method.
     */
    void Interrupt::enableAll(bool status)
    {
        int_enable(status == true ? 1 : 0);
    }    
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Interrupt::initialize()
    {
        isInitialized_ = 0;
        stage_ = -1;
        for(int32 i=0; i<HANDLERS_NUMBER; i++)
        {
            handler_[i] = NULL;
            isJumping_[i] = false;
        }        
        isInitialized_ = IS_INITIALIZED;
        return true; 
    }
    
    /**
     * Deinitialization.
     */
    void Interrupt::deinitialize()
    {
        isInitialized_ = 0;   
    }
    
    /**
     * Tests if the module has been initialized.
     *
     * @return true if the module has been initialized successfully.
     */    
    bool Interrupt::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }
    
    /** 
     * Interrupt hanlder vector number 0.
     */
    void Interrupt::handler00()
    {
        const int32 METHOD_NUMBER = 0;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }    
    
    /** 
     * Interrupt hanlder vector number 1.
     */
    void Interrupt::handler01()
    {
        const int32 METHOD_NUMBER = 1;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }    
    
    /** 
     * Interrupt hanlder vector number 2.
     */
    void Interrupt::handler02()
    {
        const int32 METHOD_NUMBER = 2;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }    
    
    /** 
     * Interrupt hanlder vector number 3.
     */        
    void Interrupt::handler03()
    {
        const int32 METHOD_NUMBER = 3;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }                   
    
    /** 
     * Interrupt hanlder vector number 4.
     */        
    void Interrupt::handler04()
    {
        const int32 METHOD_NUMBER = 4;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 5.
     */       
    void Interrupt::handler05()
    {
        const int32 METHOD_NUMBER = 5;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 6.
     */
    void Interrupt::handler06()
    {
        const int32 METHOD_NUMBER = 6;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 7.
     */        
    void Interrupt::handler07()
    {
        const int32 METHOD_NUMBER = 7;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 8.
     */        
    void Interrupt::handler08()
    {
        const int32 METHOD_NUMBER = 8;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 9.
     */        
    void Interrupt::handler09()
    {
        const int32 METHOD_NUMBER = 9;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 10.
     */        
    void Interrupt::handler10()
    {
        const int32 METHOD_NUMBER = 10;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /** 
     * Interrupt hanlder vector number 11.
     */        
    void Interrupt::handler11()
    {
        const int32 METHOD_NUMBER = 11;
        if( handler_[METHOD_NUMBER] == NULL ) return;
        isJumping_[METHOD_NUMBER] = false;
        handler_[METHOD_NUMBER]->main();
    }        
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 Interrupt::isInitialized_;
    
    /**
     * The module initialization stage (no boot).
     */
    int32 Interrupt::stage_;          
    
    /**
     * Interrupt handlers (no boot).
     */        
    ::api::Task* Interrupt::handler_[Interrupt::HANDLERS_NUMBER];    
    
    /**
     * An interrupt resource is called jump method (no boot).
     */            
    bool Interrupt::isJumping_[HANDLERS_NUMBER];        
}
