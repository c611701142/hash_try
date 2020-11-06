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
private:
std::vector<uint8_t> node_count;
std::vector<std::unordered_map<uint8_t, int>> table;
public:
hash_trie(){
    node_count[0]; 
    table.resize(1);
}
public:
void hash_try(const std::vector<std::string> str_list) {
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
                std::cout << "node" << node << std::endl;
                std::cout << "new_node appear!!!" << std::endl;
                std::cout << "new_node" << new_node << std::endl;
                s = node;t = new_node;
                node = new_node;
                key = s << 8 | c;
                value = t;
                ht.set(key,value);
                //std::cout << "key" << key << std::endl;
                //std::cout << "value" << value << std::endl;
                //ハッシュテーブルにセット 

            }
        }
        if (table[node].count(kLeafChar) == 0){
                table.emplace_back();//1個余裕を持たせる
                table[node][kLeafChar] = 1;
                //std::cout << "------word_end--------" << std::endl;
        }    
        
    }
    

    std::cout << "hashtable_complete" <<"\n";
    std::cout << table.size() <<"\n";
    //ht.display();//ハッシュテーブルを表示
}

bool contains(const std::string& str) const {//文字列strが辞書にあるかどうか検索
        int node = 0; // root
        for (uint8_t c : str) {
            if(node_count[node] == c){
                return true;
            }
            else{
                return true;
            }
        }
        return true;
    //遷移条件で確かめていた。
}

int word = 0;//単語数
/*
void insert(const std::string& str){ // 文字列strを辞書に追加
    int node = 0;
    int s,t = 0;
    word++;
    std::cout << "  key_word  " << str << std::endl;
        for (uint8_t c : str){
            std::cout << c << std::endl;//s4.txtの時消す
            std::cout << word << std::endl;
            int key,value;//key→遷移文字、遷移元 value→遷移先でハッシュテーブルに保存
            if(word == 1){//最初の単語は先頭からnode_countに入れていく
                node_count.emplace_back(c);
                auto new_node = node_count.size();
                std::cout << "new_node appear!!!" << std::endl;
                std::cout << "node" << node << std::endl;
                std::cout << "new_node" << new_node << std::endl;
                std::cout << "++++++++++++++++++++++++++++" << std::endl;
                s = node;t = new_node;
                node = new_node;
                key = s << 8 | c;
                value = t;
                ht.set(key,value);
                //std::cout << "key" << key << std::endl;
                //std::cout << "value" << value << std::endl;
                //ハッシュテーブルにセット 
            }
            else if(word > 1){//２つ目以降
                if (node_count[node] != c) { //新しいノードが出てきたとき
                    node_count.emplace_back(c);//格納
                    auto new_node = node_count.size();
                    std::cout << "new_node appear!!!" << std::endl;
                    std::cout << "node" << node << std::endl;
                    std::cout << "new_node" << new_node << std::endl;
                    std::cout << "++++++++++++++++++++++++++++" << std::endl;
                    s = node;t = new_node;
                    node = new_node;
                    key = s << 8 | c;
                    value = t;
                    ht.set(key,value);
                    //std::cout << "key" << key << std::endl;
                    //std::cout << "value" << value << std::endl;
                    //ハッシュテーブルにセット 
                } 
                else{//接頭辞の共有
                    node++;
                    std::cout << "common spell" << std::endl;
                }
            }
        }
        if (node_count[node] == kLeafChar){
            std::cout << "------word_end--------" << std::endl;
            //node_count.emplace_back();//終端文字格納

        }    
    std::cout << node_count.size() << std::endl;
    //ht.display();//ハッシュテーブルを表示
}*/
public:
void insert(const std::string& str){ // 文字列strを辞書に追加
    int node = 0;
    int s,t = 0;
    std::cout << "  key_word  " << str << std::endl;
        for (uint8_t c : str){
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
                std::cout << "node" << node << std::endl;
                std::cout << "new_node appear!!!" << std::endl;
                std::cout << "new_node" << new_node << std::endl;
                s = node;t = new_node;
                node = new_node;
                key = s << 8 | c;
                value = t;
                ht.set(key,value);
                //std::cout << "key" << key << std::endl;
                //std::cout << "value" << value << std::endl;
                //ハッシュテーブルにセット 

            }
        }
        if (table[node].count(kLeafChar) == 0){
                table.emplace_back();//1個余裕を持たせる
                table[node][kLeafChar] = 1;
                std::cout << "------word_end--------" << std::endl;
        }    
    //ht.display();//ハッシュテーブルを表示
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