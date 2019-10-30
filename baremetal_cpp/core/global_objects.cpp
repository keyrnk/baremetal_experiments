#include <cstddef>


extern void(*init_array_start[])(void);
extern void(*init_array_end[])(void);


extern "C"
void GlobalInitialize()
{
    size_t count = init_array_end - init_array_start;
    for (size_t i = 0; i < count; ++i)
    {
        init_array_start[i]();
    }
}

extern "C" int __cxa_atexit(
    void *object,
    void (*destructor)(void *),
    void *dso_handle)
{
    static_cast<void>(object);
    static_cast<void>(destructor);
    static_cast<void>(dso_handle);

    return 0;
}

void* __dso_handle = nullptr;

/*
bool __cxa_guard_acquire()
{
    return true;
}

bool __cxa_guard_release()
{
    return true;
}
*/
