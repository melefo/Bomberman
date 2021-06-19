if (NOT lua_FOUND)
  include(FetchContent)
  FetchContent_Declare(lua GIT_REPOSITORY https://github.com/walterschell/Lua)
  FetchContent_GetProperties(lua)
  if (NOT lua_POPULATED)
    SET(FETCHCONTENT_QUIET NO)
    set(LUA_BUILD_COMPILER OFF CACHE INTERNAL "")
    set(LUA_BUILD_INTERPRETER OFF CACHE INTERNAL "")
    set(LUA_BUILD_AS_CXX ON)
    FetchContent_Populate(lua)
    add_subdirectory(${lua_SOURCE_DIR} ${lua_BINARY_DIR})
    SET(lua_FOUND TRUE)
  endif()
endif()