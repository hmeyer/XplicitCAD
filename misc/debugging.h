#ifndef DEBUGGING_H
#define DEBUGGING_H


#include <iostream>



#ifdef NDEBUG
    class DebugStream {
    public:
      DebugStream& operator<< (bool val) {return *this;}
      DebugStream& operator<< (short val) {return *this;}
      DebugStream& operator<< (unsigned short val) {return *this;}
      DebugStream& operator<< (int val) {return *this;}
      DebugStream& operator<< (unsigned int val) {return *this;}
      DebugStream& operator<< (long val) {return *this;}
      DebugStream& operator<< (unsigned long val) {return *this;}
      DebugStream& operator<< (float val) {return *this;}
      DebugStream& operator<< (double val) {return *this;}
      DebugStream& operator<< (long double val) {return *this;}
      DebugStream& operator<< (const void* val) {return *this;}
      DebugStream& operator<< (std::streambuf* sb) {return *this;}
      DebugStream& operator<< (std::ostream& ( *pf )(std::ostream&)) {return *this;}
      DebugStream& operator<< (std::ios& ( *pf )(std::ios&)) {return *this;}
      DebugStream& operator<< (std::ios_base& ( *pf )(std::ios_base&)) {return *this;} 
    };
    template<typename T>
    DebugStream &operator<<(DebugStream &s, T &t) { return s; }
    extern DebugStream debugger;
#else
    extern std::ostream &debugger;
#endif
    
#endif