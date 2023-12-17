#include <iostream>
#include <cstring>

class DynamicString {
private:
    int length;
    char array[255];

public:
    DynamicString() : length(0) {
        array[0] = '\0';
    }

    DynamicString(const char* s) {
        if (std::strlen(s) > 254) {
            throw std::invalid_argument("String length exceeds maximum");
        }

        length = std::strlen(s);
        strcpy_s(array, 255, s);
    }

    DynamicString& operator=(const DynamicString& other) {
        length = other.length;
        strcpy_s(array, 255, other.array);
        return *this;
    }


    DynamicString operator+(const DynamicString& other) {
        DynamicString result;

        if (length + other.length > 254) {
            throw std::invalid_argument("String length exceeds maximum");
        }

        strcat_s(result.array, array);
        strcat_s(result.array, other.array);
        result.length = length + other.length;

        return result;
    }

    bool operator<=(const DynamicString& other) const {
        return std::strncmp(array, other.array, std::min(length, other.length) + 1) <= 0;
    }

    bool operator>=(const DynamicString& other) const {
        return std::strncmp(array, other.array, std::min(length, other.length) + 1) >= 0;
    }

    bool operator==(const DynamicString& other) const {
        return std::strcmp(array, other.array) == 0;
    }

    bool operator!=(const DynamicString& other) const {
        return std::strcmp(array, other.array) != 0;
    }

    bool operator<=(const char* s) const {
        return std::strncmp(array, s, std::min(length, (int)std::strlen(s)) + 1) <= 0;
    }

    bool operator==(const char* s) const {
        return std::strcmp(array, s) == 0;
    }

    bool operator!=(const char* s) const {
        return std::strcmp(array, s) != 0;
    }

    bool operator<<(const char c) const {
        for (int i = 0; i < length; i++) {
            if (array[i] == c) {
                return true;
            }
        }

        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicString& s) {
        os << s.array;
        return os;
    }
};

int main() {
    DynamicString str1("Hello");
    DynamicString str2(" world!");
    // test assignment operator
    DynamicString str3 = str1;
    std::cout << "str3 = " << str3 << std::endl;

    // test concatenation operator
    DynamicString str4 = str1 + str2;
    std::cout << "str4 = " << str4 << std::endl;

    // test comparison operators
    std::cout << "str1 <= str2: " << (str1 <= str2) << std::endl;
    std::cout << "str1 >= str2: " << (str1 >= str2) << std::endl;
    std::cout << "str1 == str2: " << (str1 == str2) << std::endl;
    std::cout << "str1 != str2: " << (str1 != str2) << std::endl;

    // test inclusion operator
    DynamicString str5("abcd");
    DynamicString str6("defg");
    std::cout << "str5 << 'c': " << (str5 << 'c') << std::endl;
    std::cout << "str6 << 'c': " << (str6 << 'c') << std::endl;
    return 0;
}