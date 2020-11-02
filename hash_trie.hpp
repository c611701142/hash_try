#ifndef OPEN_ADRESS__HASH_TRIE_HPP_
#define OPEN_ADRESS__HASH_TRIE_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "hashing.hpp"

using namespace std;

kuroda::HashTable ht;//ハッシュテーブル呼び出し

uint8_t kLeafChar = 0;

namespace kuroda2{

class hash_trie{
// TODO: Needs implementation by yourself.
public:
void hash_try(const std::vector<std::string> str_list) {
    // Create hash_table
    //std::vector<std::string> str_list;
    //std::vector<uint8_t> code;
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
                    //std::cout << "common spell" << std::endl;
                    //std::cout << "node" << node << std::endl;
            } 
            else{//新しいノードが出てきたとき
                auto new_node = table.size();
                table.emplace_back();//1個余裕を持たせる
                table[node][c] = new_node;
                //std::cout << "node" << node << std::endl;
                //std::cout << "new_node appear!!!" << std::endl;
                //std::cout << "new_node" << new_node << std::endl;
                s = node;t = new_node;
                node = new_node;
                key = s << 8 | c;
                value = t;
                ht.set(key,value);
                //std::cout << "key" << key << std::endl;
                std::cout << "value" << value << std::endl;
                //ハッシュテーブルにセット 
            }
          /*今の流れでは、新しいノードがでてハッシュテーブルに格納するたびに、
            ハッシュテーブルの使用割合を計算し(O(n),nはハッシュテーブルの要素数)
            SIZE(初期値)*整数倍ハッシュテーブルを成長させています。
            このままですと、かなりの計算量がかかってしまいます
            hash_percentを求めるところをもう少し工夫したいです
            (s4.txtは1時間以上かかりました)*/

        }
        if (table[node].count(kLeafChar) == 0){
                table[node][kLeafChar] = 1;
                std::cout << "------word_end--------" << std::endl;
        }

        
    }
    std::cout << "hashtable_complete" <<"\n";
    ht.display();//ハッシュテーブルを表示
}
/*留意点
・ここで呼び出すのはsetとvalueのみ
・setで(key,value)をhashIndex番目に保存
・おそらく探索を行うときにgetを使う(keyからvalueの情報を引き出す)*/



};

}

#endif //OPEN_ADRESS__HASHING_HPP_