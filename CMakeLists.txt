cmake_minimum_required(VERSION 3.23)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VESRION})

add_executable(bulk bulk.cpp logger.cpp bulk_handler.cpp)

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(bulk
    PRIVATE "${CMAKE_BINARY_DIR}"
)

include(CTest)

if(BUILD_TESTING)

    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
    )
    if (WIN32)
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif (WIN32)

    FetchContent_MakeAvailable(googletest)

    add_executable(test_bulk test_bulk.cpp logger.cpp bulk_handler.cpp)

    set_target_properties(test_bulk PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_bulk
        gtest_main
    )
    
    include(GoogleTest)
endif()

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
    if(BUILD_TESTING)
        target_compile_options(test_bulk PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror -static -pthread
    )
    if(BUILD_TESTING)
        target_compile_options(test_bulk PRIVATE
            -Wall -Wextra -pedantic -Werror -static -pthread
        )
    endif()
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(BUILD_TESTING)
    add_test(test_bulk test_bulk)
endif()
