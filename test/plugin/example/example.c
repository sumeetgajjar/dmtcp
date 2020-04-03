#include <stdio.h>
#include "dmtcp.h"
#include <Python.h>
#include <pthread.h>

static void *func(void *arg) {
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());

    printf("New thread: %ld\n", pthread_self());

    // exit the current thread
    pthread_exit(NULL);
}

static void spwan_thread() {
    printf("spawning new thread\n");
    pthread_t ptid;
    pthread_create(&ptid, NULL, &func, NULL);
}

static void py_interpreter_testing() {
    Py_Initialize();
    printf("Python Interpreter: %d.\n", Py_IsInitialized());

    printf("%s\n", Py_GetProgramName());
    printf("%s\n", Py_GetPrefix());
    printf("%s\n", Py_GetExecPrefix());
    printf("%s\n", Py_GetProgramFullPath());
    printf("%s\n", Py_GetPath());
    printf("%s\n", Py_GetVersion());
    printf("%s\n", Py_GetPlatform());
    printf("%s\n", Py_GetCopyright());
    printf("%s\n", Py_GetCompiler());
    printf("%s\n", Py_GetBuildInfo());

//    The below line fails since giving seg fault
//    printf("%s\n", Py_GetPythonHome());

}

/*
 * code to access python variables and call python functions
 * */
static void access_python_data_structures() {

}


static void checkpoint() {
    printf("\n*** The plugin is being called before checkpointing. ***\n");
}

static void resume() {
    printf("*** The application has now been checkpointed. ***\n");
}

static void restart() {
    printf("The application is now restarting from a checkpoint.\n");
}

static void example_event_hook(DmtcpEvent_t event, DmtcpEventData_t *data) {
    /* NOTE:  See warning in plugin/README about calls to printf here. */
    printf("\nCurrent event: %d\n", event);
    switch (event) {
        case DMTCP_EVENT_INIT:
            printf("The plugin containing %s has been initialized.\n", __FILE__);
            break;

        case DMTCP_EVENT_EXIT:
            printf("The plugin is being called before exiting.\n");
            break;

        case DMTCP_EVENT_PRECHECKPOINT:
            checkpoint();
            break;

        case DMTCP_EVENT_RESUME:
            resume();
            break;

        case DMTCP_EVENT_RESTART:
            restart();
//            py_interpreter_testing();
//            access_python_data_structures();

            // spawning thread fails here
            spwan_thread();
            break;

        default:
            break;
    }
}

DmtcpPluginDescriptor_t example_plugin = {
        DMTCP_PLUGIN_API_VERSION,
        DMTCP_PACKAGE_VERSION,
        "example",
        "DMTCP",
        "dmtcp@ccs.neu.edu",
        "Example plugin",
        example_event_hook
};

DMTCP_DECL_PLUGIN(example_plugin);