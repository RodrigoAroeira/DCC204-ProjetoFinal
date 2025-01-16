cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "trabalho")

project("${PROJECT_NAME}" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR "src")
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${SRC_DIR}/main.cpp")

include_directories(headers headers/Jogos)

# Arquivos que serão usados tanto no programa quanto nos testes
set(LIB "Common")
add_library("${LIB}" STATIC ${SRC_FILES})

add_executable(${PROJECT_NAME} "${SRC_DIR}/main.cpp")
target_link_libraries("${PROJECT_NAME}" "${LIB}")

add_custom_target(
  run
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

file(GLOB TEST_FILES "tests/*.cpp")
# Criar um executavel de cada arquivo de teste
foreach(FILE IN LISTS TEST_FILES)
  get_filename_component(TEST_NAME ${FILE} NAME_WE)
  add_executable(${TEST_NAME} ${FILE})
  target_link_libraries(${TEST_NAME} ${LIB})
endforeach()
