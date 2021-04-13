#include <iostream>
#include<fstream>
#include<algorithm>
#include <bits/stdc++.h>
#include <stdlib.h>
#include<strstream>
using namespace std;
struct karakter{
    char karakter;
    int gyak;
    int apa;
    int sorsz;
};

struct rendezes{
    bool operator()(const karakter &a,const karakter &b){
        if(a.gyak==0 || b.gyak==0){
            return a.sorsz<b.sorsz;
        }
        else{
            if(a.gyak==b.gyak){
                return a.sorsz<b.sorsz;
            }
            else{
               return a.gyak<b.gyak;
            }
        }
    }
};

struct charelem{
    char kar;
    string elem;
};

struct rendezsorszam{
    bool operator()(karakter a, karakter b){
        return a.sorsz<b.sorsz;
    }
};

string bejar(karakter *huffman,int sorsz,int meret,string sor){
    if(abs(huffman[sorsz].apa)!=meret){
        if(huffman[sorsz].apa<0){
            sor+="0";
        }
        else{
            sor+="1";
        }
        ///cout<<"Ezen a sorszamon:   "<<sorsz<<endl;
        ///cout<<"Ez a szam van    "<<huffman[sorsz].apa<<endl;
        ///cout<<endl;
        if(abs(huffman[sorsz].apa)<sorsz){
            cout<<"ERROR"<<endl;
        }
        else
            return bejar(huffman,abs(huffman[sorsz].apa),meret,sor);
    }
    else{
        if(huffman[sorsz].apa<0){
            sor+="0";
            return sor;
        }
        else{
            sor+="1";
            return sor;
        }
    }
}
string decToBinary(int n)
{
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    string bit="0000000";
    for (int j = i - 1; j >= 0; j--){
        //cout << binaryNum[j];
        int a = binaryNum[j];
        stringstream ss;
        ss << a;
        string str = ss.str();
        bit+=str;
    }
    ///cout<<"___"<<bit.length()<<"___"<<bit<<"___"<<endl;
    string bit2;
    for(int i=(bit.length()-7);i<bit.length();++i){
        bit2+=bit[i];
    }
    return bit2;

}

