//
// Created by jsumihiro on 10/11/22.
//

#include "utils.hpp"
#include <fstream>

std::vector<char> LoadBinaryFile(const std::filesystem::path& binPath)
{
  std::ifstream input(binPath, std::ios::binary);
  
  std::vector<char> binBuffer(std::istreambuf_iterator<char>(input), {});
  
  return binBuffer;
}