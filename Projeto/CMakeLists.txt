cmake_minimum_required(VERSION 3.16)

project(Projeto VERSION 0.1 LANGUAGES CXX)

# Ativa geração automática de código Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
configure_file(
  ${CMAKE_SOURCE_DIR}/db_Projeto.db
  ${CMAKE_BINARY_DIR}/db_Projeto.db
  COPYONLY
)

# Padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra pacotes Qt6 necessários
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Lista de todos os arquivos do projeto
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui

    cadastro.cpp cadastro.h cadastro.ui
    menuprincipal.cpp menuprincipal.h menuprincipal.ui
    esqueceusenha.cpp esqueceusenha.h esqueceusenha.ui
    fazerdeposito.cpp fazerdeposito.h fazerdeposito.ui
    fazersaque.cpp fazersaque.h fazersaque.ui
    fazertransferencia.cpp fazertransferencia.h fazertransferencia.ui
    verfaturacredito.cpp verfaturacredito.h verfaturacredito.ui
    verextrato.cpp verextrato.h verextrato.ui
    encerrarconta.cpp encerrarconta.h encerrarconta.ui
    versaldo.cpp versaldo.h versaldo.ui

    Assets.qrc
)

# Criação do executável usando Qt6
qt_add_executable(Projeto
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    conta.h conta.cpp
)

# Link com as bibliotecas do Qt
target_link_libraries(Projeto PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Configurações de bundle (opcional)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Projeto)
endif()

set_target_properties(Projeto PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Instalação
include(GNUInstallDirs)
install(TARGETS Projeto
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finaliza (apenas para Qt6)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Projeto)
endif()
