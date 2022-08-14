#include <curl/curl.h>
#include "curl_a_website.h"

uint8_t curl_a_website(const char *url) {
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
#ifdef __ANDROID__
    // For https requests, you need to specify the ca-bundle path
    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,1);
    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,1);
    //curl_easy_setopt(curl, CURLOPT_CAINFO, CA_BUNDLE_PATH);
    //curl_easy_setopt(curl, CURLOPT_PROXY, "http://192.168.72.2");
#endif

    uint8_t success = 0;
    CURLcode response = curl_easy_perform(curl);

    if (response == CURLE_OK) {
        success = 1;
    }

    curl_easy_cleanup(curl);

    return success;
}

const char* get_curl_version() {
    curl_version_info_data* data = curl_version_info(CURLVERSION_NOW);
    return data->version;
}
// "C:\Program Files\Git\usr\bin\openssl.exe" x509 -text -inform DER -in burp.der -outform PEM -out burp.pem