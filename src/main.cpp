#include <Arduino.h>

String encodeBase64(String data) {
    const char* dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    dictionary += 0x00;
    dictionary += 0x00;
    String encoded = "";

    for (int i = 0; i < data.length(); i+=3) {

        byte s1 = (data[i] & 0b11111100) >> 2;
        byte s2 = (data[i] & 0b00000011) << 4 | (data[i+1] & 0b11110000) >> 4;
        byte s3 = (data[i+1] & 0b00001111) << 2 |(data[i+2] & 0b11000000) >> 6;
        byte s4 = (data[i+2] & 0b00111111);

        encoded += dictionary[s1];
        encoded += dictionary[s2];
        encoded += dictionary[s3];
        encoded += dictionary[s4];

        if(data.length() - 1 == i) {
            encoded.setCharAt(encoded.length() - 1, '=');
            encoded.setCharAt(encoded.length() - 2, '=');
        } else if(data.length() - 2 == i) {
            encoded.setCharAt(encoded.length() - 1, '=');
        }

    }

    return encoded;
}

void setup() {
    Serial.begin(9600);
    Serial.println("Base64 Test");

    Serial.println(encodeBase64("Testing String"));
}

void loop() {

}
