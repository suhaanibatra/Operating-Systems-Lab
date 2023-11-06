#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

#define page_size 4096
#define page_table_size 16
#define logical_address_bits 16

map<int, int> page_table;

void createSamplePageTable(){
    for(int i = 0; i < page_table_size; i++){
        page_table[i] = rand() % 64; //random values from 0 to 63
    }
}

pair<int, int> translateAddress(int logical_address){
    int page_number = logical_address/page_size;
    int offset = logical_address % page_size;
    if(page_table.find(page_number) != page_table.end()){
        int frame_number = page_table[page_number];
        int physical_address = (frame_number * page_size) + offset;
        return make_pair(physical_address, frame_number);
    }
    else{
        return make_pair(-1, -1);
    }
}

int main(){
    srand(static_cast<unsigned>(time(nullptr))); 
    createSamplePageTable();
    int num_addresses_to_generate = 10;
    cout << "Logical Address\tPhysical Address\tFrame Number" << endl; 
    for (int i = 0; i < num_addresses_to_generate; i++){
        int logical_address = rand() % (1 << logical_address_bits);
        pair<int, int> result = translateAddress(logical_address);
        int physical_address = result.first;
        int frame_number = result.second;
        cout << logical_address << "\t\t" << physical_address << "\t\t\t" << frame_number << endl;
    }

    cout << "\nPage Table Entries:" << endl;
    for (auto it = page_table.begin(); it != page_table.end(); ++it) {
        cout << "Page " << it->first << ": Frame" << it->second << endl; 
    }
}