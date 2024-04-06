cmake_minimum_required(VERSION 3.26)
project(new)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.7.0/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(new src/main.cpp
        src/domain/Dog.cpp
        src/GUI/AdminGUI.cpp
        src/GUI/MainGUI.cpp
        src/GUI/UserGUI.cpp
        src/models/DogsModel.cpp
        src/repository/validators/DogValidator.cpp
        src/repository/CSVFileRepository.cpp
        src/repository/FileRepository.cpp
        src/repository/HTMLFileRepository.cpp
        src/repository/Repository.cpp
        src/service/Service.cpp
        src/tests/TestDog.cpp
        src/tests/TestRepository.cpp
        src/tests/tests.cpp
        src/tests/TestService.cpp
        src/UI/Console.cpp
        src/UndoRedo/Command.cpp
        src/UndoRedo/UndoRedo.cpp
        src/utilities/Utilities.cpp
        src/views/DogsTableView.cpp
        cmake-build-debug/new_autogen/RDKJSLABA2/moc_UserGUI.cpp
        cmake-build-debug/new_autogen/RDKJSLABA2/moc_AdminGUI.cpp
        cmake-build-debug/new_autogen/RDKJSLABA2/moc_MainGUI.cpp
)

target_link_libraries(new
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

QT6_WRAP_CPP(MOC_SOURCES ${src/GUI/AdminGUI.h} ${src/GUI/MainGUI.h} ${src/GUI/UserGUI.h} ${src/models/DogsModel.h})

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
