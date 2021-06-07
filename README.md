# 例程使用方法
## 编译
在主目录下进行make
注意修改主目录下的makefile 将编译器修改为需要的编译器、默认情况下是arm-linux-gnueabihf-gcc 
如需在x86环境下使用程序 添加参数  TARGET_ARCH=X86
```
make -j4
```
需要某个例程的话比如
```
make battery 
```
暂时就两个例程 battery 和h264 如需增加，在platform目录下拷贝一份出来，或者不拷贝出来也可以，在该例子下从battery复制Makefile到该例子下面，进入Makefile,
129行修改一下main.o为该例子的main.o,生成文件自己命名,写法如下：
```bash
@$(CXX)  ../build/Objects/mytest/main.o $(ALL_FILES) -pthread -g -fPIC -g -o mytest
```
再打开主目录下的makefile，新建一个目标比如：
```
flight-control:
   make -c flight-control
PHONY +=battery clean h264 flight-control
```
再执行
```
make flight-control
```


本工程文件目录树如下：











```
mysample
├─ .vscode
│  ├─ c_cpp_properties.json
│  └─ settings.json
├─ README.md
├─ battery
│  ├─ CMakeLists.txt
│  ├─ Makefile
│  ├─ Makefile_bak
│  ├─ UserConfig.txt
│  ├─ battary
│  └─ main.cpp
├─ build
├─ common
│  ├─ UserConfig.txt
│  ├─ dji_linux_environment.cpp
│  ├─ dji_linux_environment.hpp
│  ├─ dji_linux_helpers.cpp
│  └─ dji_linux_helpers.hpp
├─ core
│  ├─ inc
│  │  ├─ camera_manager_async_sample.hpp
│  │  ├─ camera_manager_sync_sample.hpp
│  │  ├─ flight_sample.hpp
│  │  ├─ gimbal_manager_async_sample.hpp
│  │  ├─ gimbal_manager_sync_sample.hpp
│  │  ├─ hms_sample.hpp
│  │  └─ waypoint_v2_sample.hpp
│  └─ src
│     ├─ camera_manager_async_sample.cpp
│     ├─ camera_manager_sync_sample.cpp
│     ├─ flight_sample.cpp
│     ├─ gimbal_manager_async_sample.cpp
│     ├─ gimbal_manager_sync_sample.cpp
│     ├─ hms_sample.cpp
│     └─ waypoint_v2_sample.cpp
├─ makefile
├─ osdk-core
│  ├─ CMakeLists.txt
│  ├─ README.md
│  ├─ advanced-sensing
│  │  ├─ CMakeLists.txt
│  │  ├─ api
│  │  │  ├─ inc
│  │  │  │  ├─ dji_advanced_sensing.hpp
│  │  │  │  ├─ dji_liveview.hpp
│  │  │  │  ├─ dji_liveview_impl.hpp
│  │  │  │  ├─ dji_perception.hpp
│  │  │  │  └─ dji_perception_impl.hpp
│  │  │  └─ src
│  │  │     ├─ dji_advanced_sensing.cpp
│  │  │     ├─ dji_liveview.cpp
│  │  │     ├─ dji_liveview_impl.cpp
│  │  │     ├─ dji_perception.cpp
│  │  │     └─ dji_perception_impl.cpp
│  │  ├─ camera_stream
│  │  │  ├─ src
│  │  │  │  ├─ dji_camera_image.hpp
│  │  │  │  ├─ dji_camera_image_handler.cpp
│  │  │  │  ├─ dji_camera_image_handler.hpp
│  │  │  │  ├─ dji_camera_stream.cpp
│  │  │  │  ├─ dji_camera_stream.hpp
│  │  │  │  ├─ dji_camera_stream_decoder.cpp
│  │  │  │  ├─ dji_camera_stream_decoder.hpp
│  │  │  │  ├─ dji_camera_stream_link.cpp
│  │  │  │  └─ dji_camera_stream_link.hpp
│  │  │  └─ udt
│  │  │     └─ src
│  │  │        ├─ api.cpp
│  │  │        ├─ api.h
│  │  │        ├─ buffer.cpp
│  │  │        ├─ buffer.h
│  │  │        ├─ cache.cpp
│  │  │        ├─ cache.h
│  │  │        ├─ ccc.cpp
│  │  │        ├─ ccc.h
│  │  │        ├─ channel.cpp
│  │  │        ├─ channel.h
│  │  │        ├─ common.cpp
│  │  │        ├─ common.h
│  │  │        ├─ core.cpp
│  │  │        ├─ core.h
│  │  │        ├─ epoll.cpp
│  │  │        ├─ epoll.h
│  │  │        ├─ list.cpp
│  │  │        ├─ list.h
│  │  │        ├─ md5.cpp
│  │  │        ├─ md5.h
│  │  │        ├─ packet.cpp
│  │  │        ├─ packet.h
│  │  │        ├─ queue.cpp
│  │  │        ├─ queue.h
│  │  │        ├─ udt.h
│  │  │        ├─ window.cpp
│  │  │        └─ window.h
│  │  ├─ ori-osdk-core
│  │  │  ├─ cmake-modules
│  │  │  │  ├─ DJIOSDKConfig.cmake
│  │  │  │  ├─ DJIOSDKConfig.cmake.in
│  │  │  │  ├─ DJIOSDKConfigVersion.cmake
│  │  │  │  ├─ DJIOSDKConfigVersion.cmake.in
│  │  │  │  ├─ DownloadProject
│  │  │  │  │  ├─ DownloadProject.CMakeLists.cmake.in
│  │  │  │  │  └─ DownloadProject.cmake
│  │  │  │  ├─ External_AdvancedSensing.cmake
│  │  │  │  ├─ External_WaypointV2Core.cmake
│  │  │  │  ├─ FindAdvancedSensing.cmake
│  │  │  │  ├─ FindFFMPEG.cmake
│  │  │  │  ├─ FindLibUSB.cmake
│  │  │  │  └─ FindWaypt2Core.cmake
│  │  │  ├─ hal
│  │  │  │  ├─ inc
│  │  │  │  │  ├─ dji_hard_driver.hpp
│  │  │  │  │  ├─ dji_memory.hpp
│  │  │  │  │  ├─ dji_platform_manager.hpp
│  │  │  │  │  └─ dji_thread_manager.hpp
│  │  │  │  └─ src
│  │  │  │     ├─ dji_hard_driver.cpp
│  │  │  │     ├─ dji_memory.cpp
│  │  │  │     ├─ dji_platform_manager.cpp
│  │  │  │     └─ dji_thread_manager.cpp
│  │  │  ├─ platform
│  │  │  │  ├─ Readme.md
│  │  │  │  ├─ default
│  │  │  │  │  ├─ inc
│  │  │  │  │  │  └─ dji_memory_default.hpp
│  │  │  │  │  ├─ readme.md
│  │  │  │  │  └─ src
│  │  │  │  │     └─ dji_memory_default.cpp
│  │  │  │  └─ linux
│  │  │  │     ├─ inc
│  │  │  │     │  ├─ linux_serial_device.hpp
│  │  │  │     │  ├─ posix_thread.hpp
│  │  │  │     │  └─ posix_thread_manager.hpp
│  │  │  │     └─ src
│  │  │  │        ├─ linux_serial_device.cpp
│  │  │  │        └─ posix_thread_manager.cpp
│  │  │  ├─ protocol
│  │  │  │  ├─ inc
│  │  │  │  │  ├─ dji_aes.hpp
│  │  │  │  │  ├─ dji_crc.hpp
│  │  │  │  │  ├─ dji_open_protocol.hpp
│  │  │  │  │  └─ dji_protocol_base.hpp
│  │  │  │  └─ src
│  │  │  │     ├─ dji_aes.cpp
│  │  │  │     ├─ dji_open_protocol.cpp
│  │  │  │     └─ dji_protocol_base.cpp
│  │  │  └─ utility
│  │  │     ├─ inc
│  │  │     │  ├─ dji_circular_buffer.hpp
│  │  │     │  ├─ dji_macros.hpp
│  │  │     │  └─ dji_singleton.hpp
│  │  │     └─ src
│  │  │        ├─ dji_circular_buffer.cpp
│  │  │        └─ dji_singleton.cpp
│  │  ├─ platform
│  │  │  ├─ inc
│  │  │  │  └─ linux_usb_device.hpp
│  │  │  └─ src
│  │  │     └─ linux_usb_device.cpp
│  │  └─ protocol
│  │     ├─ inc
│  │     │  └─ dji_advanced_sensing_protocol.hpp
│  │     └─ src
│  │        └─ dji_advanced_sensing_protocol.cpp
│  ├─ api
│  │  ├─ inc
│  │  │  ├─ dji_ack.hpp
│  │  │  ├─ dji_battery.hpp
│  │  │  ├─ dji_battery_impl.hpp
│  │  │  ├─ dji_broadcast.hpp
│  │  │  ├─ dji_camera.hpp
│  │  │  ├─ dji_camera_manager.hpp
│  │  │  ├─ dji_command.hpp
│  │  │  ├─ dji_control.hpp
│  │  │  ├─ dji_error.hpp
│  │  │  ├─ dji_flight_controller.hpp
│  │  │  ├─ dji_gimbal.hpp
│  │  │  ├─ dji_gimbal_manager.hpp
│  │  │  ├─ dji_hardware_sync.hpp
│  │  │  ├─ dji_hms.hpp
│  │  │  ├─ dji_hms_impl.hpp
│  │  │  ├─ dji_hms_internal.hpp
│  │  │  ├─ dji_hotpoint.hpp
│  │  │  ├─ dji_legacy_linker.hpp
│  │  │  ├─ dji_mfio.hpp
│  │  │  ├─ dji_mission_base.hpp
│  │  │  ├─ dji_mission_manager.hpp
│  │  │  ├─ dji_mission_type.hpp
│  │  │  ├─ dji_mobile_device.hpp
│  │  │  ├─ dji_payload_device.hpp
│  │  │  ├─ dji_psdk_manager.hpp
│  │  │  ├─ dji_status.hpp
│  │  │  ├─ dji_subscription.hpp
│  │  │  ├─ dji_telemetry.hpp
│  │  │  ├─ dji_telemetry_doc.hpp
│  │  │  ├─ dji_type.hpp
│  │  │  ├─ dji_vehicle.hpp
│  │  │  ├─ dji_vehicle_callback.hpp
│  │  │  ├─ dji_version.hpp
│  │  │  ├─ dji_waypoint.hpp
│  │  │  ├─ dji_waypoint_v2.hpp
│  │  │  └─ dji_waypoint_v2_action.hpp
│  │  └─ src
│  │     ├─ dji_ack.cpp
│  │     ├─ dji_battery.cpp
│  │     ├─ dji_battery_impl.cpp
│  │     ├─ dji_broadcast.cpp
│  │     ├─ dji_camera.cpp
│  │     ├─ dji_camera_manager.cpp
│  │     ├─ dji_command.cpp
│  │     ├─ dji_control.cpp
│  │     ├─ dji_error.cpp
│  │     ├─ dji_flight_controller.cpp
│  │     ├─ dji_gimbal.cpp
│  │     ├─ dji_gimbal_manager.cpp
│  │     ├─ dji_hardware_sync.cpp
│  │     ├─ dji_hms.cpp
│  │     ├─ dji_hms_impl.cpp
│  │     ├─ dji_hms_internal.cpp
│  │     ├─ dji_hotpoint.cpp
│  │     ├─ dji_legacy_linker.cpp
│  │     ├─ dji_mfio.cpp
│  │     ├─ dji_mission_manager.cpp
│  │     ├─ dji_mobile_device.cpp
│  │     ├─ dji_payload_device.cpp
│  │     ├─ dji_psdk_manager.cpp
│  │     ├─ dji_subscription.cpp
│  │     ├─ dji_vehicle.cpp
│  │     ├─ dji_version.cpp
│  │     ├─ dji_waypoint.cpp
│  │     └─ dji_waypoint_v2.cpp
│  ├─ config_example.json
│  ├─ linker
│  │  ├─ STM32
│  │  │  ├─ inc
│  │  │  │  ├─ dji_internal_command.hpp
│  │  │  │  ├─ dji_linker.hpp
│  │  │  │  ├─ mop.h
│  │  │  │  ├─ mop_entry_osdk.h
│  │  │  │  ├─ mop_osal.h
│  │  │  │  ├─ mop_platform.h
│  │  │  │  ├─ osdk_channel.h
│  │  │  │  ├─ osdk_command.h
│  │  │  │  ├─ osdk_command_instance.h
│  │  │  │  ├─ osdk_console_color.h
│  │  │  │  ├─ osdk_device_id.h
│  │  │  │  ├─ osdk_list.h
│  │  │  │  ├─ osdk_logger.h
│  │  │  │  ├─ osdk_logger_internal.h
│  │  │  │  ├─ osdk_md5.h
│  │  │  │  ├─ osdk_module_name.h
│  │  │  │  ├─ osdk_osal.h
│  │  │  │  ├─ osdk_platform.h
│  │  │  │  ├─ osdk_protocol.h
│  │  │  │  ├─ osdk_protocol_common.h
│  │  │  │  ├─ osdk_root_task.h
│  │  │  │  ├─ osdk_routetable.h
│  │  │  │  ├─ osdk_typedef.h
│  │  │  │  └─ osdk_work.h
│  │  │  └─ lib
│  │  │     └─ sdk-linker.lib
│  │  ├─ armv7
│  │  │  ├─ inc
│  │  │  │  ├─ dji_internal_command.hpp
│  │  │  │  ├─ dji_linker.hpp
│  │  │  │  ├─ mop.h
│  │  │  │  ├─ mop_entry_osdk.h
│  │  │  │  ├─ mop_osal.h
│  │  │  │  ├─ mop_platform.h
│  │  │  │  ├─ osdk_channel.h
│  │  │  │  ├─ osdk_command.h
│  │  │  │  ├─ osdk_command_instance.h
│  │  │  │  ├─ osdk_console_color.h
│  │  │  │  ├─ osdk_device_id.h
│  │  │  │  ├─ osdk_list.h
│  │  │  │  ├─ osdk_logger.h
│  │  │  │  ├─ osdk_logger_internal.h
│  │  │  │  ├─ osdk_md5.h
│  │  │  │  ├─ osdk_module_name.h
│  │  │  │  ├─ osdk_osal.h
│  │  │  │  ├─ osdk_platform.h
│  │  │  │  ├─ osdk_protocol.h
│  │  │  │  ├─ osdk_protocol_common.h
│  │  │  │  ├─ osdk_root_task.h
│  │  │  │  ├─ osdk_routetable.h
│  │  │  │  ├─ osdk_typedef.h
│  │  │  │  └─ osdk_work.h
│  │  │  └─ lib
│  │  │     └─ libdji-linker.a
│  │  ├─ armv8
│  │  │  ├─ inc
│  │  │  │  ├─ dji_internal_command.hpp
│  │  │  │  ├─ dji_linker.hpp
│  │  │  │  ├─ mop.h
│  │  │  │  ├─ mop_entry_osdk.h
│  │  │  │  ├─ mop_osal.h
│  │  │  │  ├─ mop_platform.h
│  │  │  │  ├─ osdk_channel.h
│  │  │  │  ├─ osdk_command.h
│  │  │  │  ├─ osdk_command_instance.h
│  │  │  │  ├─ osdk_console_color.h
│  │  │  │  ├─ osdk_device_id.h
│  │  │  │  ├─ osdk_list.h
│  │  │  │  ├─ osdk_logger.h
│  │  │  │  ├─ osdk_logger_internal.h
│  │  │  │  ├─ osdk_md5.h
│  │  │  │  ├─ osdk_module_name.h
│  │  │  │  ├─ osdk_osal.h
│  │  │  │  ├─ osdk_platform.h
│  │  │  │  ├─ osdk_protocol.h
│  │  │  │  ├─ osdk_protocol_common.h
│  │  │  │  ├─ osdk_root_task.h
│  │  │  │  ├─ osdk_routetable.h
│  │  │  │  ├─ osdk_typedef.h
│  │  │  │  └─ osdk_work.h
│  │  │  └─ lib
│  │  │     └─ libdji-linker.a
│  │  └─ x86
│  │     ├─ inc
│  │     │  ├─ dji_internal_command.hpp
│  │     │  ├─ dji_linker.hpp
│  │     │  ├─ mop.h
│  │     │  ├─ mop_entry_osdk.h
│  │     │  ├─ mop_osal.h
│  │     │  ├─ mop_platform.h
│  │     │  ├─ osdk_channel.h
│  │     │  ├─ osdk_command.h
│  │     │  ├─ osdk_command_instance.h
│  │     │  ├─ osdk_console_color.h
│  │     │  ├─ osdk_device_id.h
│  │     │  ├─ osdk_list.h
│  │     │  ├─ osdk_logger.h
│  │     │  ├─ osdk_logger_internal.h
│  │     │  ├─ osdk_md5.h
│  │     │  ├─ osdk_module_name.h
│  │     │  ├─ osdk_osal.h
│  │     │  ├─ osdk_platform.h
│  │     │  ├─ osdk_protocol.h
│  │     │  ├─ osdk_protocol_common.h
│  │     │  ├─ osdk_root_task.h
│  │     │  ├─ osdk_routetable.h
│  │     │  ├─ osdk_typedef.h
│  │     │  └─ osdk_work.h
│  │     └─ lib
│  │        ├─ dji_aes.c.o
│  │        ├─ dji_internal_command.cpp.o
│  │        ├─ dji_linker.cpp.o
│  │        ├─ libdji-linker.a
│  │        ├─ linker.s
│  │        ├─ mop.c.o
│  │        ├─ mop_buffer.c.o
│  │        ├─ mop_entry_osdk.c.o
│  │        ├─ mop_flow_controller.c.o
│  │        ├─ mop_link_layer.c.o
│  │        ├─ mop_net_layer.c.o
│  │        ├─ mop_osal_osdk.c.o
│  │        ├─ mop_trans_layer.c.o
│  │        ├─ osdk_buffer.c.o
│  │        ├─ osdk_channel.c.o
│  │        ├─ osdk_command.c.o
│  │        ├─ osdk_command_instance.c.o
│  │        ├─ osdk_crc.c.o
│  │        ├─ osdk_hal.c.o
│  │        ├─ osdk_list.c.o
│  │        ├─ osdk_logger.c.o
│  │        ├─ osdk_md5.c.o
│  │        ├─ osdk_msgq.c.o
│  │        ├─ osdk_osal.c.o
│  │        ├─ osdk_protocol.c.o
│  │        ├─ osdk_protocol_sdk.c.o
│  │        ├─ osdk_protocol_usbmc.c.o
│  │        ├─ osdk_protocol_v1.c.o
│  │        ├─ osdk_root_task.c.o
│  │        ├─ osdk_str.c.o
│  │        ├─ osdk_unit.c.o
│  │        └─ osdk_work.c.o
│  ├─ logger
│  │  ├─ inc
│  │  │  └─ dji_log.hpp
│  │  └─ src
│  │     └─ dji_log.cpp
│  ├─ modules
│  │  ├─ inc
│  │  │  ├─ filemgr
│  │  │  │  ├─ dji_file_mgr.hpp
│  │  │  │  ├─ dji_file_mgr_define.hpp
│  │  │  │  └─ impl
│  │  │  │     ├─ commondatarangehandler.h
│  │  │  │     ├─ dji_file_mgr_impl.hpp
│  │  │  │     ├─ dji_file_mgr_internal_define.hpp
│  │  │  │     ├─ downloadbufferqueue.h
│  │  │  │     └─ mmap_file_buffer.hpp
│  │  │  ├─ firewall
│  │  │  │  ├─ osdk_firewall.hpp
│  │  │  │  └─ osdk_policy.hpp
│  │  │  ├─ flight
│  │  │  │  ├─ dji_flight_actions_module.hpp
│  │  │  │  ├─ dji_flight_assistant_module.hpp
│  │  │  │  ├─ dji_flight_joystick_module.hpp
│  │  │  │  └─ dji_flight_link.hpp
│  │  │  ├─ mop
│  │  │  │  ├─ dji_mop_client.hpp
│  │  │  │  ├─ dji_mop_define.hpp
│  │  │  │  ├─ dji_mop_pipeline.hpp
│  │  │  │  ├─ dji_mop_pipeline_manager_base.hpp
│  │  │  │  └─ dji_mop_server.hpp
│  │  │  └─ payload
│  │  │     ├─ dji_camera_module.hpp
│  │  │     ├─ dji_gimbal_module.hpp
│  │  │     ├─ dji_payload_base.hpp
│  │  │     ├─ dji_payload_link.hpp
│  │  │     └─ dji_psdk_module.hpp
│  │  └─ src
│  │     ├─ filemgr
│  │     │  ├─ dji_file_mgr.cpp
│  │     │  ├─ dji_file_mgr_define.cpp
│  │     │  └─ impl
│  │     │     ├─ commondatarangehandler.cpp
│  │     │     ├─ dji_file_mgr_impl.cpp
│  │     │     ├─ downloadbufferqueue.cpp
│  │     │     └─ mmap_file_buffer.cpp
│  │     ├─ firewall
│  │     │  ├─ osdk_firewall.cpp
│  │     │  ├─ psdk_md5.c
│  │     │  └─ psdk_md5.h
│  │     ├─ flight
│  │     │  ├─ dji_flight_actions_module.cpp
│  │     │  ├─ dji_flight_assistant_module.cpp
│  │     │  ├─ dji_flight_joystick_module.cpp
│  │     │  └─ dji_flight_link.cpp
│  │     ├─ mop
│  │     │  ├─ dji_mop_client.cpp
│  │     │  ├─ dji_mop_define.cpp
│  │     │  ├─ dji_mop_pipeline.cpp
│  │     │  ├─ dji_mop_pipeline_manager_base.cpp
│  │     │  └─ dji_mop_server.cpp
│  │     └─ payload
│  │        ├─ dji_camera_module.cpp
│  │        ├─ dji_gimbal_module.cpp
│  │        ├─ dji_payload_base.cpp
│  │        ├─ dji_payload_link.cpp
│  │        └─ dji_psdk_module.cpp
│  ├─ platform
│  │  ├─ inc
│  │  │  └─ dji_platform.hpp
│  │  └─ src
│  │     └─ dji_platform.cpp
│  └─ utility
│     ├─ inc
│     │  ├─ dji_macros.hpp
│     │  ├─ dji_setup_helpers.hpp
│     │  └─ dji_singleton.hpp
│     └─ src
│        ├─ dji_setup_helpers.cpp
│        └─ dji_singleton.cpp
└─ platform
   └─ linux
      ├─ CMakeLists.txt
      ├─ advanced-sensing
      │  ├─ CMakeLists.txt
      │  ├─ camera_h264_callback_sample
      │  │  ├─ CMakeLists.txt
      │  │  └─ main.cpp
      │  ├─ camera_stream_callback_sample
      │  │  ├─ CMakeLists.txt
      │  │  └─ camera-stream-callback-sample.cpp
      │  └─ camera_stream_poll_sample
      │     ├─ CMakeLists.txt
      │     └─ camera-stream-poll-sample.cpp
      ├─ battery
      │  ├─ CMakeLists.txt
      │  └─ main.cpp
      ├─ common
      │  ├─ UserConfig.txt
      │  ├─ dji_linux_environment.cpp
      │  ├─ dji_linux_environment.hpp
      │  ├─ dji_linux_helpers.cpp
      │  └─ dji_linux_helpers.hpp
      ├─ config_tool
      │  ├─ CMakeLists.txt
      │  ├─ config_tool.cpp
      │  └─ config_tool.hpp
      ├─ flight-control
      │  ├─ CMakeLists.txt
      │  ├─ flight_control_sample.cpp
      │  ├─ flight_control_sample.hpp
      │  └─ main.cpp
      ├─ hal
      │  ├─ hotplug
      │  │  ├─ osdkhal_hotplug.c
      │  │  └─ osdkhal_hotplug.h
      │  ├─ osdkhal_linux.c
      │  └─ osdkhal_linux.h
      ├─ hms
      │  ├─ CMakeLists.txt
      │  └─ main.cpp
      ├─ logging
      │  ├─ CMakeLists.txt
      │  ├─ logging_sample.cpp
      │  ├─ logging_sample.hpp
      │  └─ main.cpp
      ├─ mfio
      │  ├─ CMakeLists.txt
      │  ├─ main.cpp
      │  ├─ mfio_sample.cpp
      │  └─ mfio_sample.hpp
      ├─ missions
      │  ├─ CMakeLists.txt
      │  ├─ main.cpp
      │  ├─ mission_sample.cpp
      │  ├─ mission_sample.hpp
      │  └─ waypoint_v2_main.cpp
      ├─ mobile
      │  ├─ CMakeLists.txt
      │  ├─ main.cpp
      │  ├─ mobile_sample.cpp
      │  └─ mobile_sample.hpp
      ├─ mop
      │  ├─ CMakeLists.txt
      │  ├─ mop_sample_simple_protocol.hpp
      │  ├─ om_download_sample.cpp
      │  ├─ op_download_sample.cpp
      │  ├─ op_upload_sample.cpp
      │  └─ telemetryLogFile.txt
      ├─ osal
      │  ├─ osdkosal_linux.c
      │  └─ osdkosal_linux.h
      ├─ payload-3rd-party
      │  ├─ CMakeLists.txt
      │  ├─ main.cpp
      │  ├─ payload-control-sample.cpp
      │  └─ payload-control-sample.hpp
      ├─ payloads
      │  ├─ CMakeLists.txt
      │  ├─ download_sample.cpp
      │  ├─ main_async.cpp
      │  └─ main_sync.cpp
      ├─ telemetry
      │  ├─ CMakeLists.txt
      │  ├─ main.cpp
      │  ├─ telemetry_sample.cpp
      │  └─ telemetry_sample.hpp
      └─ time-sync
         ├─ CMakeLists.txt
         ├─ time_sync_callback_sample.cpp
         └─ time_sync_poll_sample.cpp

```