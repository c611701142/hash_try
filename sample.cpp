#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

uint8_t kLeafChar = 0;
static constexpr uint8_t kEmptyCheck = 0xFF;
static constexpr int kEmptyBase = 0xFFFFFFFF;
std::vector<bool> empty_check = {};
struct DataItem {
        int key,value;
        DataItem(int k=0, int v=-1) : key(k),value(v){}
    };
std::vector<DataItem> hashArray = {};

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
    //std::cout << sizeof(empty_check[key]);//8

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
    //std::cout << "rehash = " << collision << std::endl;
    //std::cout << "hashtable_number = " << hashIndex << std::endl;
}
void display(){
    std::cout << "--------------------------" <<"\n";
    for(int i = 0; i < hashArray.size();i++){
        std::cout << i << "  ";
        std::cout << empty_check[i] << "  ";
        std::cout << hashArray[i].key << "-->" << hashArray[i].value << std::endl;

    }
}

void hash_try(const std::vector<std::string> str_list) {
    // Create hash_table
    //std::vector<std::string> str_list;
    //std::vector<uint8_t> code;
    int hashIndex = 1;
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
                    std::cout << "common spell" << std::endl;
                    std::cout << "node" << node << std::endl;
            } 
            else{//新しいノードが出てきたとき
                hashIndex++;
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
                hashArray.emplace_back(key,value);
                empty_check.emplace_back(1);
                std::cout << "key" << key << std::endl;
                std::cout << "value" << value << std::endl;
                std::cout << "hashIndex" << hashIndex << std::endl;
                //ハッシュテーブルにセット 
            }
        }
        //Q1,tableを使わずに、状態番号を割り当てる方法が思いつきません
        /*Q2,今のプログラムでは、新しいノードが出るたびに後ろからkeyとvalueをハッシュテーブルに
        入れているだけなのですが、これではハッシュテーブルの番号の情報が使えない気がします。
        (再ハッシュや衝突回数が発生しないので)
        ・ハッシュテーブルにkeyとvalueを格納するタイミング
        ・ハッシュテーブルの何番目にkeyとvalueを入れればよいのか
        ・ハッシュテーブルの成長のタイミングと条件文(教科書をみたのですが、見つけられませんでした)
         を教えていただけるとありがたいです。
        */
        if (table[node].count(kLeafChar) == 0){
                table[node][kLeafChar] = 1;
                std::cout << "------word_end--------" << std::endl;
        }
        
    }
    std::cout << "hashtable_complete" <<"\n";
}

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
  hash_try(str_list);
  display();
  return 0;//プログラム終了
}
