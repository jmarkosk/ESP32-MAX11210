deps_config := \
	/home/jasonma/esp/esp-idf/components/app_trace/Kconfig \
	/home/jasonma/esp/esp-idf/components/aws_iot/Kconfig \
	/home/jasonma/esp/esp-idf/components/bt/Kconfig \
	/home/jasonma/esp/esp-idf/components/driver/Kconfig \
	/home/jasonma/esp/esp-idf/components/esp32/Kconfig \
	/home/jasonma/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/jasonma/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/jasonma/esp/esp-idf/components/ethernet/Kconfig \
	/home/jasonma/esp/esp-idf/components/fatfs/Kconfig \
	/home/jasonma/esp/esp-idf/components/freertos/Kconfig \
	/home/jasonma/esp/esp-idf/components/heap/Kconfig \
	/home/jasonma/esp/esp-idf/components/libsodium/Kconfig \
	/home/jasonma/esp/esp-idf/components/log/Kconfig \
	/home/jasonma/esp/esp-idf/components/lwip/Kconfig \
	/home/jasonma/esp/esp-idf/components/mbedtls/Kconfig \
	/home/jasonma/esp/esp-idf/components/openssl/Kconfig \
	/home/jasonma/esp/esp-idf/components/pthread/Kconfig \
	/home/jasonma/esp/esp-idf/components/spi_flash/Kconfig \
	/home/jasonma/esp/esp-idf/components/spiffs/Kconfig \
	/home/jasonma/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/jasonma/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/jasonma/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/jasonma/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/jasonma/esp/ESP32-MAX11210/main/Kconfig.projbuild \
	/home/jasonma/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/jasonma/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
