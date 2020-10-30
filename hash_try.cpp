#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "hashing.hpp"

using namespace std;

kuroda::HashTable ht;

uint8_t kLeafChar = 0;
static constexpr uint8_t kEmptyCheck = 0xFF;
static constexpr int kEmptyBase = 0xFFFFFFFF;

void hash_try(const std::vector<std::string> str_list) {
    // Create hash_table
    //std::vector<std::string> str_list;
    //std::vector<uint8_t> code;
    int hashIndex = 1;
    std::vector<std::unordered_map<uint8_t, int>> table(1);
    for (auto& keys : str_list) {
        int node = 0;
        int s,t = 0;
        std::cout << "key_word" << keys << std::endl;
        for (uint8_t c : keys){
            //int hashIndex = 0;
            std::cout << c << std::endl;
            int key,value;//key→遷移文字、遷移元 value→遷移先でハッシュテーブルに保存
            if (table[node].count(c) == 1) { // black→blueの時の blまで
                    node = table[node][c];
                    std::cout << "common spell" << std::endl;
                    std::cout << "node" << node << std::endl;
            } 
            else{//新しいノードが出てきたとき
                hashIndex++;
                auto new_node = table.size();
                table.emplace_back();//1個余裕を持たせる
                table[node][c] = new_node;
                std::cout << "node" << node << std::endl;
                std::cout << "new_node appear!!!" << std::endl;
                std::cout << "new_node" << new_node << std::endl;
                s = node;t = new_node;
                node = new_node;
                key = s << 8 | c;
                value = t;
                /*
                hashArray.emplace_back(key,value);
                empty_check.emplace_back(1);*/
                ht.expand();
                ht.set(key,value);
                std::cout << "key" << key << std::endl;
                std::cout << "value" << value << std::endl;
                std::cout << "hashIndex" << hashIndex << std::endl;
                //ハッシュテーブルにセット 
            }
        }
        if (table[node].count(kLeafChar) == 0){
                table[node][kLeafChar] = 1;
                std::cout << "------word_end--------" << std::endl;
        }
        
    }
    std::cout << "hashtable_complete" <<"\n";
}

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
  hash_try(str_list);
  ht.display();
  return 0;//プログラム終了
}
