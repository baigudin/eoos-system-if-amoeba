/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Interrupt.hpp"
#include "os.h" 

namespace local
{ 
    namespace system
    {
        /**
         * Constructor.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.   
         * @param source  available interrupt source.
         */
        Interrupt::Interrupt(api::Task& handler, int32 source) : Parent(),
            res_   (RES_VOID),
            index_ (-1){
            bool const isConstructed = construct(&handler, source);
            setConstructed( isConstructed );
        }
        
        /**
         * Destructor.
         */
        Interrupt::~Interrupt()
        {
            bool const is = disableAll();
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
        bool Interrupt::construct(api::Task* handler, int32 source)
        {
            if( not Self::isConstructed() ) return false;
            bool ret = false;        
            bool const is = disableAll();
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
            return Parent::isConstructed();
        }
        
        /**
         * Jumps to interrupt HW vector.
         */  
        void Interrupt::jump()
        {
            if( not Self::isConstructed() ) return;
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
            if( not Self::isConstructed() ) return;
            int_clear(res_);
        }
        
        /**
         * Sets an interrupt status of this source.
         */  
        void Interrupt::set()
        {
            if( not Self::isConstructed() ) return;
            int_set(res_);
        }  
        
        /**
         * Locks this interrupt source.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        bool Interrupt::disable()
        {
            if( not Self::isConstructed() ) return false;
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
            if( not Self::isConstructed() ) return;
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
         * Interrupt hanlder vector number 0.
         */
        void Interrupt::handler00()
        {
            int32 const vector = 0;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }    
        
        /** 
         * Interrupt hanlder vector number 1.
         */
        void Interrupt::handler01()
        {
            int32 const vector = 1;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }    
        
        /** 
         * Interrupt hanlder vector number 2.
         */
        void Interrupt::handler02()
        {
            int32 const vector = 2;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }    
        
        /** 
         * Interrupt hanlder vector number 3.
         */        
        void Interrupt::handler03()
        {
            int32 const vector = 3;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }                   
        
        /** 
         * Interrupt hanlder vector number 4.
         */        
        void Interrupt::handler04()
        {
            int32 const vector = 4;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 5.
         */       
        void Interrupt::handler05()
        {
            int32 const vector = 5;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 6.
         */
        void Interrupt::handler06()
        {
            int32 const vector = 6;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 7.
         */        
        void Interrupt::handler07()
        {
            int32 const vector = 7;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 8.
         */        
        void Interrupt::handler08()
        {
            int32 const vector = 8;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 9.
         */        
        void Interrupt::handler09()
        {
            int32 const vector = 9;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 10.
         */        
        void Interrupt::handler10()
        {
            int32 const vector = 10;
            if( handler_[vector] == NULL ) return;
            isJumping_[vector] = false;
            handler_[vector]->start();
        }        
        
        /** 
         * Interrupt hanlder vector number 11.
         */        
        void Interrupt::handler11()
        {
            handler(11);
        }

        /**
         * Interrupt handler.
         */
        void Interrupt::handler(int32 const vector)
        {
            if( handler_[vector] != NULL )
            {
                isJumping_[vector] = false;
                handler_[vector]->start();
            }
        }
        
        /**
         * Interrupt handlers.
         */        
        api::Task* Interrupt::handler_[Interrupt::HANDLERS_NUMBER] = { NULL };
        
        /**
         * An interrupt resource is called jump method.
         */            
        bool Interrupt::isJumping_[HANDLERS_NUMBER] = { false };
    }
}
