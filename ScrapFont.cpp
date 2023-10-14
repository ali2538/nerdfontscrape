#include <cstddef>
#include <iostream>
#include <string>

#include "include/curl/curl.h"

std::string site_get_request(std::string url) {
  typedef size_t (*curl_write)(char *, size_t, size_t, std::string *);
  std::string final_response;
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION,
        static_cast<curl_write>([](char *contents, size_t size, size_t nmemb,
                                   std::string *data) -> size_t {
          size_t realSize = size * nmemb;
          if (data == NULL) {
            return 0;
          }
          data->append(contents, realSize);
          return realSize;
        }));
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &final_response);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      return curl_easy_strerror(res);
    }

    curl_easy_cleanup(curl);
  }

  return final_response;
}
