//
//  MyDriverClient.hpp
//  MyDriver
//
//  Created by Nick on 10/11/20.
//

#ifndef MyDriverClient_hpp
#define MyDriverClient_hpp

#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>

#include "MyDriver.hpp"

class MyDriverClient : public IOUserClient
{
    OSDeclareDefaultStructors(MyDriverClient);
    
private:
    MyDriver*   mProvider;
    task_t      mTask;
    static const IOExternalMethodDispatch sMethods[kNumberOfMethods];
    
public:
    virtual void stop(IOService* provider) override;
    virtual bool start(IOService* provider) override;
    
    virtual bool initWithTask(task_t owningTask, void* securityToken,
                              UInt32 type, OSDictionary* properties) override;

    virtual IOReturn clientClose(void) override;
    virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArguments* arguments,
                                    IOExternalMethodDispatch* dispatch, OSObject* target, void* reference) override;
    
protected:
    /**
     *  The following static methods have non-static handlers defined just beneath them,
     *  In the relative order. The static methods redirect the call to the `target` instance.
     *  The normal methods unpack args and call the related driver methods.
     */
    static IOReturn sMethodOpen(MyDriverClient* target, void* ref, IOExternalMethodArguments* args);
    static IOReturn sMethodClose(MyDriverClient* target, void* ref, IOExternalMethodArguments* args);
    static IOReturn sMethodTest(MyDriverClient* target, void* ref, IOExternalMethodArguments* args);
    
    virtual IOReturn methodOpen(IOExternalMethodArguments* args);
    virtual IOReturn methodClose(IOExternalMethodArguments* args);
    virtual IOReturn methodTest(IOExternalMethodArguments* args);
};

#endif /* MyDriverClient_hpp */
