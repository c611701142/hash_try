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

//ハッシュテーブルの要素数の初期値
static constexpr int null = -1;//データが入っていないことを示す値
static constexpr int dell = -2;//データが入っていたがそれが削除されたことを示す値

int SIZE = 8;//ハッシュテーブルの大きさ(初期値)
/* DataItemの定義 */
public:
struct DataItem {
        int key,value;
        DataItem(): key(0),value(null){}
    };
std::vector<DataItem> hashArray = {};
std::vector<DataItem> hashArray2 = {};
//2倍の大きさのハッシュテーブル　拡張してhasharrayにコピーする用

std::vector<bool> empty_check = {};
HashTable(){
    hashArray.resize(SIZE);
    empty_check.resize(SIZE,0);
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
    
    //get the hash
    int hashIndex = hashCode(key);
    //move in array until an empty or deleted cell
    int collision = 0;//衝突回数 のちにXorshiftで使うかも
    while (empty_check[hashIndex] == 1){//衝突が起こったとき
        //go to next cell
        ++hashIndex;
        ++collision;
        //wrap around the table
        hashIndex %=   SIZE;
        std::cout << "key = " << key << std::endl;
        std::cout << "collision = " << collision << std::endl;
    }
    //std::cout << "hashnumber = " << hashIndex << std::endl;
    collision = 0;
    hashArray[hashIndex].value = value;
    hashArray[hashIndex].key = key;
    empty_check[hashIndex] = 1;//使用済みにする

    int load_factor = value*100/empty_check.size();
    std::cout << "before_expand" << load_factor << "%" << std::endl;

    //valueがインクリメントしてるだけなことを思い出し、こうしました。
    if(value == empty_check.size()){
        expand();
        resize();
        int load_factor2 = value*100/empty_check.size();
        std::cout << "after_expand" << load_factor2 << "%" << std::endl;
    }
}
void display(){
    for(int i = 0; i < empty_check.size();i++){
        std::cout << i << "    " << empty_check[i] << "       ";
        std::cout << hashArray[i].key << "->" << hashArray[i].value << std::endl;
    }
}

void expand(){
    SIZE = 2*SIZE;//SIZEを２倍にする
    hashArray2.resize(SIZE);
    empty_check.resize(SIZE,0);
}

void resize() {
        int hashIndex;
        int collision = 0;
        std::cout << "empty =   "<< empty_check[SIZE] << std::endl; 
        for(int i=0;i < SIZE/2;i++){//拡張する前のSIZE
            if(hashArray[i].key != 0 && hashArray[i].value != -1){//使用要素のみ再配置
                hashIndex = hashCode(hashArray[i].key);
                std::cout << "re_set " << hashArray[i].value << std::endl;
            }
            while (empty_check[hashIndex] == 1){//衝突が起こったとき
                //go to next cell
                ++hashIndex;
                ++collision;
                //wrap around the table
                hashIndex %= SIZE;
            }
        //２倍にした方に再配置
        hashArray2[hashIndex].value = hashArray[i].value;
        hashArray2[hashIndex].key = hashArray[i].key;
        empty_check[hashIndex] = 1;//使用済みにする
        }
        hashArray = std::move(hashArray2);//
        
        for(int i =0;i<empty_check.size();i++){//コピー
            if(hashArray[i].key == 0 && hashArray[i].value == -1){
                empty_check[i] = 0;//未使用要素にする
            }
        }  
    
}

// tnew にすべてを移す
/*留意点
1 ここで使用配列の割合を検知(get_rercent)
2 1に応じてハッシュテーブルを拡張
3 再配置を行う
*/

};

}
#endif //OPEN_ADRESS__HASHING_HP