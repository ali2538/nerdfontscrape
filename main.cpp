#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Download.h"
#include "ScrapFont.h"

int main(int argc, char *argv[]) {
  std::string res =
      site_get_request("https://www.nerdfonts.com/font-downloads");
  // std::ofstream ResFile("respons.txt");
  // ResFile << res;
  // ResFile.close();
  // std::cout << res << std::endl;
  std::regex regexp("https.*zip");
  std::istringstream pageLines(res);
  std::string line;
  std::vector<std::string> links;
  std::sregex_iterator iter(res.begin(), res.end(), regexp);
  std::sregex_iterator endreg;
  // while (iter != endreg) {

  //}
  std::string dl_folder = "./downloads/";
  std::string dl_folder_file_name = "";
  std::string fileName = "";
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
      std::cout << "Found " << dl_folder_file_name << std::endl;
      dl_folder_file_name = "";
    } else {
      dl_folder_file_name = "";
    }
    skip++;
    //    dl_location = dl_location + sm[0].str();
    //    success = download(match_str.c_str(), dl_location.c_str());
    //    if (success == 0) {
    //      std::cout << "File " << sm[0].str() << " downlaoded succefully"
    //                << std::endl;
    //    } else {
    //      std::cout << "File " << sm[0].str() << " could not be downlaoded"
    //                << std::endl;
    //    }
    //    std::cout << match.str() << std::endl;
  }
  return 0;
}
