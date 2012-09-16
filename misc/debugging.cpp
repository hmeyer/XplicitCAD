#include "debugging.h"

#ifdef NDEBUG
    DebugStream debugger;
#else
    std::ostream &debugger = std::cout;
#endif