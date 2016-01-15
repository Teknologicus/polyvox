# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "OFF")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "OFF")
SET(CPACK_BINARY_NSIS "ON")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "OFF")
SET(CPACK_BINARY_ZIP "OFF")
SET(CPACK_CMAKE_GENERATOR "Visual Studio 14 2015")
SET(CPACK_COMPONENTS_ALL "Unspecified;development;library")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "NSIS")
SET(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/Jos/Documents/GitHub/polyvox/build;PolyVox;ALL;/")
SET(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/PolyVox")
SET(CPACK_MODULE_PATH "")
SET(CPACK_NSIS_CONTACT "matt@milliams.com")
SET(CPACK_NSIS_DISPLAY_NAME "PolyVox SDK 0.2.1")
SET(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
SET(CPACK_NSIS_HELP_LINK "http:\\\\thermite3d.org/phpBB/")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_MODIFY_PATH "ON")
SET(CPACK_NSIS_PACKAGE_NAME "PolyVox SDK 0.2.1")
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\thermite3d.org")
SET(CPACK_OUTPUT_CONFIG_FILE "C:/Users/Jos/Documents/GitHub/polyvox/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files (x86)/CMake/share/cmake-3.4/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PolyVox SDK")
SET(CPACK_PACKAGE_FILE_NAME "PolyVox SDK-0.2.1-win32")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "PolyVox SDK 0.2.1")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "PolyVox SDK 0.2.1")
SET(CPACK_PACKAGE_NAME "PolyVox SDK")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Thermite 3D Team")
SET(CPACK_PACKAGE_VERSION "0.2.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "2")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files (x86)/CMake/share/cmake-3.4/Templates/CPack.GenericLicense.txt")
SET(CPACK_RESOURCE_FILE_README "C:/Program Files (x86)/CMake/share/cmake-3.4/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files (x86)/CMake/share/cmake-3.4/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "ON")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "7Z;ZIP")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/Jos/Documents/GitHub/polyvox/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_TBZ2 "")
SET(CPACK_SOURCE_TGZ "")
SET(CPACK_SOURCE_TXZ "")
SET(CPACK_SOURCE_TZ "")
SET(CPACK_SOURCE_ZIP "ON")
SET(CPACK_SYSTEM_NAME "win32")
SET(CPACK_TOPLEVEL_TAG "win32")
SET(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/Jos/Documents/GitHub/polyvox/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for component "library"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Library")
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "The runtime libraries")
set(CPACK_COMPONENT_LIBRARY_REQUIRED TRUE)

# Configuration for component "development"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_DEVELOPMENT_DESCRIPTION "Files required for developing with PolyVox")
set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS library)

# Configuration for component "example"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
set(CPACK_COMPONENT_EXAMPLE_DISPLAY_NAME "OpenGL Example")
set(CPACK_COMPONENT_EXAMPLE_DESCRIPTION "A PolyVox example application using OpenGL")
set(CPACK_COMPONENT_EXAMPLE_DEPENDS library)

# Configuration for component group "bindings"
set(CPACK_COMPONENT_GROUP_BINDINGS_DISPLAY_NAME "Bindings")
set(CPACK_COMPONENT_GROUP_BINDINGS_DESCRIPTION "Language bindings")

# Configuration for component "python"

SET(CPACK_COMPONENTS_ALL Unspecified development library)
set(CPACK_COMPONENT_PYTHON_DISPLAY_NAME "Python Bindings")
set(CPACK_COMPONENT_PYTHON_DESCRIPTION "PolyVox bindings for the Python language")
set(CPACK_COMPONENT_PYTHON_GROUP bindings)
set(CPACK_COMPONENT_PYTHON_DEPENDS library)
set(CPACK_COMPONENT_PYTHON_DISABLED TRUE)