int main()
{
    ifstream fin("be.txt");
    string line,ossz;
    while(getline (fin, ossz)){
        line+=ossz;
    }

    cout<<line;
    cout<<endl;
    int a[256]={0};
    for(int i=0;i<line.length();++i){
        a[line[i]]++;
    }

    int szam=0;
    int kul_elem=0;
    for(int i=0;i<256;++i){
        if(a[i]!=0){
            ++kul_elem;
        }
    }

    cout<<"Kul elemek:"<<kul_elem<<endl;
    karakter huffman[2*(kul_elem-1)];
    for(int i=0;i<2*(kul_elem-1);++i){
        char k,ures;
        int gy;
        for(int j=szam;j<256;++j){
            if(a[j]!=0){
               gy=a[j];
               szam=j+1;
               k=j;
               break;
            }
        }
        huffman[i].gyak=gy;
        gy=0;
        huffman[i].karakter=k;
        k='\0';
        huffman[i].apa=0;
        huffman[i].sorsz=i;
    }

    /**for(int i=0;i<2*(kul_elem-1);++i){
        cout<<huffman[i].sorsz<<"   "<<huffman[i].karakter<<"   "<<huffman[i].gyak<<"   "<<huffman[i].apa<<endl;
    }*/
    sort(huffman,huffman+(sizeof(huffman)/sizeof(*huffman)),rendezes());
    cout<<endl<<endl;
    for(int i=0;i<2*(kul_elem-1);++i){
        cout<<huffman[i].sorsz<<"   "<<huffman[i].karakter<<"   "<<huffman[i].gyak<<"   "<<huffman[i].apa<<endl;
    }
    int apasorszam=kul_elem;
    for(int i=0;i<2*(kul_elem-1);i=i+2){
        int a;
        a=huffman[i].gyak+huffman[i+1].gyak;
        huffman[apasorszam].gyak=a;///ide ketto kellene beirodjon de nem irodik be ,itt a hiba
        huffman[i].apa=-apasorszam;
        huffman[i+1].apa=apasorszam;
        sort(huffman,huffman+(sizeof(huffman)/sizeof(*huffman)),rendezes());
        apasorszam++;
    }

        cout<<endl<<endl;
    for(int i=0;i<2*(kul_elem-1);++i){
        cout<<huffman[i].sorsz<<"   "<<huffman[i].karakter<<"   "<<huffman[i].gyak<<"   "<<huffman[i].apa<<endl;
    }

    sort(huffman,huffman+(sizeof(huffman)/sizeof(*huffman)),rendezsorszam());


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int teljeshossz=(sizeof(huffman)/sizeof(*huffman));
    /**char** chtomb=new char*[kul_elem];
    for(int i=0;i<kul_elem;++i){
        string hossz=bejar(huffman,i,(sizeof(huffman)/sizeof(*huffman)),"");
        chtomb[i]=new char[hossz.length()];
    }
    cout<<endl;*/

    charelem celem[kul_elem];
    string ss=bejar(huffman,0,(sizeof(huffman)/sizeof(*huffman)),"");
    for(int i=0;i<kul_elem;++i){
        for(int j=0;j<(bejar(huffman,i,(sizeof(huffman)/sizeof(*huffman)),"").length());++j){
            celem[i].kar=huffman[i].karakter;
            string str=(bejar(huffman,i,teljeshossz,""));
            celem[i].elem=str;
            ///chtomb[i][j]=str[j];
        }
    }
    for(int i=0;i<kul_elem;++i){
        cout<<celem[i].kar<<" - "<<celem[i].elem<<endl;
    }


    /*for(int i=0;i<kul_elem;++i){
        for(int j=0;j<(bejar(huffman,i,(sizeof(huffman)/sizeof(*huffman)),"").length());++j){
            cout<<chtomb[i][j]<<"  ";
        }
        cout<<endl;
    }*/
    FILE *fp;
    fp=fopen("ki.txt","w");
    unsigned int beir=0;
    int szamlalo=0;
    for(int i=0;i<line.length();++i){
        for(int j=0;j<kul_elem;++j){
            if(celem[j].kar==line[i]){
                for(int k=0;k<celem[j].elem.length();++k){
                    ///beir=celem[j].elem[k];
                    cout<<celem[j].elem[k];
                    if(celem[j].elem[k]=='1'){
                        beir = beir << 1;
                        beir=(beir | 1);
                        szamlalo++;
                    }
                    else{
                            //cout<<beir;
                        beir=(beir << 1);
                        szamlalo++;
                    }
                    if(szamlalo==31){
                        ///fwrite(beir,sizeof(char),sizeof(beir), fp);
                        fprintf(fp,"%d",beir);
                        cout<<endl<<beir<<endl;
                        szamlalo=0;
                        beir=0;
                        ///cout<<beir<<"  "<<int(beir)<<endl;
                    }
                }
            }
        }
    }
    fprintf(fp,"%d",beir);
    cout<<endl<<beir<<endl;

    fclose(fp);
    fin.close();
    ifstream fin1("ki.txt");
    string line1,ossz1;
    while(getline (fin1, ossz1)){
        line1+=ossz1;
    }
    cout<<endl;
    for(int i=0;i<line1.length();++i){
        cout<<"line: "<<line1[i]<<" - "<<int(line1[i])<<endl;
    }
    cout<<endl<<line1<<endl;
    int dc;
    string bit,bitek;
    cout<<endl;
    for(int i=0;i<ossz1.length();++i){
        //cout<<int(ossz1[i])<<endl;
        dc=int(ossz1[i]);
       /// cout<<"--"<<dc<<"--";
        bit=decToBinary(dc);
        bitek+=bit;
        cout<<bit<<"  ";
    }

}
