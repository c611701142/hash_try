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
static constexpr int SIZE = 8;
//ハッシュテーブルの要素数の初期値
uint8_t kLeafChar = 0;
/* DataItemの定義 */
public:
struct DataItem {
        int key,value;
        DataItem(): key(0),value(-1){}
    };
std::vector<DataItem> hashArray = {};
std::vector<bool> empty_check = {};
HashTable(){
};

/* ハッシュ関数の定義 */
int hashCode(int key){
    return key % empty_check.size();
}

/* 検索のための関数 */
/* liner Probingを使っているのでそれに合わせた検索を実装です。 */
int const get(int key){
    //get the hash
    
    int hashIndex = hashCode(key);
    
    while (empty_check[key] == 1){//要素が使用済みになるまで
        if (hashArray[hashIndex].key == key)
            return hashArray[hashIndex].value;
            //ここでは256のあまりが返る
        hashIndex++;

        //wrap around the table
        hashIndex %= empty_check.size();
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
        hashIndex %= empty_check.size();
        //std::cout << "rehash = " << collision << std::endl;
    }
    std::cout << "rehash = " << collision << std::endl;
    collision = 0;
    hashArray[hashIndex].value = value;
    hashArray[hashIndex].key = key;
    empty_check[hashIndex] = 1;//使用済みにする
}
void display(){
    for(int i = 0; i < empty_check.size();i++){
        std::cout << i << "    " << empty_check[i] << "       ";
        std::cout << hashArray[i].key << "->" << hashArray[i].value << std::endl;
    }
}
int get_percent(){
    int full = 0;
    for(int i = 0; i < empty_check.size();i++){
        if(empty_check[i] == 1){
            full++;
        }  
    }
    //std::cout << "percent = " <<  full*100/empty_check.size() << " \n";
    return full*100/empty_check.size();

}//全探索なので、ハッシュテーブルの要素が大きくなるほど時間がかかる

void expand(int time){
    std::cout << "time = " << time  << " \n";//ハッシュテーブルが成長した回数-1
    hashArray.resize(SIZE*time);
    empty_check.resize(SIZE*time);
}

};

}
#endif //OPEN_ADRESS__HASHING_HP