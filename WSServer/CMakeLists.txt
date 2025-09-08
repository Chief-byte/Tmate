project(WSServer CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
################################################################################
# Source groups
################################################################################
set(Headers
    "DC/DC/DC.h"
    "DC/DC/IDC.h"
    "DC/PISA/include/lfsadmin.h"
    "DC/PISA/include/lfsalm.h"
    "DC/PISA/include/lfsapi.h"
    "DC/PISA/include/lfsbcr.h"
    "DC/PISA/include/lfscam.h"
    "DC/PISA/include/lfscdm.h"
    "DC/PISA/include/lfscim.h"
    "DC/PISA/include/lfscrd.h"
    "DC/PISA/include/lfsidc.h"
    "DC/PISA/include/lfspin.h"
    "DC/PISA/include/lfsptr.h"
    "DC/PISA/include/lfssiu.h"
    "DC/PISA/include/lfsspi.h"
    "DC/PISA/include/lfsttu.h"
    "DC/PISA/include/lfsvdm.h"
    "DC/PISA/XFS30/DC_30.h"
    "DC/PISA/XFS30/DCCamera_31/DCCamera_31.h"
    "DC/PISA/XFS30/DCCardReader_30/DCCardReader_30.h"
    "DC/PISA/XFS30/DCCashAcceptor_30/DCCashAcceptor_30.h"
    "DC/PISA/XFS30/DCCashDispenser_30/DCCashDispenser_30.h"
    "DC/PISA/XFS30/DCPinPad_30/DCPinPad_30.h"
    "DC/PISA/XFS30/DCPinPad_30/XFSPINCHN.h"
    "DC/PISA/XFS30/DCPrinter_30/DCPrinter_30.h"
    "DC/PISA/XFS30/DCSensorsAndIndicators_30/DCSensorsAndIndicators_30.h"
    "Extension/Extension.h"
    "include/Base64.h"
    "include/DCTrace.h"
    "include/FileHelper.h"
    "include/JavaScriptStringParam.h"
    "include/KDMexp.h"
    "include/Keyou.h"
    "include/ssm.h"
    "include/SSMKeyou.h"
    "include/Utils.h"
    "include/xmlhelper.h"
    "MessageHandle.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "DC/DC/DC.cpp"
    "DC/PISA/XFS30/DC_30.cpp"
    "DC/PISA/XFS30/DCCamera_31/DCCamera_31.cpp"
    "DC/PISA/XFS30/DCCardReader_30/DCCardReader_30.cpp"
    "DC/PISA/XFS30/DCCashAcceptor_30/DCCashAcceptor_30.cpp"
    "DC/PISA/XFS30/DCCashDispenser_30/DCCashDispenser_30.cpp"
    "DC/PISA/XFS30/DCPinPad_30/DCPinPad_30.cpp"
    "DC/PISA/XFS30/DCPrinter_30/DCPrinter_30.cpp"
    "DC/PISA/XFS30/DCSensorsAndIndicators_30/DCSensorsAndIndicators_30.cpp"
    "Extension/Extension.cpp"
    "include/Base64.cpp"
    "include/FileHelper.cpp"
    "include/JavaScriptStringParam.cpp"
    "include/Keyou.cpp"
    "include/SSMKeyou.cpp"
    "include/Utils.cpp"
    "include/xmlhelper.cc"
    "main.cpp"
    "MessageHandle.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################

add_executable(WSServer ${ALL_FILES})
target_include_directories(WSServer PRIVATE
	DC/DC
	DC/PISA/include
	DC/PISA/XFS30
	Extension
	include
)

target_link_libraries(WSServer PRIVATE
	websockets
	pthread
	dl
	x11
	xml2
	nettle
	gmodule-2.0
	gthread-2.0
	gobject-2.0	
)
target_compile_options(WSServer PRIVATE -Wall)

#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
#set(ROOT_NAMESPACE WSServer)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    VS_GLOBAL_KEYWORD "Linux"
#)
################################################################################
# Compile definitions
################################################################################

################################################################################
# Compile and link options
################################################################################

