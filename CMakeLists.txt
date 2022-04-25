cmake_minimum_required(VERSION 2.8)
project(vigdec)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
	target_compile_options(tester PUBLIC "-pthread")
endif()


set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

if (DIRTY)
  set(CMAKE_C_FLAGS_RELEASE "-O3 -march=broadwell -mtune=broadwell")
endif()	

set(CRYPTO 
	crypto/exception.cpp
	crypto/sym_alg.cpp
	crypto/vigenere_ciph.cpp
	crypto/subst_cipher.cpp
)

set(ANALYZER 
	analyzer/analyzer.cpp
	analyzer/scanner.cpp
	analyzer/utils.cpp
	analyzer/ngram.cpp
	analyzer/vigdec.cpp
)

set(TEST 
	test/test_main.cpp
	test/test_cryptor.cpp
	analyzer/utils.cpp
	test/gtest/gtest-all.cc
)

add_library(cryptor SHARED ${CRYPTO})

include_directories(test/include)

add_executable(tester ${TEST})
add_executable(vigdec ${ANALYZER})
target_link_libraries(vigdec cryptor)
if (CMAKE_THREAD_LIBS_INIT)
	target_link_libraries(tester cryptor "${CMAKE_THREAD_LIBS_INIT}")
endif()
target_link_libraries(tester cryptor)
