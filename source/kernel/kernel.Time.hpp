/** 
 * The kernel time resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_TIME_HPP_
#define KERNEL_TIME_HPP_

#include "os.h"
#include "Object.hpp"
#include "api.Value.hpp"
 
namespace kernel
{
    class Time : public ::Object<>, public ::api::Value<int64>
    {
        typedef ::Object<> Parent;
  
    public:
  
        /** 
         * Constructor.
         */     
        Time() : Parent(),
            isConstructed_ (getConstruct()){
            setConstruct( construct() );
        }
      
        /** 
         * Destructor.
         */
        virtual ~Time()
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
         * Sets a value.
         *
         * @param value a value for setting.
         */    
        virtual void setValue(int64 value)
        {
        }
          
        /**
         * Returns set value.
         *
         * @return the set value.
         */      
        virtual int64 getValue() const
        {
            int64 time = static_cast<int64>( time_core_n() );
            return isConstructed_ ? time : 0;        
        }
        
        /**
         * Returns illegal element which will be returned as error value.
         *
         * @return illegal element.
         */
        virtual int64 getIllegal() const
        {
            return ILLEGAL_VALUE;
        }
        
        /**
         * Sets illegal element which will be returned as error value.
         *
         * @param value illegal value.
         */
        virtual void setIllegal(int64 value)
        {
        }
        
        /**
         * Tests if given value is an illegal.
         *
         * @param value testing value.
         * @param true if value is an illegal.
         */
        virtual bool isIllegal(const int64& value) const
        {
            return value == ILLEGAL_VALUE ? true : false;
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
            return true;
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Time(const Time& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Time& operator =(const Time& obj); 
        
        /** 
         * Illegal value of counting time.
         */
        static const int64 ILLEGAL_VALUE = -1;
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;

    };
}
#endif // KERNEL_TIME_HPP_

