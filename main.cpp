#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Download.h"
#include "ScrapFont.h"

int main(int argc, char *argv[]) {
  std::string res =
      site_get_request("https://www.nerdfonts.com/font-downloads");
  std::regex regexp("https.*zip");
  std::istringstream pageLines(res);
  std::sregex_iterator iter(res.begin(), res.end(), regexp);
  std::sregex_iterator endreg;

  std::map<std::string, std::string> file_src_dest_list;

  std::string dl_folder = "./downloads/";
  std::string dl_folder_file_name = "";
  std::string match_str = "";
  int success = 0;
  std::regex file_name_match("[a-zA-Z0-9]*\\.zip");
  std::smatch sm, tempMatch;
  int skip = 0;
  for (std::sregex_iterator i = iter; i != endreg; ++i) {
    tempMatch = *i;
    if (skip % 2 == 0) {
      match_str = tempMatch.str();
      std::regex_search(match_str, sm, file_name_match);
      dl_folder_file_name = dl_folder + sm.str();
      std::cout << match_str << std::endl;
      file_src_dest_list[match_str] = dl_folder_file_name;
      dl_folder_file_name = "";
    } else {
      dl_folder_file_name = "";
    }
    skip++;
  }

  std::vector<std::thread> threads;
  std::map<std::string, std::string>::iterator itr = file_src_dest_list.begin();
  while (itr != file_src_dest_list.end()) {
    threads.push_back(
        std::thread(download, itr->first.c_str(), itr->second.c_str()));
    ++itr;
  }

  for (auto &th : threads) {
    th.join();
  }
  return 0;
}
