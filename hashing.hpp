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

public:
//ハッシュテーブルの要素数の初期値
static constexpr int null = -1;//データが入っていないことを示す値
static constexpr int dell = -2;//データが入っていたがそれが削除されたことを示す値
static constexpr int invalid = -1;
static constexpr int invalid_key = -1;
static constexpr int default_size = 4;

private://クラスメンバ変数
int SIZE;//ハッシュテーブルの大きさ(初期値)
int hash_use = 0;//ハッシュテーブルの使用数
/* DataItemの定義 */
struct DataItem {
    int key,value;
    DataItem(): key(invalid_key),value(null){}
};
std::vector<DataItem> hashArray;
//2倍の大きさのハッシュテーブル　拡張してhasharrayにコピーする用
std::vector<bool> exists;

public:
HashTable(size_t size = default_size) : SIZE(size), hashArray(size), exists(size, false) {}

private:
/* ハッシュ関数の定義 */
int hashCode(int key){
    return key % SIZE;
}

/* 検索のための関数 */
/* liner Probingを使っているのでそれに合わせた検索を実装です。 */
public:
int const get(int key){
    //get the hash
    
    int hashIndex = hashCode(key);
    while (exists[hashIndex]){
        if (hashArray[hashIndex].key == key)
            return hashArray[hashIndex].value;
            //ここでは256のあまりが返る
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
        // SIZE = 2*SIZE;//SIZEを２倍にする
        // std::vector<DataItem> hashArray2(SIZE);
        // std::vector<bool> empty_check2(SIZE,false);
        // int hashIndex = 0;
        // int collision = 0;
        // //std::cout << "empty =   "<< exists.size() << std::endl; 
        // for(int i=0;i < SIZE/2;i++){//拡張する前のSIZE
        //     if(exists[i]){{//使用要素のみ再配置
        //         hashIndex = hashCode(hashArray[i].key);
        //         //std::cout << "re_set " << hashArray[i].value << std::endl;
        //         //std::cout << i << std::endl;
        //         while (empty_check2[hashIndex] == true){//衝突が起こったとき
        //             //go to next cell
        //             ++hashIndex;
        //             ++collision;
        //             //wrap around the table
        //             hashIndex %= SIZE;
        //         }
        //         //２倍にした方に再配置
        //     hashArray2[hashIndex].value = hashArray[i].value;
        //     hashArray2[hashIndex].key = hashArray[i].key;
        //     empty_check2[hashIndex] = true;//使用済みにする
        //     }
        // }
        // hashArray = std::move(hashArray2);//
        // exists = std::move(empty_check2);
    HashTable nht(SIZE*2);
    for (int i = 0; i < SIZE; i++) {
        if (!exists[i])
            continue;
        auto [k, v] = hashArray[i];
        nht.set(k, v);//--c++17 
    }
    *this = std::move(nht);
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