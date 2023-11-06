#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

struct PageTableEntry {
 int frame_number;
 bool valid;
};

struct ProcessControlBlock {
 int pid;
 int num_pages;
 vector<PageTableEntry> page_table;
};

vector<int> frame_table;
int allocate_frame(ProcessControlBlock& pcb, int page_number) {
    for (int i = 0; i < frame_table.size(); i++) {
        if (frame_table[i] == -1) {
            frame_table[i] = pcb.pid;
            pcb.page_table[page_number].frame_number = i;
            pcb.page_table[page_number].valid = true;
            return i;
        }
    }
    return -1; // No free frame available
}

void display_status(const vector<ProcessControlBlock>& processes) {
    for (const ProcessControlBlock& pcb : processes) {
        cout << "Process " << pcb.pid << " - Page Table:" << endl;
        for (int j = 0; j < pcb.num_pages; j++) {
            if (pcb.page_table[j].valid) {
                cout << "Page " << j << " -> Frame " << pcb.page_table[j].frame_number << endl;
            } else {
                cout << "Page " << j << " -> Not in memory" << endl;
            }
        }
    }
    cout << "Frame Allocation Status:" << endl;
    for (int i = 0; i < frame_table.size(); i++) {
        cout << "Frame " << i << " -> ";
        if (frame_table[i] == -1) {
        cout << "Not allocated" << endl;
        } else {
            for (const ProcessControlBlock& pcb : processes) {
            if (pcb.pid == frame_table[i]) {
                for (int j = 0; j < pcb.num_pages; j++) {
                    if (pcb.page_table[j].frame_number == i) {
                        cout << "Process " << pcb.pid << ", Page " << j << endl;
                        break;
                    }
                }
            }
        }
    }
 }
}
int main() {
    srand(time(0));
    int ram_size, page_size, num_processes;
    cout << "Enter RAM size: ";
    cin >> ram_size;
    cout << "Enter page size: ";
    cin >> page_size;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    vector<ProcessControlBlock> processes(num_processes);
    frame_table.resize(ram_size / page_size, -1);
    for (int i = 0; i < num_processes; i++) {
    processes[i].pid = i;
    cout << "Enter the number of pages for Process " << i << ": ";
    cin >> processes[i].num_pages;
    processes[i].page_table.resize(processes[i].num_pages);
    for (int j = 0; j < processes[i].num_pages; j++) {
    processes[i].page_table[j].frame_number = -1;
    processes[i].page_table[j].valid = false;
    }
    }
    int page_count = 0;
    int i=0;
    while (page_count < frame_table.size()&& i!=num_processes) {
    for ( i = 0; i < num_processes; i++) {
    for (int j = 0; j < processes[i].num_pages; j++) {
    if (page_count < frame_table.size() && allocate_frame(processes[i], j) != -1) {
    cout << "Page allocated: Process " << processes[i].pid << ", Page " << j << " -> Frame "
    << processes[i].page_table[j].frame_number << endl;
    page_count++;
    } else {
    break;
    }
    }
    }
    }
    for (int i = page_count; i < frame_table.size(); i++) {
    cout << "Frame " << i << " -> Not allocated" << endl;
    }
    display_status(processes);
 return 0;
}