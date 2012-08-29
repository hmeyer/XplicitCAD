/*
    This file is part of XplicitCAD.
    Copyright 2012 Henning Meyer

    XplicitCAD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xplicit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XplicitCAD.  If not, see <http://www.gnu.org/licenses/>.
*/

extern "C"
{
        #include "lua.h"
        #include "lualib.h"
        #include "lauxlib.h"
}

#include <luabind/luabind.hpp>
#include <iostream>
#include <string>
#include <boost/scoped_array.hpp>
#include "luabridge.h"


using namespace std;

class FDLogger {
  public:
	FDLogger(int fd);
	~FDLogger();
	void getLog(std::string &log);
	int getFD() const { return m_pipe[1]; }	
	void closeWriteEnd();
  protected:
	int m_old_fd;
	int m_pipe[2];
};

FDLogger::FDLogger(int fd) {
	if ((m_old_fd = dup(fd))==-1) throw;
	if (pipe(m_pipe)) throw;
	if (dup2(m_pipe[1], 1)==-1) throw;
}

FDLogger::~FDLogger() {
	closeWriteEnd();
	close(m_pipe[0]);
}

void FDLogger::closeWriteEnd() {
	if (m_pipe[1]) {
		close(m_pipe[1]);
		m_pipe[1]=0;
		dup2(m_old_fd, 1);
	}
}

void FDLogger::getLog(std::string &log) {
  const int BuffSize = 1024;
  boost::scoped_array<char> buff(new char[BuffSize]);
  memset( buff.get(), 0, BuffSize );
  int count;
  while((count=read(m_pipe[0], buff.get(), BuffSize-1))>0) {
	log += buff.get();
  	memset( buff.get(), 0, BuffSize );
  }
}


LuaBridge::LuaBridge():m_state( luaL_newstate())  {
  // Connect LuaBind to this lua state
  luabind::open(m_state);
  luaL_openlibs( m_state ); 
}

LuaBridge::~LuaBridge() {
  lua_close(m_state);
}

int LuaBridge::evaluate(const std::string &code, std::string &logStr) {
  FDLogger log(1);
  int result = luaL_dostring(
    m_state,
    code.c_str());
  luaL_dostring( m_state, "io.flush()");
  log.closeWriteEnd();
  log.getLog( logStr );
  return result;
}
  
