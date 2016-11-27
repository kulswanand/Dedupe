#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

/* 
Linux commands before execution of my_dedupe 

$md5sum file* > md5_files.txt

Linux commands post execution of my_dedupe 

swanand@swanand-VirtualBox:~/Desktop/Dedupe$ mkdir ./d_f
swanand@swanand-VirtualBox:~/Desktop/Dedupe$ cat u_files.txt | awk '{system("cp "$0" ./d_f/")}'
swanand@swanand-VirtualBox:~/Desktop/Dedupe$ ls ./d_f/
file.dat  file_ns1.dat  file_ns2.dat

*/ 

/*
class Node 
{
public : 
   char file_name[40]; 
   class Node* next; 

   Node(char file_name) {
        this->file_name = file_name; 
   }
}

class Linked_List 
{
public : 
    Node* head; 

    Append(char file_name[]); 
    Print();  
}

*/ 

class my_dedupe
{
public : 
      char data[100]; 
      fstream afile,ufile; 
      int dcnt; // count of unique entries 
      
      // md5sum class 
      std::string md5[20];
      char filename[20][40]; 

      // deduped md5 class
      std::string d_md5[20];
      int  d_fname[20]; 
      std::string u_fname[20]; 
      
      int dedupe(void); 
      int md5checksum(void); 
      int u_files(void);
      int undedupe(); 
};

int main() {

    my_dedupe D1; 

    cout<<"Hello"<<endl; 

    D1.dedupe();

    return 0; 

}

 
int my_dedupe::dedupe(void) {
    int r, nof = 1, lcnt = 0;
    dcnt = 1;

    r = md5checksum();
    if (r == 0) 
         return 0; 

    d_md5[0] = md5[0];
    d_fname[0] = lcnt; 
    u_fname[0] = filename[0];
   
    r--; 
    while (nof < r) {
           for (lcnt=0;lcnt < nof;lcnt++) {
                 if (md5[lcnt] == md5[nof]) {
                     d_fname[nof] = lcnt; 
                     break; 
                 } else {
                     d_fname[nof] = dcnt; 
                 }     
           }
           if (lcnt == nof) {
            d_md5[dcnt] = md5[nof];
            u_fname[dcnt] = filename[nof]; 
            d_fname[nof] = dcnt; 
            dcnt++;
           } 
           nof++; 
    }

    for (lcnt = 0; lcnt < dcnt; lcnt++) {
         cout<<d_md5[lcnt]<<" "<<u_fname[lcnt]<<endl; 
    }
    for (lcnt = 0; lcnt < r; lcnt++) {
         cout<<filename[lcnt]<<" "<<d_fname[lcnt]<<" "<<d_md5[d_fname[lcnt]]<<endl; 
    }

    r = u_files(); 

    return dcnt; 
}

int my_dedupe::u_files(void) {
    int lcnt=0; 

    ufile.open("u_files.txt", ios::out | ios::in );  

    while (lcnt < dcnt) {
           ufile << u_fname[lcnt]<<endl;
           lcnt++;
    }

    ufile.close(); 
}

int my_dedupe::md5checksum(void) { 
    int nof = 0; 

    afile.open("md5_files.txt", ios::out | ios::in );

    while (afile >> md5[nof] >> filename[nof]) {
           cout<<md5[nof]<<" "<<filename[nof]<<" "<< endl;
           nof++;  
    }
    
    afile.close();
    return (++nof);
}

/* 
int my_dedupe::deduped_folder(void) {
    int lcnt = 0; 
    
    // create deduped folder 
    system("gnome-terminal -x sh -c 'mkdir ./deduped_folder'"); 
}
 
int Linked_List::Append(char file_name[]) {

     // Create Node 
     Node* Temp(file_name);  
     
     if(this == NULL) {
        this = Temp; 
     } else {
        Node* Head = this; 
        while (Head != NULL)
               Head = Head->next;  
     }
     
     Head->next = Temp;
     return 0; 
}

int Linked_List::Print(char file_name[]) {
     
}

*/ 
