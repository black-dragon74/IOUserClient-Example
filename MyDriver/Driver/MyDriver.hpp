//
//  MyDriver.hpp
//  MyDriver
//
//  Created by Nick on 10/11/20.
//
#include<IOKit/IOService.h>

#include "UserKernelShared.h"

class MyDriver : public IOService
{
    OSDeclareDefaultStructors(MyDriver);
    
public:
    virtual bool init(OSDictionary* dictionary) override;
    virtual void free(void) override;
    
    virtual bool start(IOService* provider) override;
    virtual void stop(IOService* provider) override;
};
