# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\georgewaller\Desktop\CameraProcessor\camera\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\georgewaller\Desktop\CameraProcessor\camera\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {camera}\
-hw {C:\Users\georgewaller\Desktop\CameraFPGA\camera.xsa}\
-fsbl-target {psu_cortexa53_0} -out {C:/Users/georgewaller/Desktop/CameraProcessor}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform write
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
bsp reload
domain active {zynq_fsbl}
bsp reload
platform generate -domains 
domain active {standalone_ps7_cortexa9_0}
bsp reload
bsp config stdin "ps7_uart_0"
bsp config stdin "ps7_uart_0"
bsp config stdout "ps7_uart_0"
bsp write
platform generate -domains 
