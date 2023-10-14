#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "ScrapFont.h"
int main(int argc, char *argv[]) {
  std::string res =
      site_get_request("https://www.nerdfonts.com/font-downloads");
  std::ofstream ResFile("respons.txt");
  ResFile << res;
  ResFile.close();
  std::cout << res << std::endl;
  return 0;
}
