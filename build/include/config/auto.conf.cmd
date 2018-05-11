deps_config := \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/app_trace/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/aws_iot/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/bt/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/esp32/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/ethernet/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/fatfs/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/freertos/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/heap/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/libsodium/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/log/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/lwip/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/mbedtls/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/openssl/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/pthread/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/spi_flash/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/spiffs/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/wear_levelling/Kconfig \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/blink/main/Kconfig.projbuild \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/c/Users/JAMA/AppData/Roaming/SPB_Data/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
