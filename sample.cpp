#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

uint8_t kLeafChar = 0;
static constexpr uint8_t kEmptyCheck = 0xFF;
static constexpr int kEmptyBase = 0xFFFFFFFF;
/*
struct DataItem{
    int value = -1;
    int key;
};
struct DataItem hashArray[SIZE] = {};//初期化
*/
std::vector<bool> empty_check = {};
struct DataItem {
        int key,value;
        DataItem(int k=0, int v=-1) : key(k),value(v){}
    };
    std::vector<DataItem> hashArray;//外から

/* ハッシュ関数の定義 */
int hashCode(int key){
    return key % empty_check.size();
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
        hashIndex %=  empty_check.size();
    }
    return hashArray[hashIndex].value;//ここでは初期値が返る
}
//ハッシュテーブルの中身を
/* 挿入のための関数 */
//ハッシュ値の衝突が発生した場合は、再ハッシュを繰り返して、「空状態」バケットを調べていき、空いているバケットを発見したらデータを格納します。
void set(int key, int value){
    hashArray[key].value = value;
    hashArray[key].key = key;
    empty_check[key] = 1;//使用済みにする
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
        hashIndex %=  empty_check.size();
        //std::cout << "rehash = " << collision << std::endl;
    }
    collision = 0;
}
void display(){
    for(int i = 0; i < empty_check.size();i++){
        std::cout << i << "  ";
        std::cout << empty_check[i] << "  ";
        std::cout << hashArray[i].key << "-->" << hashArray[i].value << std::endl;

    }
}
/*
int find_base(const std::unordered_map<uint8_t, int>& row) {
        for (int base = 0; true; ++base) {
            bool found = true;
            for (auto p : row) {
                uint8_t c = p.first;
                int next_row = p.second;
                std::cout << "top =" << next_row << std::endl;
                int index = base + c;//xorに変更　
                if (index < hashArray.size() and hashArray[index].value != -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return base;
            }
        }
        return hashArray.size();
    }

void expand(int index) {
    if (index < hashArray.size())
        return;
    hashArray.resize(index+1);
}
*/  
void hash_try(const std::vector<std::string> str_list) {
    // Create hash_table
    std::vector<std::unordered_map<uint8_t, int>> table(1);
    for (auto& key : str_list) {
        int node = 0;
        //hashArray.resize();
        //int new_node = 0;
        std::cout << "key" << key << std::endl;
        for (uint8_t c : key) {
            if (table[node].count(c) == 1) { // exists
                node = table[node][c];
                //hashArray[c].key = node;
            } 
            else {
                auto new_node = table.size();
                table.emplace_back();
                table[node][c] = new_node;
                empty_check.resize(new_node + 1,0);
                hashArray.resize(new_node + 1);
                //とりあえず今はセグメントエラー回避のためにここでハッシュテーブルの
                //拡張をしています
                set(node,new_node);//key→遷移文字、遷移元 value→遷移先でハッシュテーブルに保存
                                   //多分この条件文でしか保存していないので要素が少ないと思っています
                node = new_node;
            }
            std::cout << "code =" << c << std::endl;
            std::cout << "node =" << node << std::endl;
            //std::cout << "now_node" << new_node << std::endl;
        }
        if (table[node].count(kLeafChar) == 0) {
            table[node][kLeafChar] = 1;
            std::cout << "leaf_node" << std::endl;
        }
    }
    std::cout << "************************" << std::endl;
    /*
     std::vector<int> row_to_index(table.size());
        //bc_ = {0, kEmptyCheck}; // set root element
        row_to_index[0] = 0;
        for (int i = 0; i < table.size(); i++) {
            auto& row = table[i];
            if (row.empty())
                continue;
            int parent_index = row_to_index[i];
            std::cout << "parent" << parent_index << std::endl;
            int key = find_base(row);
            std::cout << "parent index ="<< parent_index <<"\n";
            std::cout << "findbase complete" <<"\n";
            hashArray[parent_index].key = key;
            /*
            for (auto p : row) {
                std::cout << "KKKKKKKKKK" <<"\n";
                uint8_t c = p.first;
                int next_row = p.second;
                int next_index = key + c;//xorに変更
                expand(next_index);
                std::cout << "expand complete" <<"\n";
                hashArray[next_index].value = parent_index;
                row_to_index[next_row] = next_index;
            }
        }*/
}

int main(int argc, char* argv[]){
    //hashArray.resize(256);
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
  display();
  return 0;
}