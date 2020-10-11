//
//  MyDriver.cpp
//  MyDriver
//
//  Created by Nick on 10/11/20.
//
#include <IOKit/IOLib.h>
#include "MyDriver.hpp"

#define super IOService
OSDefineMetaClassAndStructors(MyDriver, IOService);

bool MyDriver::start(IOService* provider)
{
    bool    success;
    IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    
    success = super::start(provider);
    
    if (success)
        registerService();
    
    return success;
}

void MyDriver::stop(IOService* provider)
{
    IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    
    super::stop(provider);
}

bool MyDriver::init(OSDictionary* dictionary)
{
    if (!super::init(dictionary)) {
        return false;
    }

    // This IOLog must follow super::init because getName relies on the superclass initialization.
    IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, dictionary);

    // This is where you could set the initial value of your driver's data members.
    
    return true;
}

void MyDriver::free(void)
{
    IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
    
    super::free();
}
