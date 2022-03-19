# Add libzippp dependency
find_package(libzippp CONFIG REQUIRED)

# Add Magic Enum dependency
find_package(magic_enum CONFIG REQUIRED)

# Add Nameof dependency
find_package(nameof CONFIG REQUIRED)

set(SOURCES
   ${SOURCES}
   ${LIB_SRC_DIR}/DataStream.cpp
   ${LIB_SRC_DIR}/LayerStuff.cpp
   ${LIB_SRC_DIR}/Pad.cpp
   ${LIB_SRC_DIR}/Parser.cpp
)

set(HEADERS
   ${HEADERS}
   ${LIB_INCLUDE_DIR}/DataStream.hpp
   ${LIB_INCLUDE_DIR}/General.hpp
   ${LIB_INCLUDE_DIR}/LayerStuff.hpp
   ${LIB_INCLUDE_DIR}/Pad.hpp
   ${LIB_INCLUDE_DIR}/PadFile.hpp
   ${LIB_INCLUDE_DIR}/Parser.hpp
)

include(GenerateExportHeader)

# Create library file from sources
add_library(${NAME_LIB} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${NAME_LIB} PRIVATE
)

target_link_libraries(${NAME_LIB} PRIVATE
                      libzip::zip
                      libzippp::libzippp
                      magic_enum::magic_enum
                      nameof::nameof
)