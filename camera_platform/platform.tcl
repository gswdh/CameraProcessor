# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\georgewaller\Desktop\CameraProcessor\camera_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\georgewaller\Desktop\CameraProcessor\camera_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {camera_platform}\
-hw {C:\Users\georgewaller\Desktop\CameraFPGA\camera_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -fsbl-target {psu_cortexa53_0} -out {C:/Users/georgewaller/Desktop/CameraProcessor}

platform write
platform generate -domains 
platform active {camera_platform}
bsp reload
domain active {zynq_fsbl}
bsp reload
bsp write
domain active {freertos10_xilinx_domain}
bsp setlib -name xilffs -ver 4.4
bsp write
bsp reload
catch {bsp regenerate}
platform generate
