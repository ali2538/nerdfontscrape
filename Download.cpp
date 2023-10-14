#include <cstddef>
#include <cstdio>
#include <string>

#include "include/curl/curl.h"
#include "include/curl/easy.h"
static size_t save_file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t saved = std::fwrite(ptr, size, nmemb, stream);
  return saved;
}

int download(const char *dl_link, const char *dl_location) {
  CURL *curl;
  FILE *dfile;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    dfile = std::fopen(dl_location, "wb");
    curl_easy_setopt(curl, CURLOPT_URL, dl_link);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, dfile);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      return 1;
    }
    curl_easy_cleanup(curl);
    std::fclose(dfile);
  }

  return 0;
}
