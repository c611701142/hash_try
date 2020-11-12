#ifndef OPEN_ADRESS__HASHING_HPP_
#define OPEN_ADRESS__HASHING_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

namespace kuroda {

class HashTableInterface {
public:
  virtual int get(int key)const = 0;
  virtual void set(int key, int value) = 0;
};

class HashTable : public HashTableInterface{
// TODO: Needs implementation by yourself.

public:
//ハッシュテーブルの要素数の初期値
static constexpr int null = -1;//データが入っていないことを示す値
static constexpr int dell = -2;//データが入っていたがそれが削除されたことを示す値
static constexpr int invalid = -1;
static constexpr int invalid_key = -1;
static constexpr int default_size = 4;
HashTable(size_t size = default_size) : SIZE(size), hashArray(size), exists(size, false) {}

private://クラスメンバ変数
int SIZE;//ハッシュテーブルの大きさ(初期値)
int hash_use = 0;//ハッシュテーブルの要素の使用数
/* DataItemの定義 */
struct DataItem {
    int key,value;
    DataItem(): key(invalid_key),value(null){}
};
std::vector<DataItem> hashArray;//ハッシュテーブル
std::vector<bool> exists;//空判定配列

/* ハッシュ関数*/
int hashCode(int key)const{
    return key % SIZE;
}

public:
int get(int key)const{
    //get the hash
    
    int hashIndex = hashCode(key);
    while (exists[hashIndex]){
        if (hashArray[hashIndex].key == key)
            return hashArray[hashIndex].value;
        hashIndex++;
        //wrap around the table
        hashIndex %= SIZE;
    }
    return invalid;//ここでは初期値が返る
}
//ハッシュテーブルの中身を
/* 挿入のための関数 */
//ハッシュ値の衝突が発生した場合は、再ハッシュを繰り返して、
//「空状態」バケットを調べていき、空いているバケットを発見したらデータを格納します。
void set(int key, int value){
    int load_factor = hash_use*100/SIZE;
    //std::cout << "before_expand" << load_factor << "%" << std::endl;

    //keyによる探索の期待計算量が、負荷率をqとしてO(1/(1-q))になる
    if(hash_use * 2 >= SIZE){
        expand_resize();
        int load_factor2 = hash_use*100/SIZE;
        //std::cout << "after_expand" << load_factor2 << "%" << std::endl;
    }
    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty or deleted cell
    int collision = 0;//衝突回数 のちにXorshiftで使うかも
    while(exists[hashIndex]){
        //go to next cell
        ++hashIndex;
        ++collision;
        //wrap around the table
        hashIndex %=   SIZE;
        //std::cout << "key = " << key << std::endl;
        //std::cout << "collision = " << collision << std::endl;
    }
    //std::cout << "hashnumber = " << hashIndex << std::endl;
    collision = 0;
    hashArray[hashIndex].value = value;
    hashArray[hashIndex].key = key;
    exists[hashIndex] = true;//使用済みにする
    hash_use++;
}
void display(){
    for(int i = 0; i < SIZE;i++){
        std::cout << i << "    " << exists[i] << "       ";
        std::cout << hashArray[i].key << "->" << hashArray[i].value << std::endl;
    }
}

private:
void expand_resize() {
    HashTable nht(SIZE*2);
    for (int i = 0; i < SIZE; i++) {
        if (!exists[i])
            continue;
        auto [k, v] = hashArray[i];
        nht.set(k, v);//--c++17 
    }
    *this = std::move(nht);
}

};

}
#endif //OPEN_ADRESS__HASHING_HP