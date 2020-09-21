# http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt Config
find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# DtkConfig
add_definitions("-DQT_MESSAGELOGCONTEXT")
pkg_search_module(DtkPay REQUIRED dtkpay)
include_directories(${DtkPay_INCLUDE_DIRS})

add_executable(com.deepin.demo main.cpp)
target_link_libraries(com.deepin.demo
		Qt5::Widgets
		Qt5::DBus
		OpenSSL::SSL
		OpenSSL::Crypto
		${DtkPay_LDFLAGS})

install(TARGETS com.deepin.demo DESTINATION ${CMAKE_INSTALL_PREFIX}/files/bin)
install(FILES ${CMAKE_SOURCE_DIR}/src/metadata/info DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/metadata/entries
		DESTINATION ${CMAKE_INSTALL_PREFIX}
		USE_SOURCE_PERMISSIONS)
