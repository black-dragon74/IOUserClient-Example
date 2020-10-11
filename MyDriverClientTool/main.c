//
//  main.c
//  MyDriverClientTool
//
//  Created by Nick on 10/11/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <IOKit/IOKitLib.h>

#include "UserKernelShared.h"

int main(int argc, const char * argv[]) {
    kern_return_t   kernResult;
    io_service_t    service;
    io_iterator_t   iterator;
    io_connect_t    connect = 0;
    bool            found = false;
    
    kernResult = IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("MyDriver"), &iterator);
    
    if (kernResult != KERN_SUCCESS) {
        fprintf(stderr, "IOServiceGetMatchingServices returned 0x%08x\n\n", kernResult);
        return -1;
    }
        
    while ((service = IOIteratorNext(iterator)) != IO_OBJECT_NULL) {
        printf("Found a device of class MyDriver\n");
        found = true;
        
        kernResult = IOServiceOpen(service, mach_task_self(), 0, &connect);
        if (kernResult != kIOReturnSuccess)
            break;
        
        IOObjectRelease(service);
    }
    
    // Release the io_iterator_t now that we're done with it.
    IOObjectRelease(iterator);
    
    if (!found) {
        fprintf(stderr, "No matching drivers found.\n");
        return -1;
    }
    
    // Now execute any method you want, like:
    printf("Calling functions from userspace to kernel space...\n\n");
    for (int i = 0; i < kNumberOfMethods; i++) {
        kernResult = IOConnectCallScalarMethod(connect, i, NULL, 0, NULL, NULL);
        if (kernResult == kIOReturnSuccess)
            printf("Successfully called method at %d in kernel space.\n", i);
        sleep(1.5);
    }

    return EXIT_SUCCESS;
}
