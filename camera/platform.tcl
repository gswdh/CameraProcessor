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
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {C:/Users/georgewaller/Desktop/CameraProcessor}

platform write
platform generate -domains 
platform clean
platform generate
bsp reload
platform generate -domains freertos10_xilinx_domain 
platform generate -domains freertos10_xilinx_domain 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
bsp reload
catch {bsp regenerate}
platform active {camera}
bsp reload
bsp setlib -name xilffs -ver 5.0
bsp write
bsp reload
catch {bsp regenerate}
platform active {camera}
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain 
platform active {camera}
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform active {camera}
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
bsp reload
domain active {zynq_fsbl}
bsp reload
platform generate -domains 
platform active {camera}
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains freertos10_xilinx_domain 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform clean
platform generate
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform clean
platform generate
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
platform config -updatehw {C:/Users/georgewaller/Desktop/CameraFPGA/camera.xsa}
platform generate -domains 
platform generate -domains freertos10_xilinx_domain,zynq_fsbl 
