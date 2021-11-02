cmake_minimum_required(VERSION 3.20.1)

project(maseczki-pk)

if (APPLE)
	set(OpenCV_DIR $ENV{OPENCVPATH})
endif (APPLE)

if (WIN32)
	set(OpenCV_DIR "C:/opencv/build/x64/vc15/lib")
endif (WIN32)


find_package(OpenCV 4.5.4 REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
	include
)

add_executable(maseczki-pk
	src/main.cpp
	src/FaceDetection.cpp
	src/EyesDetection.cpp
	src/MouthDetection.cpp
	src/MaskDetection.cpp
	src/Painter.cpp
	# You can put here your .h and .cpp files to expand the example.
)

target_link_libraries(maseczki-pk
	${OpenCV_LIBS}
)