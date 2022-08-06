# Add Catch2 dependency
find_package(Catch2 CONFIG REQUIRED)

# Add fmt dependency
find_package(fmt CONFIG REQUIRED)

# Add Magic Enum dependency
find_package(magic_enum CONFIG REQUIRED)

# Add Nameof dependency
find_package(nameof CONFIG REQUIRED)

# Add automatically generated test files
file(GLOB TEST_MISC_SRC ${TEST_SRC_DIR}/Misc/Test_*.cpp)

set(SOURCES
   ${SOURCES}
   ${TEST_SRC_DIR}/unit_tests.cpp
   ${TEST_MISC_SRC}
)

set(HEADERS
   ${HEADERS}
)

# Create executable file from sources
add_executable(${NAME_TEST} ${SOURCES} ${HEADERS})

target_include_directories(${NAME_TEST} PRIVATE
                           ${LIB_INCLUDE_DIR}
                           ${TEST_INCLUDE_DIR}
)

target_link_libraries(${NAME_TEST} PRIVATE
                      Catch2::Catch2WithMain
                      fmt::fmt
                      magic_enum::magic_enum
                      nameof::nameof
                      ${NAME_LIB}
)