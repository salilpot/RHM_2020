#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <shunyaInterfaces.h>
#include <functions.h>
#include <simple-mode.h>
#include <advance-mode.h>

#include <curl/curl.h>

int main(void)
{

	debugLogOn();
	initLib();

	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();

        float temp = getCelsius();
	time_t seconds;

	char* msg = (char*)malloc(38*sizeof(char) + 40*sizeof(char));

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.31.119:8086/write?db=test_db");
		while(1) {
			temp = getCelsius();
			seconds = time(NULL);
			printf("\nTIME: %lld\n", seconds);
			sprintf(msg, "patient,name=pat1,hospital=hosp1 temp=%.2f %ld", temp, seconds);
        		//printf("Temperature = %.2f deg C \n", temp);
			printf("%s\n", msg);
			delay(1000);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform failed: %s\n", curl_easy_strerror(res));
				break;
			}
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}
