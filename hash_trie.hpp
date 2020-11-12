#ifndef OPEN_ADRESS__HASH_TRIE_HPP_
#define OPEN_ADRESS__HASH_TRIE_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "hashing.hpp"

namespace kuroda {

class hash_trie{
kuroda::HashTable ht;
// TODO: Needs implementation by yourself.
public:
hash_trie(){
}
static constexpr uint8_t kLeafChar = 0;
/*
void hash_try(const std::vector<std::string>& str_list) {
    // Create hash_table
    //std::vector<std::string> str_list;
    //std::vector<uint8_t> code;
    int word_number = 0;
    std::vector<std::unordered_map<uint8_t, int>> table(1);
    for (auto& keys : str_list) {
        int node = 0;
        int s,t = 0;
        word_number++;
        //std::cout << "####################################################" << std::endl;
        std::cout << word_number << "  key_word  " << keys << std::endl;
        for (uint8_t c : keys){
            //int hashIndex = 0;
            //std::cout << c << std::endl;
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
                key = create_key(s,c);
                value = t;
                ht.set(key,value);
                std::cout << "key" << key << std::endl;
                //std::cout << "value" << value << std::endl;
                //ハッシュテーブルにセット 

            }
        }
        //最後#へ遷移する
        if (table[node].count(kLeafChar) == 0){
            int key,value;//key→遷移文字、遷移元 value→遷移先でハッシュテーブルに保存
                table.emplace_back();//1個余裕を持たせる
                key = create_key(node,kLeafChar);
                value = table.size();
                ht.set(key,value);
                table[node][kLeafChar] = 1;
                std::cout << "------word_end--------" << std::endl;
        }    
        
    }
    

    std::cout << "hashtable_complete" <<"\n";
    std::cout << table.size() <<"\n";
    ht.display();//ハッシュテーブルを表示
}*/
private:
int create_key(int node, uint8_t c) const {
    assert(node < (1u<<24));
    return node << 8 | c;
}
public:
bool contains(const std::string& str){//文字列strが辞書にあるかどうか検索
    int node = 0; // root
    for (uint8_t c : str) {
        int new_node = ht.get(create_key(node, c));
        if(new_node == HashTable::invalid){
            return false;
        }
        node = new_node;
    }
    return ht.get(create_key(node,kLeafChar)) !=  HashTable::invalid;
}
private:
int node_count = 0;
public:
void insert(const std::string& str){ // 文字列strを辞書に追加
    int node = 0;
    for (uint8_t c : str) {
        if(ht.get(create_key(node,c)) !=  HashTable::invalid){
            node = ht.get(create_key(node,c));
        }
        else{
             //setする(new_nodeの登場)
            node_count++;
            auto new_node = node_count;
            int key = create_key(node,c);
            int value = new_node;
            ht.set(key,value);
            node = new_node;
        }

    }
    node_count++;
    ht.set(create_key(node,kLeafChar),node_count);//終端文字の遷移を格納
    int a = ht.get(create_key(node, kLeafChar));
   // ht.display();

}
/*留意点
・ここで呼び出すのはsetとgetのみ
・setで(key,value)をhashIndex番目に保存
・おそらく探索を行うときにgetを使う(keyからvalueの情報を引き出す)*/
};

}

#endif //OPEN_ADRESS__HASHING_HPP_
/*留意点
・ここで呼び出すのはsetとgetのみ
・setで(key,value)をhashIndex番目に保存
・おそらく探索を行うときにgetを使う(keyからvalueの情報を引き出す)*/