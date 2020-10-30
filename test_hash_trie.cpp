#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "hash_trie.hpp"

kuroda2::hash_trie ht_try;//ハッシュトライ呼び出し

int main(int argc, char* argv[]){
    int num = 0;
    std::cout << "file_number" << "\n";
    std::cin >> num;
    std::string input_name = std::string("s")+char(num+'0')+".txt";
    std::ifstream ifs(input_name);
    if (!ifs) {
        std::cerr<<"File not found input file: "<<input_name<<std::endl;
        exit(0);
    }
    std::vector<std::string> str_list;
    for (std::string s; std::getline(ifs, s);){
        str_list.push_back(s);
    }
  ht_try.hash_try(str_list);
  return 0;//プログラム終了
}
