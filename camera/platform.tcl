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
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -display-name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos10_xilinx} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {freertos_hello_world}
platform generate -domains 
platform active {camera}
domain active {zynq_fsbl}
domain active {freertos10_xilinx_ps7_cortexa9_0}
platform generate -quick
platform generate
