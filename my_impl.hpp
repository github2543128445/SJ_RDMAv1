#pragma once

unsigned short write_string_into(char *buffer,std::string s){
    unsigned short len = s.length();
    memcpy(buffer, &len, sizeof(unsigned short));
    memcpy(buffer+2, s.data(), sizeof(char)*len);
    return 2+len;
}