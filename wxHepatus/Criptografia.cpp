#include <wxHepatus/Criptografia.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

namespace wxHepatus
{

std::string
crypto(std::string const& input, std::string const& key)
{
	char sbox[256];
    memset(sbox, 0, sizeof(sbox));
    for (std::size_t i = 0; i < 256U; ++i) {
        sbox[i] = (char)i;
    }

	char sbox2[256];
	memset(sbox2, 0, sizeof(sbox2));
    for (std::size_t i = 0, j = 0; i < 256U ; ++i) {
        if (j == key.length()) {
            j = 0;
        }
        sbox2[i] = key[j++];
    }    

    //scramble sbox1 with sbox2
    for (std::size_t i = 0, j = 0; i < 256U ; ++i) {
        j = (j + (std::size_t)sbox[i] + (std::size_t)sbox2[i]) % 256U ;
        char temp =  sbox[i];
        sbox[i] = sbox[j];
        sbox[j] =  temp;
    }

	std::string result = input;
    for (std::size_t i = 0, j = 0, x = 0; x < result.length(); ++x) {
        i = (i + 1U) % 256U;
        j = (j + (std::size_t) sbox[i]) % 256U;

        //Scramble SBox #1 further so encryption routine will 
        //will repeat itself at great interval
        char temp = sbox[i];
        sbox[i] = sbox[j] ;
        sbox[j] = temp;

        //Get ready to create pseudo random  byte for encryption key
        std::size_t t = ((std::size_t)sbox[i] + (std::size_t)sbox[j]) %  256U;

        //xor with the data and done
        result[x] ^= sbox[t];
    }
    return result;
}

std::string
toHEX(boost::uint8_t number) {
	char hexChars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	std::string result;
	if (number < 16) {
		result = "0";
	} else {
		result = hexChars[number/16];
		number = number % 16;
	}
	return result + hexChars[number];
}

std::string
crypt(std::string const& seed, std::string const& key)
{
   	std::string cryptoSeed = crypto(seed, key);
	std::string aux = "";
   	for (std::size_t i = 0; i < cryptoSeed.length(); ++i) {
		boost::uint8_t e1 = 255 - boost::uint8_t(cryptoSeed[i]);
      	aux += toHEX(e1);
   	}
   	return aux;
}

struct FileGuard 
{ 
	FILE* keyFile; 
	FileGuard(FILE* keyFile) : keyFile(keyFile) {} 
	~FileGuard() { fclose(keyFile); } 
};	
	
void 
generarKeyFile(std::string const& keyFileName, std::string const& seed)
{	
	FILE* keyFile = fopen(keyFileName.c_str(), "w");
	if (!keyFile) {
		throw std::runtime_error("can't open file: " + keyFileName);
	}
	FileGuard guard(keyFile);	
	struct stat keyFileStats;
	if (stat(keyFileName.c_str(), &keyFileStats) == -1) {
		throw std::runtime_error("can't get stats from file: " + keyFileName);
	}
    tm* time = localtime(&keyFileStats.st_mtime);
    char timeStr[13];
    sprintf(timeStr, "%d%02d%02d%02d%02d", time->tm_year + 1900, 
            time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min);
    
    std::string cryptString = crypt(seed, timeStr);
    std::string key = crypto(cryptString, timeStr);
    char keyBuffer[41];
    memset(keyBuffer, 0, sizeof(keyBuffer));
    strncpy(keyBuffer, key.c_str(), sizeof(keyBuffer) - 1);
    fwrite(keyBuffer, sizeof(keyBuffer), 1, keyFile);
}

}

