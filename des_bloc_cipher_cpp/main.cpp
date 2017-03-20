//
//  main.cpp
//  des_block_cipher
//
//  Created by Mahesh Mhatre on 3/20/17.
//  Copyright © 2017 Mahesh Mhatre. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>

// creating ck dk
std::string ck[17];
std::string dk[17];
std::string kn[17];

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    
    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");
    
    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");
        
        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");
        
        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

std::string GetBinaryStringFromHexString (std::string sHex)
{
    std::string sReturn = "";
    for (int i = 0; i < sHex.length(); ++i)
    {
        switch (sHex [i])
        {
            case '0': sReturn.append ("0000"); break;
            case '1': sReturn.append ("0001"); break;
            case '2': sReturn.append ("0010"); break;
            case '3': sReturn.append ("0011"); break;
            case '4': sReturn.append ("0100"); break;
            case '5': sReturn.append ("0101"); break;
            case '6': sReturn.append ("0110"); break;
            case '7': sReturn.append ("0111"); break;
            case '8': sReturn.append ("1000"); break;
            case '9': sReturn.append ("1001"); break;
            case 'A': sReturn.append ("1010"); break;
            case 'B': sReturn.append ("1011"); break;
            case 'C': sReturn.append ("1100"); break;
            case 'D': sReturn.append ("1101"); break;
            case 'E': sReturn.append ("1110"); break;
            case 'F': sReturn.append ("1111"); break;
        }
    }
    return sReturn;
}

std::string GetHexStringFromBinaryString (std::string sBin)
{
    std::string sReturn = "";
    for (int i = 0; i < sBin.length(); i=i+4)
    {
        std::string cmp = sBin.substr(i,4);
        if(cmp=="0000")sReturn.append("0");
        if(cmp=="0001")sReturn.append("1");
        if(cmp=="0010")sReturn.append("2");
        if(cmp=="0011")sReturn.append ("3");
        if(cmp=="0100")sReturn.append("4");
        if(cmp=="0101")sReturn.append("5");
        if(cmp=="0110")sReturn.append("6");
        if(cmp=="0111")sReturn.append("7");
        if(cmp=="1000")sReturn.append("8");
        if(cmp=="1001")sReturn.append("9");
        if(cmp=="1010")sReturn.append("A");
        if(cmp=="1011")sReturn.append("B");
        if(cmp=="1100")sReturn.append("C");
        if(cmp=="1101")sReturn.append("D");
        if(cmp=="1110")sReturn.append("E");
        if(cmp=="1111")sReturn.append("F");
    }
    return sReturn;
}

std::string keyPermutationPC1(std::string k){
    
    
    int PC1[64] = {  57  , 49   , 41  , 33  ,  25  ,  17  ,  9,
        1  , 58  ,  50  , 42  ,  34  ,  26  , 18,
        10 ,   2  ,  59 ,  51  ,  43  ,  35  , 27,
        19 ,  11   ,  3 ,  60   , 52  ,  44  , 36,
        63  , 55   , 47  , 39  ,  31  ,  23 ,  15,
        7 ,  62  ,  54 ,  46  ,  38  ,  30  , 22,
        14  ,  6  ,  61  , 53  ,  45  ,  37  , 29,
        21  , 13  ,   5  , 28   , 20  ,  12  ,  4};
    
    return "";
    
}

std::string convertKeyTo48bits(std::string k64){
    
    std::string key48;
    int counter = 0;
    for(int i=1;i<=64;i++){
        
        if(i%8==0){}
        else{
            
            key48  += k64[i-1];
            counter++;
            
        }
    }
    return key48;
}

std::string leftShift(std::string s1,int pos){
    
    s1.append(s1.substr(0, pos));
    s1=s1.substr(pos, s1.length());
    
    return s1;
}

std::string PC2(std::string cn,std::string dn){
    
    int pc2[48] = {14  ,  17  , 11  ,  24   ,  1  ,  5,
        3  ,  28  , 15  ,   6  ,  21 ,  10,
        23  ,  19  , 12  ,   4  ,  26  ,  8,
        16   ,  7  , 27   , 20  ,  13  ,  2,
        41  ,  52 ,  31   , 37  ,  47  , 55,
        30  ,  40  , 51  ,  45   , 33   ,48,
        44  ,  49  , 39  ,  56  ,  34  , 53,
        46  ,  42  , 50   , 36  ,  29  , 32};
    
    std::string c = cn +dn;
    std::string s;
    for(int i=0;i<48;i++){
        
        s += c[pc2[i]-1];
    }
    return s;
}

