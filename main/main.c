#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "esp_log.h"
// 1. Include some files
#include "driver/adc.h"
#include "esp_adc_cal.h"


void app_main(void)
{
// 2. adc1_config_channel_atten()

	adc1_config_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_11);
	esp_adc_cal_characteristics_t adc1_chars;
	esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
	adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
	int adc_raw = adc1_get_raw(ADC_CHANNEL_0);

	ESP_LOGI("ADC", "ADC_RAW = %d\n", adc_raw);
	while (true) {
		adc_raw = adc1_get_raw(ADC_CHANNEL_0);
		ESP_LOGI("ADC", "ADC_RAW = %d", adc_raw);
		uint32_t adc_mV = esp_adc_cal_raw_to_voltage(adc_raw, &adc1_chars);
		ESP_LOGI("ADC", "ADC(mV) = %d\n", adc_mV);
        sleep(1);
    }
}
