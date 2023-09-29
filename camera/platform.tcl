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
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -fsbl-target {psu_cortexa53_0} -out {C:/Users/georgewaller/Desktop/CameraProcessor}

platform write
platform generate -domains 
platform generate
platform clean
platform generate
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
bsp reload
platform generate -domains 
