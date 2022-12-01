cmake_minimum_required(VERSION 3.16)
include(FetchContent)
project(isim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

# Build libs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/zlib)
set(LIBPNG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/libpng)

include_directories(src tests ${ZLIB_INCLUDE_DIR} ${LIBPNG_INCLUDE_DIR})

set(SOURCES
        src/Vector/Vector.cpp
        src/Scene/Scene.cpp
		src/Scene/Factory/Dictionary.cpp
        src/Object/MeshObject.cpp
		src/Object/Box/Box.cpp
		src/Object/Box/CubeBox.cpp
		src/Object/Camera/Camera.cpp
		src/Object/Light/Light.cpp
        src/Object/Light/PointLight.cpp
        src/Image/PNG.cpp
        src/Image/Image.cpp
		src/Menger/Menger.cpp
		src/Object/Sphere.cpp
        src/Object/Cube/Cube.cpp
        src/Object/Triangle/Triangle.cpp
		src/Material/UniformMaterial.cpp
		src/Profiler/Profiler.cpp
		src/Pyramide/Pyramide.cpp)

set(TESTS
		tests/Vector/Vector.cpp
		tests/Object/CameraTest.cpp
		tests/Light/PointLight/PointLight.cpp
		#tests/Object/CubeTest.cpp
		tests/Object/CubeBoxTest.cpp
		tests/Scene/Scene.cpp
		tests/Parser.hpp
		tests/Menger/MengerTest.cpp
		tests/Triangle/TriangleTest.cpp
		tests/Object/TransformTest.cpp
		tests/Object/MeshObjectTest.cpp
		tests/Object/CubeTest.cpp
		tests/Object/SphereTest.cpp
		tests/Pyramide/PyramideTest.cpp)


add_executable(isim
			   ${SOURCES} main.cpp)

FetchContent_Declare(
		googletest
		# Specify the commit you depend on and update it regularly.
		URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test ${TESTS} ${SOURCES})

set(LIBS PRIVATE
	gtest
	gtest_main
	nlohmann_json::nlohmann_json
	zlib
	png
	)


include(GoogleTest)
gtest_discover_tests(test)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
target_link_libraries(isim ${LIBS})
target_link_libraries(test ${LIBS})