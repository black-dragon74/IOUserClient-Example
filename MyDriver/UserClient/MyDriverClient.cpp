//
//  MyDriverClient.cpp
//  MyDriver
//
//  Created by Nick on 10/11/20.
//
#include <IOKit/IOLib.h>

#include "MyDriverClient.hpp"

#define super IOUserClient
OSDefineMetaClassAndStructors(MyDriverClient, IOUserClient);

//MARK:- Dispatch table for user client dispatch
const IOExternalMethodDispatch MyDriverClient::sMethods[kNumberOfMethods] = {
    { //kMethodOpen
        (IOExternalMethodAction) &MyDriverClient::sMethodOpen,      // Method pointer
        0,                                                          // Num of scalar input values
        0,                                                          // Num of struct input values
        0,                                                          // Num of scalar output values
        0                                                           // Num of struct output values
    },
    { //kMethodClose
        (IOExternalMethodAction) &MyDriverClient::sMethodClose,     // Method pointer
        0,                                                          // Num of scalar input values
        0,                                                          // Num of struct input values
        0,                                                          // Num of scalar output values
        0                                                           // Num of struct output values
    },
    { //kMethodOpen
        (IOExternalMethodAction) &MyDriverClient::sMethodTest,      // Method pointer
        0,                                                          // Num of scalar input values
        0,                                                          // Num of struct input values
        0,                                                          // Num of scalar output values
        0                                                           // Num of struct output values
    }
};

//MARK:- IOUserClient overrides
IOReturn MyDriverClient::externalMethod(uint32_t selector, IOExternalMethodArguments *arguments, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference)
{
    IOLog("%s[%p]::%s(%d, %p, %p, %p, %p)\n", getName(), this, __FUNCTION__,
          selector, arguments, dispatch, target, reference);
    
    if (selector >= kNumberOfMethods)
        return kIOReturnUnsupported;
    
    dispatch = (IOExternalMethodDispatch*) &sMethods[selector];
    target = this;
    reference = NULL;
    
    return super::externalMethod(selector, arguments, dispatch, target, reference);
}

bool MyDriverClient::initWithTask(task_t owningTask, void *securityToken, UInt32 type, OSDictionary *properties)
{
    if (!owningTask)
        return false;
    
    if (!super::initWithTask(owningTask, securityToken, type))
        return false;
    
    IOLog("%s[%p]::%s(%p, %p, %u, %p)\n", getName(), this, __FUNCTION__, owningTask, securityToken, (unsigned int)type, properties);
    
    mTask = owningTask;
    mProvider = NULL;
    
    return true;
}

bool MyDriverClient::start(IOService *provider)
{
    bool success;
    
    IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    
    mProvider = OSDynamicCast(MyDriver, provider);
    success = (mProvider != NULL);
    
    if (success)
        success = super::start(provider);
    
    return success;
}

void MyDriverClient::stop(IOService* provider)
{
    IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);
    
    super::stop(provider);
}

IOReturn MyDriverClient::clientClose(void)
{
    IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
    
    if (!isInactive())
        terminate();
    
    return kIOReturnSuccess;
}

//MARK:- Static dispatch methods
IOReturn MyDriverClient::sMethodOpen(MyDriverClient *target, void *ref, IOExternalMethodArguments *args)
{
    return target->methodOpen(args);
}

IOReturn MyDriverClient::sMethodClose(MyDriverClient *target, void *ref, IOExternalMethodArguments *args)
{
    return target->methodClose(args);
}

IOReturn MyDriverClient::sMethodTest(MyDriverClient *target, void *ref, IOExternalMethodArguments *args)
{
    return target->methodTest(args);
}

//MARK:- Non static driver methods
IOReturn MyDriverClient::methodOpen(IOExternalMethodArguments *args)
{
    IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
    return kIOReturnSuccess;
}

IOReturn MyDriverClient::methodClose(IOExternalMethodArguments *args)
{
    IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
    return kIOReturnSuccess;
}

IOReturn MyDriverClient::methodTest(IOExternalMethodArguments *args)
{
    IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);
    return kIOReturnSuccess;
}
