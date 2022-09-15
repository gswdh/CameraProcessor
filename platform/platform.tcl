# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\georgewaller\Desktop\CameraProcessor\platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\georgewaller\Desktop\CameraProcessor\platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {platform}\
-hw {C:\Users\georgewaller\Desktop\CameraProcessor\microzed_base_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -fsbl-target {psu_cortexa53_0} -out {C:/Users/georgewaller/Desktop/CameraProcessor}

platform write
platform generate -domains 
platform active {platform}
bsp reload
bsp setlib -name lwip211 -ver 1.3
bsp setlib -name xilffs -ver 4.4
bsp write
bsp reload
catch {bsp regenerate}
bsp write
bsp removelib -name lwip211
bsp setlib -name lwip211 -ver 1.3
bsp write
bsp reload
catch {bsp regenerate}
bsp config api_mode "SOCKET_API"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_domain 
