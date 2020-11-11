#include <iostream>
#include <vector>
#include <fstream>

#include "hash_trie.hpp"

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
    kuroda::hash_trie ht_try;//ハッシュトライ呼び出し
    //ht_try.hash_try(str_list);//静的トライ １度にすべて渡す (str_list)

    
    for(const std::string &str : str_list) {//配列の単語数
        std::cout << "-----key_word-------" << str << std::endl;
        ht_try.insert(str);//1単語ずつ追加(str)
        bool check = ht_try.contains(str);
        if(check == false){
            std::cout << "failed..." << std::endl;
            //exit(0);//プログラム異常終了
        }
        else{
            std::cout << "OK" << std::endl;
        }
    }
    return 0;//プログラム終了
}