std::string Ern(std::string r){
    
    int Ebits[48] = {32   ,  1  ,  2  ,   3   ,  4  ,  5,
        4  ,   5  ,  6  ,   7   ,  8  ,  9,
        8   ,  9  , 10   , 11  ,  12  , 13,
        12  ,  13 ,  14  ,  15  ,  16  , 17,
        16  ,  17  , 18  ,  19  ,  20  , 21,
        20  ,  21 ,  22  ,  23  ,  24  , 25,
        24  ,  25  , 26  ,  27  ,  28  , 29,
        28  ,  29  , 30   , 31  ,  32  ,  1};
    
    std::string r48;
    
    for(int i=0;i<48;i++){
        
        r48 += r[Ebits[i]-1];
        
    }
    return r48;
}

void produceKeys(std::string inputString){
    std::string hexSt = string_to_hex(inputString);
    std::string binSt = GetBinaryStringFromHexString(hexSt);
    //std::cout << binSt << std::endl;
    std::string k48 =  convertKeyTo48bits(binSt) ;
    //std::cout << k48 << std::endl;
    // divide the key into 2 halves
    std::string c0,d0;
    for(int i=0;i<k48.length();i++){
        
        if(i<28){
            c0 += k48[i];
        }
        else{
            d0 += k48[i];
        }
    }
    
    //std::cout << "showing c0 and d0" << std::endl;
    //std::cout << c0 << std::endl;
    //std::cout << d0 << std::endl;
    
    ck[0] = c0;
    dk[0] = d0;
    
    int shiftNums[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    
    for(int i=0;i<16;i++){
        ck[i+1] = leftShift(ck[i], shiftNums[i]);
        dk[i+1] = leftShift(dk[i], shiftNums[i]);
    }
    
    //produce kn
    
    for(int i=0;i<16;i++){
        kn[i+1] = PC2(ck[i+1], dk[i+1]);
        //std::cout << "Round " << i << " : " << kn[i] << std::endl;
    }
}

std::string bitwiseXor(std::string s1,std::string s2){
    
    int s1l = s1.length();
    int s2l = s2.length();
    if(s1.length() != s2.length())
        return "0";
    std::string s;
    for(int i=0;i<s1.length();i++){
        
        if((s1[i] == '0' && s2[i] == '0') || (s1[i] == '1' && s2[i] == '1'))
            s += "0";
        else
            s += "1";
    }
    return s;
}

std::string initialPermutation(std::string message){
    
    int IP[64] = {58  ,  50  , 42  ,  34  ,  26  , 18  ,  10  ,  2,
        60  ,  52  , 44  ,  36  ,  28  , 20  ,  12  ,  4,
        62  ,  54  , 46  ,  38   , 30  , 22   , 14   , 6,
        64  ,  56  , 48  ,  40  ,  32  , 24  ,  16  ,  8,
        57  ,  49  , 41  ,  33  ,  25  , 17   ,  9  ,  1,
        59  ,  51  , 43   , 35   , 27  , 19   , 11  ,  3,
        61   , 53  , 45  ,  37  ,  29  , 21   , 13  ,  5,
        63  ,  55  , 47  ,  39  ,  31  , 23   , 15  ,  7};
    
    std::string s;
    for(int i=0;i<64;i++){
        s += message[IP[i]-1];
    }
    return s;
}


int binaryString2int(std::string binStr){
    
    int value = 0;
    int indexCounter = 0;
    for(int i=binStr.length()-1;i>=0;i--){
        
        if(binStr[i]=='1'){
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}

std::string SBox32(std::string s1,int boxNo){
    
    std::string sB[8][4][16] ={
        {   // s1
            {"1110","0100","1101","0001","0010","1111","1011","1000","0011","1010","0110","1100","0101","1001","0000","0111"},
            {"0000","1111","0111","0010","1110","0010","1101","0001","1010","0110","1100","1011","1001","0101","0011","1000"},
            {"0100","0001","1110","1000","1101","0110","0010","1011","1111","1100","1001","0111","0011","1010","0101","0000"},
            {"1111","1100","1000","0010","0100","1001","0001","0111","0101","1011","0011","1110","1010","0000","0110","1101"}
        },
        {   // s2
            {"1111","0001","1000","1110","0110","1011","0011","0100","1001","0111","0010","1101","1100","0000","0101","1010"},
            {"0011","1101","0100","0111","1111","0010","1000","1110","1100","0000","0001","1010","0110","1001","1011","0101"},
            {"0000","1110","0111","1011","1010","0100","1101","0001","0101","1000","1100","0110","1001","0011","0010","1111"},
            {"1101","1000","1010","0001","0011","1111","0100","0010","1011","0110","0111","1100","0000","0101","1110","1001"},
        },
        {   // s3
            {"1010","0000","1001","1110","0110","0011","1111","0101","0001","1101","1100","0111","1011","0100","0010","1000"},
            {"1101","0111","0000","1001","0011","0100","0110","1010","0010","1000","0101","1110","1100","1011","1111","0001"},
            {"1101","0110","0100","1001","1000","1111","0011","0000","1011","0001","0010","1100","0101","1010","1110","0111"},
            {"0001","1010","1101","0000","0110","1001","1000","0111","0100","1111","1110","0011","1011","0101","0010","1100"}
        },
        {   // s4
            {"0111","1101","1110","0011","0000","0110","1001","1010","0001","0010","1000","0101","1011","1100","0100","1111"},
            {"1101","1001","1011","0101","0110","1111","0000","0011","0100","0111","0010","1100","0001","1010","1110","1001"},
            {"1010","0110","1001","0000","1100","1011","0111","1101","1111","0001","0011","1110","0101","0010","1000","0100"},
            {"0011","1111","0000","0110","1010","0001","1101","1000","1001","0100","0101","1011","1100","0111","0010","1110"}
        },
        {   // s5
            {"0010","1100","0100","0001","0111","1010","1011","0110","1000","0101","0011","1111","1101","0000","1110","1001"},
            {"1110","1011","0010","1100","0100","0111","1101","0001","0101","0000","1111","1010","0011","1001","1000","0110"},
            {"0100","0010","0001","1011","1010","1101","0111","1000","1111","1001","1100","0101","0110","0011","0000","1110"},
            {"1011","1000","1100","0111","0001","1110","0010","1101","0110","1111","0000","1001","1010","0100","0101","0011"}
        },
        {   // s6
            {"1100","0001","1010","1111","1001","0010","0110","1000","0000","1101","0011","0100","1110","0111","0101","1011"},
            {"1010","1111","0100","0010","0111","1100","1001","0101","0110","0001","1101","1110","0000","1011","0011","1000"},
            {"1001","1110","1111","0101","0010","1000","1100","0011","0111","0000","0100","1010","0001","1101","1011","0110"},
            {"0100","0011","0010","1100","1001","0101","1111","1010","1011","1110","0001","0111","0110","0000","1000","1101"}
        },
        {   // s7
            {"0100","1101","0010","1110","1111","0000","1000","1101","0011","1100","1001","0111","0101","1010","0110","0001"},
            {"1101","0000","1011","0111","0100","1001","0001","1010","1110","0011","0101","1100","0010","1111","1000","0110"},
            {"0001","0100","1011","1101","1100","0011","0111","1110","1010","1111","0110","1000","0000","0101","1001","0010"},
            {"0110","1011","1101","1000","0001","0100","1010","0111","1001","0101","0000","1111","1110","0010","0011","1100"}
        },
        {   // s8
            {"1101","0010","1000","0100","0110","1111","1011","0001","1010","1001","0011","1110","0101","0000","1100","0111"},
            {"0001","1111","1101","1000","1010","0011","0111","0100","1100","0101","0110","1011","0000","1110","1001","0010"},
            {"0111","1011","0100","0001","1001","1100","1110","0010","0000","0110","1010","1101","1111","0011","0101","1000"},
            {"0010","0001","1110","0111","0100","1010","1000","1101","1111","1100","1001","0000","0011","0101","0110","1011"}
        }
    };
    
    std::string row;
    row += s1[0];
    row+= s1[5];
    int rC = binaryString2int(row);
    //rC = rC-1;
    
    int cC = binaryString2int(s1.substr(1,4));
    //cC = cC-1;
    
    return sB[boxNo][rC][cC];
}

std::string f32(std::string r32){
    
    int IP2[32] = { 16 ,  7 , 20 , 21,
        29 , 12 , 28 , 17,
        1 , 15 , 23 , 26,
        5 , 18 , 31 , 10,
        2 ,  8 , 24 , 14,
        32 , 27 ,  3 ,  9,
        19 , 13 , 30  , 6,
        22 , 11  , 4 , 25};
    
    std::string s;
    for(int i=0;i<32;i++){
        s += r32[IP2[i]-1];
    }
    return s;
}

std::string finalPermutation(std::string str64){
    
    int IPn[64] =   {   40  ,   8  , 48  ,  16  ,  56 ,  24  ,  64 ,  32,
        39   ,  7  , 47  ,  15  ,  55  , 23  ,  63 ,  31,
        38  ,   6  , 46  ,  14  ,  54 ,  22  ,  62  , 30,
        37  ,   5  , 45  ,  13  ,  53  , 21  ,  61 ,  29,
        36  ,   4  , 44  ,  12  ,  52  , 20  ,  60 ,  28,
        35  ,   3  , 43  ,  11  ,  51  , 19  ,  59 ,  27,
        34  ,   2  , 42  ,  10  ,  50  , 18  ,  58 ,  26,
        33  ,   1  , 41  ,   9  ,  49  , 17  ,  57 ,  25};
    
    std::string s;
    for(int i=0;i<64;i++){
        
        s += str64[IPn[i]-1];
    }
    return s;
}

std::string encryptMessage(std::string hexSt){
    
    std::string binSt = GetBinaryStringFromHexString(hexSt);
    //std::cout << " Scrambed message" << std::endl;
    std::string ipStr = initialPermutation(binSt);
    // divide in to l0 and r0
    std::string l[17],r[17];
    std::string kE[17];
    std::string r48[17];
    
    // divide into left and right part
    for(int i=0;i<64;i++){
        if(i<32)
            l[0] += ipStr[i];
        else
            r[0] += ipStr[i];
    }
    
    for(int j=0;j<16;j++){
        
        // got l0 r0
        // converted right part into 48 bits by E(R0)
        r48[j] = Ern(r[j]); // E(rn-1)
        kE[j+1] = bitwiseXor(kn[j+1], r48[j]); // Kn + E(Rn-1)
        
        // Passing it through
        std::string Rk;
        for(int i=0;i<48;i+=6){
            std::string tobesent = kE[j+1].substr(i,6);
            Rk += SBox32(tobesent, (i/6));
        }
        
        std::string f = f32(Rk);
        
        r[j+1] = bitwiseXor(l[j], f);
        l[j+1] = r[j];
    }
    
    // flip left and right half
    std::string r16l16 = r[16] +l[16];
    
    // performing IP inverse function
    std::string encM = finalPermutation(r16l16);
    // get hex from binary
    std::string hexEnc = GetHexStringFromBinaryString(encM);
    return hexEnc;
}

std::string decryptMessage(std::string msg){
    
    std::string binSt = GetBinaryStringFromHexString(msg);
    //std::cout << " Scrambed message" << std::endl;
    std::string ipStr = initialPermutation(binSt);
    // divide in to l0 and r0
    std::string l[17],r[17];
    std::string kE[17];
    std::string r48[17];
    
    // divide into left and right part
    for(int i=0;i<64;i++){
        if(i<32)
            l[0] += ipStr[i];
        else
            r[0] += ipStr[i];
    }
    
    for(int j=0;j<16;j++){
        
        // got l0 r0
        // converted right part into 48 bits by E(R0)
        r48[j] = Ern(r[j]); // E(rn-1)
        kE[j+1] = bitwiseXor(kn[16-j], r48[j]); // Kn + E(Rn-1)
        
        // Passing it through
        std::string Rk;
        for(int i=0;i<48;i+=6){
            std::string tobesent = kE[j+1].substr(i,6);
            Rk += SBox32(tobesent, (i/6));
        }
        
        std::string f = f32(Rk);
        
        r[j+1] = bitwiseXor(l[j], f);
        l[j+1] = r[j];
    }
    
    // flip left and right half
    std::string r16l16 = r[16] +l[16];
    
    // performing IP inverse function
    std::string decM = finalPermutation(r16l16);
    // get hex from binary
    std::string hexdec = GetHexStringFromBinaryString(decM);
    return hexdec;
}


int main(int argc, const char * argv[]) {
    
    std::string inputString;
    std::cout << "Enter a key 8 bites key\n";
    std::cout << "The algorithm accepts 64 bit key with last bit of every byte as odd parity bit" << std::endl;
    std::cout << "Please enter 8 chars long alphanumeric key" << std::endl;
    while(true){
        std::cin >> inputString;
        
        if(inputString.length()==8)
            break;
        else
            std::cout << "Please enter 8 chars long key" << std::endl;
    }
    
    produceKeys(inputString);
    // insert code here...
    std::cout << "enter the message" << std::endl;
    std::string msg;
    std::cin >> msg;
    
    std::cout << "The message has " << msg.length()*8 << " bits" << std::endl;
    
    std::string encM;
    for(int i=0;i<msg.length();i=i+8){
        
        std::string bits64 = msg.substr(i,8);
        std::string hexSt = string_to_hex(bits64);
        encM += encryptMessage(hexSt);
    }
    
    
    //show encrypted message
    std::cout << " The encrypted message is " << encM << std::endl;
    std::string recvdMsg;
    for(int i=0;i<encM.length();i=i+16){
        
        std::string bits64 = encM.substr(i,16);
        std::string decM = decryptMessage(bits64);
        //show encrypted message
        
        recvdMsg += hex_to_string(decM);
    }
    
    std::cout << "The Decrypted message is " << recvdMsg << std::endl;
    return 0;
}

