#ifndef OPEN_ADRESS__HASHING_HPP_
#define OPEN_ADRESS__HASHING_HPP_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

namespace kuroda {

class HashTableInterface {
public:
  virtual int const get(int key) = 0;
  virtual void set(int key, int value) = 0;
};

class HashTable : public HashTableInterface{
// TODO: Needs implementation by yourself.
static constexpr int SIZE = 256;
uint8_t kLeafChar = 0;
static constexpr uint8_t kEmptyCheck = 0xFF;
static constexpr int kEmptyBase = 0xFFFFFFFF;
//-------------------------------------------------------------------
/* DataItemの定義 */
public:
struct DataItem {
        int key,value;
        DataItem(int k=0, int v=-1) : key(k),value(v){}
    };
std::vector<DataItem> hashArray = {};
std::vector<bool> empty_check = {};
HashTable(){
};

/* ハッシュ関数の定義 */
int hashCode(int key){
    return key % SIZE;
}

/* 検索のための関数 */
/* liner Probingを使っているのでそれに合わせた検索を実装です。 */
int const get(int key){
    //get the hash
    
    int hashIndex = hashCode(key);
    //return hashArray[hashIndex].data;
    //move in array until an empty
    
    while (empty_check[key] == 1){//要素が使用済みになるまで
        if (hashArray[hashIndex].key == key)
            return hashArray[hashIndex].value;
            //ここでは256のあまりが返る
        hashIndex++;

        //wrap around the table
        hashIndex %= SIZE;
    }
    return hashArray[hashIndex].value;//ここでは初期値が返る
}
//ハッシュテーブルの中身を
/* 挿入のための関数 */
//ハッシュ値の衝突が発生した場合は、再ハッシュを繰り返して、「空状態」バケットを調べていき、空いているバケットを発見したらデータを格納します。
void set(int key, int value){
    std::cout << sizeof(empty_check[key]);//8

    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty or deleted cell
    int collision = 0;//衝突回数 のちにXorshiftで使うかも
    while (empty_check[hashIndex] == 1 ){//衝突が起こったとき
        //go to next cell
        ++hashIndex;
        ++collision;
        //wrap around the table
        hashIndex %= SIZE;
        //std::cout << "rehash = " << collision << std::endl;
    }
    collision = 0;
    hashArray[hashIndex].value = value;
    hashArray[hashIndex].key = key;
    empty_check[hashIndex] = 1;//使用済みにする
}
void display(){
    for(int i = 0; i < empty_check.size();i++){
        std::cout << empty_check[i] << "**" << hashArray[i].value << std::endl;

    }
}

void expand(){
    hashArray.resize(256);
    empty_check.resize(256);
}

};

}

#endif //OPEN_ADRESS__HASHING_HP