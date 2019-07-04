#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <typeinfo>


// ��CRC16 ����ܶ��ظ���Ϊ������ģ�����ֲ��
namespace LRC {
    typedef unsigned char BYTE;
    typedef unsigned short WORD;

    /**
    * @brief         calculate LRC
    * @author        George
    * @date          2019-07-03
    */
    // https://www.modbustools.com/modbus.html
    inline BYTE calLRC(BYTE *nData, WORD wLength)
    {
        BYTE nLRC = 0; // LRC char initialized

        for (int i = 0; i < wLength; i++) {
            nLRC += *nData++;
        }

        return (BYTE)(-nLRC);

    } // End: LRC


    /**
    * @brief         ��intת��Ϊhex, ����һ���ֽڵ���ʽ���
    * @author        George
    * @date          2019-07-04
    */
    inline std::string intToHex2(int input)
    {
        std::stringstream stream;
        stream << std::setw(2) << std::setfill('0') << std::hex << input;
        return stream.str();
    }

    /**
    * @brief         toupper every char in nData
    * @author        George
    * @date          2019-07-03
    */
    inline void mytoupper(BYTE *nData, WORD wLength) {
        for (int i = 0; i < wLength; i++) {
            if (*nData >= 'a' && *nData <= 'z') {
                *nData = toupper(*nData);
            }
            nData++;
        }
    }

    /**
    * @brief         toupper every char in nData
    * @author        George
    * @date          2019-07-03
    */
    inline std::string mytoupper2(std::string nData) {
        // std::cout << "==" << "SIZE: " << nData.size() << "==" << std::endl;
        for (int i = 0; i < nData.size(); i++) {
            // std::cout << "==" << nData[i] << "==" << std::endl;
            if (nData[i] >= 'a' && nData[i] <= 'z') {
                nData[i] = toupper(nData[i]);
            }
        }
        return nData;
    }


    /**
    * @brief         ��char����ת��Ϊ��hex������ַ���
    * @author        George
    * @date          2019-07-04
    */
    inline std::string convertCharToHexString(const BYTE *nData, WORD wLength) {
        std::string res;
        while (wLength--)
        {
            res.append(mytoupper2(intToHex2(static_cast<int>(*nData++))));
        }
        return res;
    }

    /**
    * @brief         convert each char in Input string to Ascii and ignore space in Input string
    * @author        George
    * @date          2019-07-03
    */
    inline std::string convertStringToFinalAscii(std::string temp) {

        std::string results = "3A";
        std::stringstream tempStream;
        // ===== ƴ��У���� ======= //
        for (size_t i = 0; i < temp.size(); i++)
        {
            if (temp[i] == ' ') {
                continue;
            }
            tempStream << std::hex << int(temp[i]);
            // std::cout << tempStream.str() << std::endl;
            // tempStream.clear();
        }
        results.append(tempStream.str());
        std::string tempRes = "0D0A";
        results.append(tempRes);

//        std::cout << "===============================" << std::endl;
//        std::cout << "Results:   " << results << std::endl;
//        std::cout << "===============================" << std::endl;

        return results;
    }

    /**
    * @brief         convert the data to Ascii string(following the modbus rule)
    * @author        George
    * @date          2019-07-03
    */
    inline std::string convertIntToModbusString(int input, int numberOfRefgister) {
        const int wLength = 6;
        // 1. ���ó�ʼֵ -- ������У����
        BYTE byteArray[wLength] = { 0x01, 0x06, 0x13, 0x18, 0xFF, 0x00 };

        // 2. �Ĵ�������
        // ---- ��λ ---- //
        *(byteArray + 2) = static_cast<BYTE>(numberOfRefgister >> 8);
        // ---- ��λ ---- //
        *(byteArray + 3) = static_cast<BYTE>((numberOfRefgister & 0x00FF));
        // 3. ���÷���λ
        if (input <= 0) {
            *(byteArray + 4) = 0xFF;
            input = std::abs(input);
        }
        else
        {
            *(byteArray + 4) = 0x00;
        }

        // 4. ����д�����ݵľ���ֵ ������ֵת��Ϊ16����
        *(byteArray + 5) = static_cast<BYTE>(input);

        std::string intStr1 = convertCharToHexString(byteArray, wLength);

//        std::cout << "===============================" << std::endl;
//        std::cout << "intStr1:   " << intStr1 << std::endl;
//        std::cout << "===============================" << std::endl;

        // 5. У�������
        BYTE tempLRC;
        tempLRC= calLRC(byteArray, wLength);

        std::string intStr2 = mytoupper2(intToHex2(tempLRC));

//        std::cout << "===============================" << std::endl;
//        //std::cout << intToHex2(tempLRC) << std::endl;
//        std::cout << "intStr2:   " << intStr2 << std::endl;
//        std::cout << "===============================" << std::endl;

        intStr1.append(intStr2);

//        std::cout << "===============================" << std::endl;
//        std::cout << "intStr:   " << intStr1 << std::endl;
//        std::cout << "===============================" << std::endl;

        return convertStringToFinalAscii(intStr1);
    }
}
