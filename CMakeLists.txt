cmake_minimum_required(VERSION 3.5)

project(AlcoMetr LANGUAGES CXX VERSION 1.0.2)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBS OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_RC_FLAGS —use-temp-file)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(QTimWidgets REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    $<TARGET_PROPERTY:QTimWidgets,INTERFACE_INCLUDE_DIRECTORIES>
    ${QT_INCLUDES}    
    ${${PROJECT_NAME}_OPT_INCLUDE_DIRS}    
    )
set(${PROJECT_NAME}_SRC
	src/main.cpp
    src/mainwindow.cpp
    src/alco_item.cpp    
    src/parse_inshaker.cpp   
    src/alco_save_worker.cpp
    src/alco_base_worker.cpp
    src/alco_tablewidget.cpp
    src/alco_cocktail_manager.cpp    
    src/alco_create_coctail_form.cpp
    src/alco_current_bar.cpp    
    src/alco_chose_item_widget.cpp    
    src/alco_coctails_save_worker.cpp    
    src/alco_edit_base.cpp
    src/alco_use_coctails.cpp
    )

set(${PROJECT_NAME}_HDR	
    src/include/mainwindow.h 
    src/include/alco_item.h
    src/include/parse_inshaker.h
    src/include/alco_save_worker.h
    src/include/alco_base_worker.h
    src/include/alco_tablewidget.h
    src/include/alco_cocktail_manager.h
    src/include/alco_create_coctail_form.h
    src/include/alco_current_bar.h
    src/include/alco_chose_item_widget.h
    src/include/alco_coctails_save_worker.h
    src/include/alco_edit_base.h    
    src/include/alco_use_coctails.h
)

set(${PROJECT_NAME}_FORMS_UI
    gui/mainwindow.ui     
    gui/alco_cocktail_manager.ui
    gui/alco_create_coctail_form.ui
    gui/alco_current_bar.ui
    gui/alco_chose_item_widget.ui
    gui/alco_edit_base.ui
    gui/alco_use_coctails.ui
)

set(${PROJECT_NAME}_Qt_Resource_files
    resources.qrc
    ${${PROJECT_NAME}_Qt_Resource_files})

qt5_wrap_ui(${PROJECT_NAME}_UIs ${${PROJECT_NAME}_FORMS_UI})
qt5_wrap_cpp(${PROJECT_NAME}_MOCs ${${PROJECT_NAME}_HDR})
qt5_add_resources(${PROJECT_NAME}_RCCs ${${PROJECT_NAME}_Qt_Resource_files})

set(TARGET_EXE ${PROJECT_NAME})

add_executable(${TARGET_EXE} WIN32 ${OS_EX_FLAG}
    ${${PROJECT_NAME}_QT_SOURCES}
    ${${PROJECT_NAME}_QT_HEADERS}
    ${${PROJECT_NAME}_UIs}
    ${${PROJECT_NAME}_RCCs}
    ${${PROJECT_NAME}_MOCs}
    ${${PROJECT_NAME}_SRC}
    ${${PROJECT_NAME}_HDR}    
    ${${PROJECT_NAME}_VERSION_FILES})
set_target_properties(${TARGET_EXE}
    PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    )	
	
target_link_libraries(${TARGET_EXE}
    ${QT_LIBRARIES} 
    ${${PROJECT_NAME}_OPT_LIBS}
    Qt5::Widgets
    Qt5::Core       
    Qt5::Network
    QTimWidgets
    )
