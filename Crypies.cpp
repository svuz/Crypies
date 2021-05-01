#include "Lib\aes.h"
#include "Lib\cryptlib.h"
#include "Lib\filters.h"
#include "Lib\osrng.h"
#include "Lib\hex.h"
#include "Lib\modes.h"
#include "Lib\base64.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;
using namespace CryptoPP;
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::StringSink;
using CryptoPP::StreamTransformation;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::CTR_Mode;

void InitKey(byte* key, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        key[i] = rand();
    }
}

/*
string Base64CryptIvKey(byte key, byte iv) {
    Base64Encoder encoder;
    encoder.Put(key, sizeof(key));
    encoder.MessageEnd();

    word64 size = encoder.MaxRetrievable();
    if (size)
    {
        key.resize(size);
        encoder.Get((byte*)&key[0], key.size());
    }
}
*/

string CTRCrypt(string plainText){
    //Initialize common key and IV with appropriate values
    byte key[32];
    byte iv[16];

    // Initialize common key and IV with appropriate values
    InitKey(key, sizeof(key));
    InitKey(iv, sizeof(iv));
    //Create an encrypted object
    CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKeyWithIV(key, sizeof(key), iv);
    string encText;
    CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText));

    // encryption
    encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
    encFilter.MessageEnd();

    return encText;
    

}

/*
void CTRDecrypt(string Cipher, byte Key[32], byte iv[16]) {
    CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(key, sizeof(key), iv);
    string decText;
    CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
    decFilter.Put(reinterpret_cast<const byte*>(Cipher.c_str()), Cipher.size());
    decFilter.MessageEnd();

    cout << "Decrypted Text : " << decText << endl;
}
*/

string OPFile(string FILENAME) {
    string CFILE = FILENAME + ".nice";
    return CFILE;
}

string ReadFile(string FILEPATH) {
    string file;
    ifstream inFile;
    // open the file stream
    inFile.open(FILEPATH);
    // check if opening a file failed
    if (inFile.fail()) {
        cerr << "Error opeing a file" << endl;
        inFile.close();
        exit(1);
    }
    string line;
    while (getline(inFile, line))
    {
        file.append(line+"\n");
    }
    // close the file stream
    inFile.close();
    return file;

}

int main() {
    string LOCATION = "C:\\Users\\smbla\\Desktop\\saad.txt";
    cout << CTRCrypt(ReadFile(LOCATION)) << endl;
    //CTRCrypt("Hello");
}