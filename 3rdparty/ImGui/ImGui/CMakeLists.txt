cmake_minimum_required (VERSION 3.6)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE, DEBUG)
endif (NOT CMAKE_BUILD_TYPE)

set (CMAKE_CXX_STANDARD 17)

if(NOT MSVC)
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g2 -O0 -Wall -Werror -fPIC")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -Wall -Werror -fPIC -funroll-loops -Ofast -fno-math-errno -fomit-frame-pointer -ffast-math -flto")
	
	if (NOT CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm")
		set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")
	endif ()
else(NOT MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /nologo /DNOMINMAX /D_CRT_SECURE_NO_WARNINGS /D_DEBUG /GS /Zi /debug")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /nologo /DNOMINMAX /D_CRT_SECURE_NO_WARNINGS /GS /GL /Gm /O2 /Od /Ox")
    add_compile_options(/MP)
endif(NOT MSVC)

file (GLOB_RECURSE IMGUI_SOURCES *)

add_library (ImGui SHARED ${IMGUI_SOURCES})

target_include_directories (ImGui PUBLIC ${PROJECT_SOURCE_DIR}/3rdparty/ImGui)

if(MSVC)
    MACRO(GROUP_SRC SRCS)
      foreach(FILE ${IMGUI_SOURCES}) 
        #convert source file to absolute
        get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
        # Get the directory of the absolute source file
        get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
        # Remove common directory prefix to make the group
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
        # Make sure we are using windows slashes
        string(REPLACE "/" "\\" GROUP "${GROUP}")
        # Group into "Source Files" and "Header Files"
        if ("${FILE}" MATCHES ".*\\.cpp")
          set(GROUP "Source Files${GROUP}")
        elseif("${FILE}" MATCHES ".*\\.h")
          set(GROUP "Header Files${GROUP}")
        endif()
        source_group("${GROUP}" FILES "${FILE}")
      endforeach()
    ENDMACRO(GROUP_SRC)

    group_src (${IMGUI_SOURCES})
endif(MSVC)

if(NOT MSVC)

    target_compile_definitions (ImGui PRIVATE IMGUI_API=)
else(NOT MSVC)
    SET_TARGET_PROPERTIES(ImGui PROPERTIES ENABLE_EXPORTS TRUE)

    target_compile_definitions (ImGui PRIVATE "IMGUI_API=__declspec(dllexport)")
endif(NOT MSVC)
